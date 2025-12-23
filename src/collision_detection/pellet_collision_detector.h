#pragma once

#include "coordinates.h"
#include "utils.h"
#include <QtGlobal>

// Pacman <-> pellet collision using circle overlap test
template<typename T>
class PelletCollisionDetector
{
    static_assert(std::is_integral_v<decltype(T::DIAMETER)>, "Pellet type T must provide integral static constexpr DIAMETER");
    static_assert((T::DIAMETER % 2) == 0, "Pellet DIAMETER must be divisible by 2 (so pellet radius is integer)");

public:
    explicit PelletCollisionDetector(const int pacmanDiameter) : pacmanRadius_(pacmanDiameter / 2), pelletRadius_(T::DIAMETER / 2)
    {
        Q_ASSERT(pacmanDiameter >= 0);
        Q_ASSERT((pacmanDiameter % 2) == 0); // enforce integer radius
    }

    [[nodiscard]] bool checkPacmanCollisionWithPellet(const Coordinates& pacmanCoordinates, const T& pellet) const noexcept
    {
        if (!pellet.isAlive())
        {
            return false;
        }

        return CollisionDetectionUtils::areCirclesOverlapping(pacmanCoordinates, pacmanRadius_, pellet.getCoordinates(), pelletRadius_);
    }

private:
    const int pacmanRadius_;
    const int pelletRadius_;
};
