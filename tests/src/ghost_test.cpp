#include "common_test_fixture.h"
#include "game_config.h"
#include "entities/ghosts/blue_ghost.h"
#include "entities/ghosts/orange_ghost.h"
#include "entities/ghosts/purple_ghost.h"
#include "entities/ghosts/red_ghost.h"
#include "entities/pacman.h"
#include "ghost_movement_manager.h"

class GhostTest : public CommonTestFixture
{
protected:
    GameConfig gameConfig;
};

TEST_F(GhostTest, CreateBlueGhost)
{
    const BlueGhost blueGhost{gameConfig.blueGhost().STARTING_COORDINATES, gameConfig.blueGhost().STARTING_DIRECTION};
    EXPECT_EQ(blueGhost.getCoordinates(), Coordinates(265, 318));
}

TEST_F(GhostTest, CreateOrangeGhost)
{
    const OrangeGhost orangeGhost{gameConfig.orangeGhost().STARTING_COORDINATES, gameConfig.orangeGhost().STARTING_DIRECTION};
    EXPECT_EQ(orangeGhost.getCoordinates(), Coordinates(349, 318));
}

TEST_F(GhostTest, CreatePurpleGhost)
{
    const PurpleGhost purpleGhost{gameConfig.purpleGhost().STARTING_COORDINATES, gameConfig.purpleGhost().STARTING_DIRECTION};
    EXPECT_EQ(purpleGhost.getCoordinates(), Coordinates(307, 318));
}

TEST_F(GhostTest, CreateRedGhost)
{
    const RedGhost redGhost{gameConfig.redGhost().STARTING_COORDINATES, gameConfig.redGhost().STARTING_DIRECTION};
    EXPECT_EQ(redGhost.getCoordinates(), Coordinates(307, 252));
}

TEST_F(GhostTest, ResetGhost)
{
    GameConfig gameConfig;

    Pacman pacman(gameConfig.pacman().STARTING_COORDINATES, gameConfig.pacman().STARTING_DIRECTION);

    BlueGhost blueGhost{gameConfig.blueGhost().STARTING_COORDINATES, gameConfig.blueGhost().STARTING_DIRECTION};
    OrangeGhost orangeGhost{gameConfig.orangeGhost().STARTING_COORDINATES, gameConfig.orangeGhost().STARTING_DIRECTION};
    PurpleGhost purpleGhost{gameConfig.purpleGhost().STARTING_COORDINATES, gameConfig.purpleGhost().STARTING_DIRECTION};
    RedGhost redGhost{gameConfig.redGhost().STARTING_COORDINATES, gameConfig.redGhost().STARTING_DIRECTION};

    GhostMovementManager ghostMovementManager;

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    ghostMovementManager.processMove(blueGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(orangeGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(purpleGhost, pacman.getCoordinates(), pathPoints_);
    ghostMovementManager.processMove(redGhost, pacman.getCoordinates(), pathPoints_);

    blueGhost.reset();
    orangeGhost.reset();
    purpleGhost.reset();
    redGhost.reset();

    EXPECT_EQ(blueGhost.getCoordinates(), Coordinates(265, 318));
    EXPECT_EQ(orangeGhost.getCoordinates(), Coordinates(349, 318));
    EXPECT_EQ(purpleGhost.getCoordinates(), Coordinates(307, 318));
    EXPECT_EQ(redGhost.getCoordinates(), Coordinates(307, 252));
}
