#include "game_coordinator.h"

GameCoordinator::GameCoordinator(Model& model, GameLoop& gameLoop, QmlHelper& qmlHelper) : model_(model), gameLoop_(gameLoop), qmlHelper_(qmlHelper)
{}

void GameCoordinator::startGameLoop()
{
    gameLoop_.start();
}

void GameCoordinator::stopGameLoop()
{
    gameLoop_.stop();
}

void GameCoordinator::restartGame()
{
    qInfo() << "Restarting game";

    // Restore keyboard focus to GameInput
    QMetaObject::invokeMethod(qmlHelper_.getGameInput(), "refocus");

    model_.reset();
}
