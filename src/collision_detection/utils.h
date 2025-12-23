#pragma once

#include "coordinates.h"

namespace CollisionDetectionUtils
{
    // Exact circle overlap test using integers (radius units)
    // Fast-reject on axis-aligned distance before computing squared distance.
    inline static bool areCirclesOverlapping(const Coordinates& centerA, const int radiusA, const Coordinates& centerB, const int radiusB) noexcept
    {
        Q_ASSERT(radiusA >= 0);
        Q_ASSERT(radiusB >= 0);

        const int radiusSum = radiusA + radiusB;

        const int dx = centerA.x_ - centerB.x_;
        const int dy = centerA.y_ - centerB.y_;

        // Fast axis-aligned reject — cheap (no multiplies)
        if (std::abs(dx) > radiusSum)
        {
            return false;
        }

        if (std::abs(dy) > radiusSum)
        {
            return false;
        }

        // Tight check: squared distance <= radiusSum^2
        return dx * dx + dy * dy <= radiusSum * radiusSum;
    }
}
