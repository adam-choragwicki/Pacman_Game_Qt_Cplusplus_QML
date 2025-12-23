#include "movable_character.h"

MovableCharacter::MovableCharacter(const Coordinates& startingCoordinates, const Direction initialDirection, const int animationSpeedFactor, const int animationPhasesCount)
    : direction_(initialDirection),
      nextDirection_(initialDirection),
      STARTING_COORDINATES(startingCoordinates),
      STARTING_DIRECTION(initialDirection),
      ANIMATION_SPEED_FACTOR(animationSpeedFactor),
      ANIMATION_PHASES_COUNT(animationPhasesCount),
      coordinates_(startingCoordinates)
{
    MovableCharacter::reset();
}

MovableCharacter::~MovableCharacter() = default;

void MovableCharacter::reset()
{
    moving_ = false;
    animationPhase_ = 0;
    animationPhaseAscending_ = true;
    stepCounter_ = 0;

    direction_ = STARTING_DIRECTION;
    nextDirection_ = direction_;

    coordinates_ = Coordinates{STARTING_COORDINATES.x_, STARTING_COORDINATES.y_};

    emit changedSignal();
}

void MovableCharacter::moveInDirection(const Direction& direction)
{
    switch(direction)
    {
        case Direction::LEFT:
            --coordinates_.x_;
            break;

        case Direction::RIGHT:
            ++coordinates_.x_;
            break;

        case Direction::UP:
            --coordinates_.y_;
            break;

        case Direction::DOWN:
            ++coordinates_.y_;
            break;
    }
}

void MovableCharacter::moveTo(const Coordinates& coordinates)
{
    coordinates_ = coordinates;
}

void MovableCharacter::advanceAnimation()
{
    if (moving_)
    {
        ++stepCounter_;

        if (stepCounter_ >= ANIMATION_SPEED_FACTOR)
        {
            stepCounter_ = 0;

            if (animationPhaseAscending_)
            {
                ++animationPhase_;
                if (animationPhase_ == ANIMATION_PHASES_COUNT - 1)
                {
                    animationPhaseAscending_ = false;
                }
            }
            else
            {
                --animationPhase_;
                if (animationPhase_ == 0)
                {
                    animationPhaseAscending_ = true;
                }
            }
        }
    }
}
