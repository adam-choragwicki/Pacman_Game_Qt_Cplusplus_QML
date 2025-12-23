#pragma once

#include "movable_character.h"

class Pacman : public MovableCharacter
{
public:
    Pacman(const Coordinates& startingCoordinates, const Direction startingDirection) : MovableCharacter(startingCoordinates, startingDirection, ANIMATION_SPEED_FACTOR, ANIMATION_PHASES_COUNT)
    {}

private:
    static constexpr int ANIMATION_PHASES_COUNT = 4;
    static constexpr int ANIMATION_SPEED_FACTOR = 10; // set higher to make animation slower
};
