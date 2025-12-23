#include "entities/ghosts/abstract_ghost.h"
#include "ghost_timing_manager.h"

AbstractGhost::AbstractGhost(const Coordinates& coordinates, const Direction initialDirection, const std::chrono::seconds& moveOutOfTheStartingBoxTimeout, const QString& color)
    : MovableCharacter(coordinates, initialDirection, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT), color_(color)
{
    ghostTimingManager_ = std::make_unique<GhostTimingManager>(moveOutOfTheStartingBoxTimeout);

    MovableCharacter::reset();
    scaredState_ = ScaredState::NO_SCARED;
    isSlowedDown_ = false;
    moveTickCounter_ = 0;
}

AbstractGhost::~AbstractGhost() = default;

void AbstractGhost::reset()
{
    ghostTimingManager_->reset();
    scaredState_ = ScaredState::NO_SCARED;
    isSlowedDown_ = false;
    moveTickCounter_ = 0;

    MovableCharacter::reset(); // this has to be the last one because it emits a signal
}

void AbstractGhost::respawn()
{
    reset();
    ghostTimingManager_->setTimeToLeaveStartingBox();
}

bool AbstractGhost::isScared() const
{
    return scaredState_ != ScaredState::NO_SCARED;
}

void AbstractGhost::setScared()
{
    scaredState_ = ScaredState::SCARED_BLUE;
    isSlowedDown_ = true;
    moveTickCounter_ = 0; // restart slowdown counter

    connect(&ghostTimingManager_->getScaredBlueStateTimer(), &QTimer::timeout, [this]()
    {
        scaredState_ = ScaredState::SCARED_WHITE;

        connect(&ghostTimingManager_->getScaredWhiteStateTimer(), &QTimer::timeout, [this]()
        {
            scaredState_ = ScaredState::NO_SCARED;
            isSlowedDown_ = false;
            moveTickCounter_ = 0;
        });

        ghostTimingManager_->startScaredWhiteTimer();
    });

    ghostTimingManager_->startScaredBlueTimer();
}

bool AbstractGhost::canMoveThisTurn() const
{
    if (isSlowedDown_)
    {
        // if slowed, allow movement only on every SLOWDOWN_SKIP_TICKS-th call.
        return moveTickCounter_ % SLOWDOWN_SKIP_TICKS == 0;
    }

    // if not slowed, always allow move
    return true;
}
