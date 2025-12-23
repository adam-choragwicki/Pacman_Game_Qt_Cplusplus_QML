#pragma once

#include "abstract_ghost.h"

class RedGhost : public AbstractGhost
{
public:
    explicit RedGhost(const Coordinates& startingCoordinates, const Direction startingDirection) : AbstractGhost(startingCoordinates, startingDirection, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, "red") {}

private:
    static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{0};
};
