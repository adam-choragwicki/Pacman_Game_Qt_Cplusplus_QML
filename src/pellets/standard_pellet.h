#pragma once

#include "abstract_pellet.h"

class StandardPellet : public AbstractPellet
{
public:
    explicit StandardPellet(const Coordinates& coordinates) : AbstractPellet(coordinates, DIAMETER)
    {}

    static constexpr int DIAMETER = 8;
};
