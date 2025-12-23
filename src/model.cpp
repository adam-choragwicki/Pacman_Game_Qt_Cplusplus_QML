#include "model.h"

Model::Model(const GameConfig& gameConfig)
{
    qInfo() << "Initializing model";

    pathPoints_ = std::make_unique<PathPoints>();

    pacman_ = std::make_unique<Pacman>(gameConfig.pacman().STARTING_COORDINATES, gameConfig.pacman().STARTING_DIRECTION);
    blueGhost_ = std::make_unique<BlueGhost>(gameConfig.blueGhost().STARTING_COORDINATES, gameConfig.blueGhost().STARTING_DIRECTION);
    orangeGhost_ = std::make_unique<OrangeGhost>(gameConfig.orangeGhost().STARTING_COORDINATES, gameConfig.orangeGhost().STARTING_DIRECTION);
    purpleGhost_ = std::make_unique<PurpleGhost>(gameConfig.purpleGhost().STARTING_COORDINATES, gameConfig.purpleGhost().STARTING_DIRECTION);
    redGhost_ = std::make_unique<RedGhost>(gameConfig.redGhost().STARTING_COORDINATES, gameConfig.redGhost().STARTING_DIRECTION);

    scoreManager_ = std::make_unique<ScoreManager>();

    standardPelletsManager_ = std::make_unique<StandardPelletsManager>(pathPoints_->getStandardPelletPositions());
    standardPelletsModel_ = std::make_unique<StandardPelletsModel>(*standardPelletsManager_);

    powerPelletsManager_ = std::make_unique<PowerPelletsManager>(pathPoints_->getPowerPelletPositions());
    powerPelletsModel_ = std::make_unique<PowerPelletsModel>(*powerPelletsManager_);
}

void Model::reset()
{
    qDebug() << "Resetting model";

    standardPelletsManager_->reset();
    powerPelletsManager_->reset();

    pacman_->reset();
    blueGhost_->reset();
    orangeGhost_->reset();
    purpleGhost_->reset();
    redGhost_->reset();

    scoreManager_->reset();
}
