#include "game_loop.h"
#include "model.h"
#include "collision_detection/pellet_collision_detector.h"
#include "collision_detection/ghost_collision_detector.h"
#include "ghost_timing_manager.h"
#include "game_result.h"
#include <QTimer>

GameLoop::GameLoop(const GameConfig& gameConfig, Model& model) : model_(model),
                                                                 pacman_(model_.getPacman()),
                                                                 blueGhost_(model_.getBlueGhost()),
                                                                 orangeGhost_(model_.getOrangeGhost()),
                                                                 purpleGhost_(model_.getPurpleGhost()),
                                                                 redGhost_(model_.getRedGhost()),
                                                                 scoreManager_(model_.getScoreManager()),
                                                                 standardPelletCollisionDetector_(pacman_.getDiameter()),
                                                                 powerPelletCollisionDetector_(pacman_.getDiameter()),
                                                                 ghostCollisionDetector_(pacman_.getDiameter(), AbstractGhost::DIAMETER),
                                                                 standardPellets_(model_.getStandardPelletsManager().getPellets()),
                                                                 powerPellets_(model_.getPowerPelletsManager().getPellets())
{
    timer_ = std::make_unique<QTimer>();
    timer_->setTimerType(Qt::PreciseTimer);
    timer_->setInterval(gameConfig.CHARACTERS_MOVEMENT_INTERVAL_MS);
    connect(timer_.get(), &QTimer::timeout, this, &GameLoop::execute);

    ghosts_.at(0) = &blueGhost_;
    ghosts_.at(1) = &orangeGhost_;
    ghosts_.at(2) = &purpleGhost_;
    ghosts_.at(3) = &redGhost_;
}

void GameLoop::start()
{
    for (AbstractGhost* ghost: ghosts_)
    {
        ghost->getGhostTimingManager()->startLeaveStartingBoxTimer();
    }

    timer_->start();
}

void GameLoop::stop()
{
    timer_->stop();
}

void GameLoop::execute()
{
    // qDebug() << "GameLoop::execute";

    pacmanMovementHandler();

    ghostMovementHandler(blueGhost_);
    ghostMovementHandler(orangeGhost_);
    ghostMovementHandler(purpleGhost_);
    ghostMovementHandler(redGhost_);

    // qDebug() << "Pacman coordinates:" << pacman_.getCoordinates().x_ << "," << pacman_.getCoordinates().y_;
    // qDebug() << "Blue ghost coordinates:" << blueGhost_.getCoordinates().x_ << "," << blueGhost_.getCoordinates().y_;
    // qDebug() << "Orange ghost coordinates:" << orangeGhost_.getCoordinates().x_ << "," << orangeGhost_.getCoordinates().y_;
    // qDebug() << "Purple ghost coordinates:" << purpleGhost_.getCoordinates().x_ << "," << purpleGhost_.getCoordinates().y_;
    // qDebug() << "Red ghost coordinates:" << redGhost_.getCoordinates().x_ << "," << redGhost_.getCoordinates().y_;

    // Standard pellets collision detection
    for (size_t i = 0; i < standardPellets_.size(); ++i)
    {
        if (StandardPellet& standardPellet = standardPellets_.at(i); standardPelletCollisionDetector_.checkPacmanCollisionWithPellet(pacman_.getCoordinates(), standardPellet))
        {
            qDebug() << "Pacman eats standard pellet" << i;
            standardPellet.setAlive(false);
            model_.getStandardPelletsModel().pelletChanged(i);
            scoreManager_.increaseScoreForEatingStandardPellet();
        }
    }

    // Power pellets collision detection
    for (size_t i = 0; i < powerPellets_.size(); ++i)
    {
        if (PowerPellet& powerPellet = powerPellets_.at(i); powerPelletCollisionDetector_.checkPacmanCollisionWithPellet(pacman_.getCoordinates(), powerPellet))
        {
            qInfo() << "Pacman eats power pellet" << i;
            powerPellet.setAlive(false);
            model_.getPowerPelletsModel().pelletChanged(i);
            scoreManager_.increaseScoreForEatingPowerPellet();

            for (AbstractGhost* ghost: ghosts_)
            {
                ghost->setScared();
            }
        }
    }

    // Ghost collision detection
    for (AbstractGhost* ghost: ghosts_)
    {
        if (ghostCollisionDetector_.checkPacmanCollisionWithGhost(pacman_, *ghost))
        {
            if (ghost->isScared())
            {
                qInfo().noquote() << "Pacman eats" << ghost->getColor() << "ghost";
                qDebug().noquote() << "Pacman:" << pacman_.getCoordinates();
                qDebug().noquote() << ghost->getColor().toUpper() << "ghost:" << ghost->getCoordinates();

                scoreManager_.increaseScoreForEatingGhost();
                ghost->respawn();
            }
            else
            {
                qInfo().noquote() << "Pacman has been eaten by" << ghost->getColor() << "ghost";
                qDebug().noquote() << "Pacman:" << pacman_.getCoordinates();
                qDebug().noquote() << ghost->getColor().toUpper() << "ghost:" << ghost->getCoordinates();

                emit endGame(GameResult::DEFEAT);
            }
        }
    }

    if (model_.getStandardPelletsManager().getAliveStandardPelletsCount() == 0) // this will automatically make the game victorious if no standard pellets were created
    {
        emit endGame(GameResult::VICTORY);
    }
}

void GameLoop::pacmanMovementHandler()
{
    // qDebug() << "GameLoop::pacmanMovementHandler";

    pacmanMovementManager_.processMove(pacman_, model_.getPathPoints());

    pacman_.advanceAnimation();
    pacman_.changed();
}

void GameLoop::ghostMovementHandler(AbstractGhost& ghost)
{
    // qDebug().noquote() << ghost.getMoveTickCounter() << ":" << ghost.getColor() << "ghost moves";

    if (ghost.canMoveThisTurn())
    {
        if (ghostMovementManager_.isGhostInsideStartingBox(ghost))
        {
            if (ghost.getGhostTimingManager()->isItTimeToLeaveStartingBox())
            {
                ghostMovementManager_.moveOutOfStartingBox(ghost);
            }
            else
            {
                ghostMovementManager_.moveUpAndDownInsideStartingBox(ghost);
            }
        }
        else
        {
            ghostMovementManager_.processMove(ghost, pacman_.getCoordinates(), model_.getPathPoints());
        }

        ghost.advanceAnimation();
        ghost.changed();
    }

    ghost.incrementMoveTickCounter();
}
