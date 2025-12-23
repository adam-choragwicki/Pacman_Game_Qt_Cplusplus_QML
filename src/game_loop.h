#pragma once

#include "game_config.h"
#include "pellets/standard_pellet.h"
#include "pellets/power_pellet.h"
#include "collision_detection/pellet_collision_detector.h"
#include "collision_detection/ghost_collision_detector.h"
#include "pacman_movement_manager.h"
#include "ghost_movement_manager.h"

class Model;

class BlueGhost;
class OrangeGhost;
class PurpleGhost;
class RedGhost;

class ScoreManager;

enum class GameResult;

class GameLoop : public QObject
{
    Q_OBJECT

signals:
    void endGame(GameResult gameResult);

public:
    explicit GameLoop(const GameConfig& gameConfig, Model& model);
    void start();
    void stop();

private slots:
    void execute();

    void pacmanMovementHandler();
    void ghostMovementHandler(AbstractGhost& ghost);

private:
    Model& model_;

    Pacman& pacman_;

    BlueGhost& blueGhost_;
    OrangeGhost& orangeGhost_;
    PurpleGhost& purpleGhost_;
    RedGhost& redGhost_;

    std::array<AbstractGhost*, 4> ghosts_;

    ScoreManager& scoreManager_;

    std::unique_ptr<QTimer> timer_;

    PelletCollisionDetector<StandardPellet> standardPelletCollisionDetector_;
    PelletCollisionDetector<PowerPellet> powerPelletCollisionDetector_;
    GhostCollisionDetector ghostCollisionDetector_;

    std::vector<StandardPellet>& standardPellets_;
    std::vector<PowerPellet>& powerPellets_;

    PacmanMovementManager pacmanMovementManager_;
    GhostMovementManager ghostMovementManager_;
};
