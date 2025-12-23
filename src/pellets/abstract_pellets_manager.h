#pragma once

#include "coordinates.h"
#include <set>
#include <vector>

template<typename T>
class AbstractPelletsManager
{
public:
    explicit AbstractPelletsManager(const std::set<Coordinates>& pelletPositions)
    {
        createPellets(pelletPositions);
    }

    virtual ~AbstractPelletsManager() = default;

    virtual void reset()
    {
        for (T& pellet: pellets_)
        {
            pellet.setAlive(true);
        }
    }

    const std::vector<T>& getPellets() const
    {
        return pellets_;
    }

    std::vector<T>& getPellets()
    {
        return pellets_;
    }

private:
    void createPellets(const std::set<Coordinates>& pelletPositions)
    {
        pellets_.reserve(pelletPositions.size());

        for (const auto& coordinates: pelletPositions)
        {
            pellets_.emplace_back(coordinates);
        }
    }

    std::vector<T> pellets_;
};
