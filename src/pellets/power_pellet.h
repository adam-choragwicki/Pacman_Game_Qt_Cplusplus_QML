#pragma once

#include "abstract_pellet.h"

class PowerPellet : public AbstractPellet
{
public:
    explicit PowerPellet(const Coordinates& coordinates) : AbstractPellet(coordinates, DIAMETER)
    {}

    static constexpr int DIAMETER = 16;
};
