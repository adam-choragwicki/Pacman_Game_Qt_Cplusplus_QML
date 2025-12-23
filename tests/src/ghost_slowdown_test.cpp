#include <gtest/gtest.h>
#include "entities/ghosts/abstract_ghost.h"

class TestGhost final : public AbstractGhost
{
public:
    TestGhost() : AbstractGhost(Coordinates{0, 0}, Direction::LEFT, std::chrono::seconds{2}, "test")
    {}
};

TEST(GhostSlowdownTest, NotSlowed_AlwaysMoves)
{
    TestGhost ghost;

    for (int i = 0; i < 20; ++i)
    {
        EXPECT_TRUE(ghost.canMoveThisTurn());
        ghost.incrementMoveTickCounter();
    }
}

TEST(GhostSlowdownTest, Slowed_MovesEveryNthTick)
{
    TestGhost ghost;
    ghost.setScared(); // enables slowdown

    // Tick 0 -> movement allowed
    EXPECT_TRUE(ghost.canMoveThisTurn());
    ghost.incrementMoveTickCounter();

    // Ticks 1–4 -> movement blocked
    for (int i = 1; i < 5; ++i)
    {
        EXPECT_FALSE(ghost.canMoveThisTurn()) << "Tick " << i << " should be blocked";
        ghost.incrementMoveTickCounter();
    }

    // Tick 5 -> movement allowed again
    EXPECT_TRUE(ghost.canMoveThisTurn());
    ghost.incrementMoveTickCounter();
}

TEST(GhostSlowdownTest, Reset_ClearsSlowdownAndCounter)
{
    TestGhost ghost;
    ghost.setScared();

    // Advance some ticks
    for (int i = 0; i < 3; ++i)
    {
        ghost.incrementMoveTickCounter();
    }

    ghost.reset();

    // After reset: not slowed, should always move
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_TRUE(ghost.canMoveThisTurn());
        ghost.incrementMoveTickCounter();
    }
}
