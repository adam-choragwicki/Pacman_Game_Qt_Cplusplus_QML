#include <gtest/gtest.h>
#include <QTest>

#include "entities/ghosts/blue_ghost.h"
#include "entities/ghosts/orange_ghost.h"
#include "entities/ghosts/purple_ghost.h"
#include "entities/ghosts/red_ghost.h"

#include "ghost_timing_manager.h"
#include "game_config.h"

class GhostStartingBoxTest : public ::testing::Test
{
protected:
    static void SetUpTestSuite()
    {
        initializeQCoreApp();
    }

    static void initializeQCoreApp()
    {
        if (!QCoreApplication::instance())
        {
            static int argc = 0;
            static char* argv[] = {nullptr};
            static QCoreApplication app(argc, argv);
        }
    }

    GameConfig gameConfig;
};

TEST_F(GhostStartingBoxTest, RedGhost_LeavesImmediately)
{
    RedGhost ghost(gameConfig.redGhost().STARTING_COORDINATES, gameConfig.redGhost().STARTING_DIRECTION);

    auto* ghostTimingManager = ghost.getGhostTimingManager();

    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox());

    ghostTimingManager->startLeaveStartingBoxTimer();

    QTest::qWait(10);

    EXPECT_TRUE(ghostTimingManager->isItTimeToLeaveStartingBox());
}

TEST_F(GhostStartingBoxTest, PurpleGhost_LeavesAfterOneSecond)
{
    PurpleGhost ghost(gameConfig.purpleGhost().STARTING_COORDINATES, gameConfig.purpleGhost().STARTING_DIRECTION);

    auto* ghostTimingManager = ghost.getGhostTimingManager();

    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox());

    ghostTimingManager->startLeaveStartingBoxTimer();

    QTest::qWait(500);
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Purple ghost left starting box too early (after around 0.5s)";

    QTest::qWait(300); // total ~800ms
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Purple ghost left starting box too early (after around 0.8s)";

    QTest::qWait(400); // total ~1200ms
    EXPECT_TRUE(ghostTimingManager->isItTimeToLeaveStartingBox());
}

TEST_F(GhostStartingBoxTest, OrangeGhost_LeavesAfterTwoSeconds)
{
    OrangeGhost ghost(gameConfig.orangeGhost().STARTING_COORDINATES,gameConfig.orangeGhost().STARTING_DIRECTION);

    auto* ghostTimingManager = ghost.getGhostTimingManager();

    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox());

    ghostTimingManager->startLeaveStartingBoxTimer();

    QTest::qWait(800);
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Orange ghost left starting box too early (after around 0.8s)";

    QTest::qWait(700); // total ~1500ms
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Orange ghost left starting box too early (after around 1.5s)";

    QTest::qWait(800); // total ~2300ms
    EXPECT_TRUE(ghostTimingManager->isItTimeToLeaveStartingBox());
}

TEST_F(GhostStartingBoxTest, BlueGhost_LeavesAfterThreeSeconds)
{
    BlueGhost ghost(gameConfig.blueGhost().STARTING_COORDINATES, gameConfig.blueGhost().STARTING_DIRECTION);

    auto* ghostTimingManager = ghost.getGhostTimingManager();

    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox());

    ghostTimingManager->startLeaveStartingBoxTimer();

    QTest::qWait(1000);
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Blue ghost left starting box too early (after around 1s)";

    QTest::qWait(1000); // total ~2000ms
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Blue ghost left starting box too early (after around 2s)";

    QTest::qWait(500); // total ~2500ms
    EXPECT_FALSE(ghostTimingManager->isItTimeToLeaveStartingBox()) << "Blue ghost left starting box too early (after around 2.5s)";

    QTest::qWait(1200); // total ~3200ms
    EXPECT_TRUE(ghostTimingManager->isItTimeToLeaveStartingBox());
}
