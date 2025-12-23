#pragma once

#include "entities/pacman.h"
#include "abstract_movement_manager.h"

class PacmanMovementManager : public AbstractMovementManager
{
public:
    void processMove(Pacman& pacman, const PathPoints& pathPoints)
    {
        AbstractMovementManager::processMove(pacman, pathPoints);
    }
};
