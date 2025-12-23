#pragma once

#include "abstract_ghost.h"

class BlueGhost : public AbstractGhost
{
public:
    BlueGhost(const Coordinates& startingCoordinates, const Direction startingDirection) : AbstractGhost(startingCoordinates, startingDirection, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, "blue") {}

private:
    static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{3};
};
