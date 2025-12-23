#include "controller.h"

Controller::Controller(const GameConfig& gameConfig, Model& model, QQmlApplicationEngine& view) : model_(model), view_(view), gameStateManager_(this)
{
    qInfo() << "Initializing controller";

    gameLoop_ = std::make_unique<GameLoop>(gameConfig, model_);

    inputHandler_ = std::make_unique<InputHandler>(this, &windowManager_);

    connect(gameLoop_.get(), &GameLoop::endGame, this, &Controller::gameEnded);
}

void Controller::onQmlEngineFullyInitialized()
{
    qDebug() << "QML engine fully initialized";

    windowManager_.setWindow(qmlHelper_.getMainWindow());
    overlayManager_ = std::make_unique<OverlayManager>(qmlHelper_);

    gameCoordinator_ = std::make_unique<GameCoordinator>(model_, *gameLoop_, qmlHelper_);

    qInfo() << "Game started";
    setGameState(GameStateType::ReadyToStart);
}

void Controller::processKeyPress(const int key)
{
    // qDebug() << "Key pressed:" << key;
    inputHandler_->processKeyPress(key);
}

void Controller::startGameLoop()
{
    qDebug() << "Controller::startGameLoop()";
    gameCoordinator_->startGameLoop();
}

void Controller::stopGameLoop()
{
    qDebug() << "Controller::stopGameLoop()";
    gameCoordinator_->stopGameLoop();
}

void Controller::processPacmanDirectionKeyPress(const Direction& nextDirection)
{
    model_.getPacman().setNextDirection(nextDirection);
}

void Controller::showTextOverlay(const QString& text)
{
    overlayManager_->showTextOverlay(text);
}

void Controller::hideTextOverlay()
{
    overlayManager_->hideTextOverlay();
}

void Controller::showEscapeMenuOverlay()
{
    overlayManager_->showEscapeMenuOverlay();
}

void Controller::hideEscapeMenuOverlay()
{
    overlayManager_->hideEscapeMenuOverlay();
}

void Controller::showEndGameOverlay(const GameResult gameResult)
{
    overlayManager_->showEndGameOverlay(gameResult, model_.getScoreManager().getScoreAsString());
}

void Controller::hideEndGameOverlay()
{
    overlayManager_->hideEndGameOverlay();
}

void Controller::setGameState(const GameStateType newGameState)
{
    gameStateManager_.setGameState(newGameState);
}

void Controller::restorePreviousState()
{
    gameStateManager_.restorePreviousGameState();
}

void Controller::gameEnded(const GameResult gameResult)
{
    qDebug() << "Controller received endGame signal";

    if (gameResult == GameResult::VICTORY)
    {
        qInfo() << "Game ended. Result = victory";
        setGameState(GameStateType::EndedVictory);
    }
    else if (gameResult == GameResult::DEFEAT)
    {
        qInfo() << "Game ended. Result = defeat";
        setGameState(GameStateType::EndedDefeat);
    }
    else
    {
        throw std::runtime_error("Unsupported game result");
    }
}

void Controller::onResumeClicked()
{
    qInfo() << "Resume button clicked";
    gameStateManager_.restorePreviousGameState();
}

void Controller::onRestartClicked()
{
    qInfo() << "Restart button clicked";
    gameCoordinator_->restartGame();
    gameStateManager_.setGameState(GameStateType::ReadyToStart);
}

void Controller::onQuitClicked()
{
    qInfo() << "Quit button clicked";
    emit applicationShutdownRequested();
}

void Controller::onPlayAgainClicked()
{
    gameCoordinator_->restartGame();
    gameStateManager_.setGameState(GameStateType::ReadyToStart);
}
