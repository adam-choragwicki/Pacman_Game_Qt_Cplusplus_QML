#pragma once

#include "entities/pacman.h"
#include "entities/ghosts/abstract_ghost.h"
#include "utils.h"
#include <QtGlobal>

// Pacman <-> Ghost collision using circle overlap test (pacman is an ideal circle, ghosts can be approximated as circles)
class GhostCollisionDetector
{
public:
    GhostCollisionDetector(const int pacmanDiameter, const int ghostDiameter) : pacmanRadius_(pacmanDiameter / 2), ghostRadius_(ghostDiameter / 2)
    {
        Q_ASSERT(pacmanDiameter >= 0);
        Q_ASSERT(ghostDiameter >= 0);
        Q_ASSERT(pacmanDiameter % 2 == 0);
        Q_ASSERT(ghostDiameter % 2 == 0);
    }

    [[nodiscard]] bool checkPacmanCollisionWithGhost(const Pacman& pacman, const AbstractGhost& ghost) const noexcept
    {
        return CollisionDetectionUtils::areCirclesOverlapping(pacman.getCoordinates(), pacmanRadius_, ghost.getCoordinates(), ghostRadius_);
    }

private:
    const int pacmanRadius_;
    const int ghostRadius_;
};
