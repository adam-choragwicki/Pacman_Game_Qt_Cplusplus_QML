#pragma once

#include "path_points.h"

#include "entities/pacman.h"
#include "entities/ghosts/blue_ghost.h"
#include "entities/ghosts/orange_ghost.h"
#include "entities/ghosts/purple_ghost.h"
#include "entities/ghosts/red_ghost.h"

#include "score_manager.h"

#include "game_config.h"

#include "pellets/standard_pellets_model.h"
#include "pellets/power_pellets_model.h"

class Model
{
public:
    explicit Model(const GameConfig& gameConfig);
    void reset();

    [[nodiscard]] Pacman& getPacman() const { return *pacman_; }

    [[nodiscard]] BlueGhost& getBlueGhost() const { return *blueGhost_; }
    [[nodiscard]] OrangeGhost& getOrangeGhost() const { return *orangeGhost_; }
    [[nodiscard]] PurpleGhost& getPurpleGhost() const { return *purpleGhost_; }
    [[nodiscard]] RedGhost& getRedGhost() const { return *redGhost_; }

    [[nodiscard]] ScoreManager& getScoreManager() const { return *scoreManager_; }

    [[nodiscard]] const PathPoints& getPathPoints() const { return *pathPoints_; }

    Q_PROPERTY(QObject* standardPelletsModel READ getStandardPelletsModel CONSTANT)
    [[nodiscard]] StandardPelletsModel& getStandardPelletsModel() const { return *standardPelletsModel_; }
    [[nodiscard]] StandardPelletsManager& getStandardPelletsManager() const { return *standardPelletsManager_; }

    Q_PROPERTY(QObject* powerPelletsModel READ getPowerPelletsModel CONSTANT)
    [[nodiscard]] PowerPelletsModel& getPowerPelletsModel() const { return *powerPelletsModel_; }
    [[nodiscard]] PowerPelletsManager& getPowerPelletsManager() const { return *powerPelletsManager_; }

private:
    std::unique_ptr<PathPoints> pathPoints_;

    std::unique_ptr<Pacman> pacman_;
    std::unique_ptr<BlueGhost> blueGhost_;
    std::unique_ptr<OrangeGhost> orangeGhost_;
    std::unique_ptr<PurpleGhost> purpleGhost_;
    std::unique_ptr<RedGhost> redGhost_;

    std::unique_ptr<ScoreManager> scoreManager_;

    std::unique_ptr<StandardPelletsManager> standardPelletsManager_;
    std::unique_ptr<StandardPelletsModel> standardPelletsModel_;

    std::unique_ptr<PowerPelletsManager> powerPelletsManager_;
    std::unique_ptr<PowerPelletsModel> powerPelletsModel_;
};
