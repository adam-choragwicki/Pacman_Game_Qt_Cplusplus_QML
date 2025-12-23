#include "ghost_movement_manager.h"
#include <QRandomGenerator>

bool GhostMovementManager::isGhostInsideStartingBox(const AbstractGhost& ghost)
{
    constexpr int STARTING_BOX_LEFT_EDGE_X = 209;
    constexpr int STARTING_BOX_RIGHT_EDGE_X = 406;
    constexpr int STARTING_BOX_TOP_EDGE_Y = 252;
    constexpr int STARTING_BOX_BOTTOM_EDGE_Y = 384;

    const Coordinates coordinates = ghost.getCoordinates();

    return (coordinates.x_ > STARTING_BOX_LEFT_EDGE_X && coordinates.x_ < STARTING_BOX_RIGHT_EDGE_X) && (coordinates.y_ > STARTING_BOX_TOP_EDGE_Y && coordinates.y_ < STARTING_BOX_BOTTOM_EDGE_Y);
}

void GhostMovementManager::processMove(AbstractGhost& ghost, const Coordinates& pacmanCoordinates, const PathPoints& pathPoints)
{
    basicMovementAI(ghost, pacmanCoordinates);
    AbstractMovementManager::processMove(ghost, pathPoints);
}

void GhostMovementManager::basicMovementAI(AbstractGhost& ghost, const Coordinates& pacmanCoordinates)
{
    const int GHOST_X = ghost.getCoordinates().x_;
    const int GHOST_Y = ghost.getCoordinates().y_;

    const int PACMAN_X = pacmanCoordinates.x_;
    const int PACMAN_Y = pacmanCoordinates.y_;

    const Direction direction = ghost.getDirection();

    if (ghost.isMoving())
    {
        if ((direction == Direction::RIGHT && GHOST_Y < PACMAN_Y) || (direction == Direction::LEFT && GHOST_Y > PACMAN_Y))
        {
            if (direction == Direction::LEFT && GHOST_Y > PACMAN_Y)
            {
                ghost.setNextDirection(Direction::UP);
            }
            else if (direction == Direction::RIGHT && GHOST_Y < PACMAN_Y)
            {
                ghost.setNextDirection(Direction::DOWN);
            }
        }
        else if ((direction == Direction::DOWN && GHOST_X < PACMAN_X) || (direction == Direction::UP && GHOST_X > PACMAN_X))
        {
            if (direction == Direction::UP && GHOST_X > PACMAN_X)
            {
                ghost.setNextDirection(Direction::LEFT);
            }
            else if (direction == Direction::DOWN && GHOST_X < PACMAN_X)
            {
                ghost.setNextDirection(Direction::RIGHT);
            }
        }
    }
    else
    {
        // pick a random direction from the container
        ghost.setDirection(ALL_DIRECTIONS[QRandomGenerator::global()->bounded(DIRECTIONS_COUNT)]);
    }
}

void GhostMovementManager::moveUpAndDownInsideStartingBox(AbstractGhost& ghost)
{
    constexpr int CENTER_Y = 318;
    constexpr int MAX_VERTICAL_MOVEMENT_OFFSET = 15;
    constexpr int MIN_Y_AFTER_OFFSET = CENTER_Y - MAX_VERTICAL_MOVEMENT_OFFSET;
    constexpr int MAX_Y_AFTER_OFFSET = CENTER_Y + MAX_VERTICAL_MOVEMENT_OFFSET;

    const Coordinates ghostCoordinates_ = ghost.getCoordinates();
    const Direction ghostDirection = ghost.getDirection();

    if (ghostCoordinates_.y_ == MIN_Y_AFTER_OFFSET || ghostCoordinates_.y_ == MAX_Y_AFTER_OFFSET)
    {
        if (ghostDirection == Direction::UP)
        {
            ghost.setDirection(Direction::DOWN);
        }
        else if (ghostDirection == Direction::DOWN)
        {
            ghost.setDirection(Direction::UP);
        }
        else
        {
            qFatal("Unsupported direction inside starting box. Only UP/DOWN is allowed");
        }
    }

    ghost.moveInDirection(ghost.getDirection());
}

void GhostMovementManager::moveOutOfStartingBox(AbstractGhost& ghost)
{
    const Coordinates ghostCoordinates = ghost.getCoordinates();

    if (constexpr int STARTING_BOX_CENTER_X = 307; ghostCoordinates.x_ > STARTING_BOX_CENTER_X)
    {
        ghost.moveInDirection(Direction::LEFT);
    }
    else if (ghostCoordinates.x_ < STARTING_BOX_CENTER_X)
    {
        ghost.moveInDirection(Direction::RIGHT);
    }
    else
    {
        ghost.moveInDirection(Direction::UP);
    }
}
