#pragma once

#include "coordinates.h"

class AbstractPellet
{
public:
    explicit AbstractPellet(const Coordinates& coordinates, const int diameter) : x_(coordinates.x_), y_(coordinates.y_), width_(diameter), height_(diameter)
    {
        alive_ = true;
    }

    [[nodiscard]] int x() const
    {
        return x_;
    }

    [[nodiscard]] int y() const
    {
        return y_;
    }

    [[nodiscard]] int width() const
    {
        return width_;
    }

    [[nodiscard]] int height() const
    {
        return height_;
    }

    [[nodiscard]] bool isAlive() const
    {
        return alive_;
    }

    void destroy()
    {
        alive_ = false;
    }

    void setAlive(const bool alive)
    {
        alive_ = alive;
    }

    [[nodiscard]] Coordinates getCoordinates() const
    {
        return Coordinates{x_, y_};
    }

protected:
    int x_;
    int y_;
    int width_;
    int height_;
    bool alive_;
};
