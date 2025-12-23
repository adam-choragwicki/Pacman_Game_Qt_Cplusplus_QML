#pragma once

#include "entities/movable_character.h"

class GhostTimingManager;

class AbstractGhost : public MovableCharacter
{
    Q_OBJECT

public:
    AbstractGhost(const Coordinates& coordinates, Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, const QString& color);
    ~AbstractGhost() override = 0;

    void reset() override;
    void respawn();

    void setScared();

    [[nodiscard]] bool isScared() const;

    [[nodiscard]] bool isSlowedDown() const { return isSlowedDown_; }

    [[nodiscard]] GhostTimingManager* getGhostTimingManager() const { return ghostTimingManager_.get(); }

    [[nodiscard]] int getScaredState() const { return static_cast<int>(scaredState_); }
    Q_PROPERTY(int scaredState READ getScaredState NOTIFY changedSignal)

    [[nodiscard]] QString getColor() const { return color_; }

    bool canMoveThisTurn() const; // returns true when the ghost is allowed to perform its movement step this tick.

    void incrementMoveTickCounter() { ++moveTickCounter_; }
    int getMoveTickCounter() const { return moveTickCounter_; }

protected:
    bool isSlowedDown_{};

private:
    enum class ScaredState
    {
        NO_SCARED = 0, SCARED_BLUE = 1, SCARED_WHITE = 2
    } scaredState_;

    static const int ANIMATION_PHASES_COUNT = 2;

    /* Set higher to make animation slower */
    static const int ANIMATION_SPEED_FACTOR = 30;

    std::unique_ptr<GhostTimingManager> ghostTimingManager_;

    QString color_{"NULL"};

    // Per-ghost counter for slowdown gating.
    // When the ghost is slowed (isSlowedDown_ == true) we only allow a movement
    // on every SLOWDOWN_SKIP_TICKS'th call to canMoveThisTurn().
    int moveTickCounter_ = 0;

    static constexpr int SLOWDOWN_SKIP_TICKS = 5;
};
