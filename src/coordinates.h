#pragma once

#include "direction.h"
#include <QString>

struct Coordinates
{
    friend std::ostream& operator<<(std::ostream& os, const Coordinates& coordinates);

    Coordinates() = default;
    Coordinates(int x, int y);
    Coordinates operator+(const std::pair<int, int>& coordinates) const;
    Coordinates& operator+=(const Coordinates& coordinates);
    operator QString() const;

    Coordinates shiftInDirection(Direction direction);

    int x_{};
    int y_{};
};

bool operator==(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator!=(const Coordinates& coordinates1, const Coordinates& coordinates2);
bool operator<(const Coordinates& coordinates1, const Coordinates& coordinates2);
