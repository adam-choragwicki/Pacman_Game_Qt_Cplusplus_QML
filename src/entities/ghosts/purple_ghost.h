#pragma once

#include "abstract_ghost.h"

class PurpleGhost : public AbstractGhost
{
public:
    explicit PurpleGhost(const Coordinates& startingCoordinates, const Direction startingDirection) : AbstractGhost(startingCoordinates, startingDirection, MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT, "purple") {}

private:
    static constexpr std::chrono::seconds MOVE_OUT_OF_THE_STARTING_BOX_TIMEOUT{1};
};
