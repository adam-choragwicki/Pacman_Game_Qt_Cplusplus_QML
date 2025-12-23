#pragma once

#include "abstract_ghost.h"

class OrangeGhost : public AbstractGhost
{
public:
    OrangeGhost(const Coordinates& startingCoordinates, const Direction startingDirection) : AbstractGhost(startingCoordinates, startingDirection, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, "orange") {}

private:
    static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{2};
};
