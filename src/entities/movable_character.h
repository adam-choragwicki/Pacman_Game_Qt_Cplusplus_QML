#pragma once

#include <QTimer>
#include "direction.h"
#include "coordinates.h"

class MovableCharacter : public QObject
{
    Q_OBJECT

signals:
    void changedSignal();

public:
    MovableCharacter(const Coordinates& startingCoordinates, Direction initialDirection, int animationSpeedFactor, int animationPhasesCount);
    ~MovableCharacter() override = 0;

    void advanceAnimation();

    virtual void reset();

    [[nodiscard]] Direction getDirection() const { return direction_; }

    [[nodiscard]] Coordinates getCoordinates() const { return coordinates_; }

    void setNextDirection(const Direction direction) { nextDirection_ = direction; }

    [[nodiscard]] Direction getNextDirection() const { return nextDirection_; }

    [[nodiscard]] bool isMoving() const { return moving_; }

    void setDirection(const Direction direction) { direction_ = direction; }

    void setMoving(const bool moving) { moving_ = moving; }

    void moveInDirection(const Direction& direction);
    void moveTo(const Coordinates& coordinates);

    [[nodiscard]] int getX() const { return getCoordinates().x_; }
    Q_PROPERTY(int x_ READ getX NOTIFY changedSignal)

    [[nodiscard]] int getY() const { return getCoordinates().y_; }
    Q_PROPERTY(int y_ READ getY NOTIFY changedSignal)

    [[nodiscard]] int getDirectionQML() const { return static_cast<int>(direction_); }
    Q_PROPERTY(int directionQML READ getDirectionQML NOTIFY changedSignal)

    [[nodiscard]] int getAnimationPhase() const { return animationPhase_; }
    Q_PROPERTY(int animationPhase READ getAnimationPhase NOTIFY changedSignal)

    [[nodiscard]] int getDiameter() const { return DIAMETER; }
    Q_PROPERTY(int diameter READ getDiameter CONSTANT)

    virtual void changed()
    {
        emit changedSignal();
    }

    static constexpr int DIAMETER = 30;

protected:
    bool moving_{};
    Direction direction_;
    Direction nextDirection_;

    const Coordinates STARTING_COORDINATES;
    const Direction STARTING_DIRECTION;

    const int ANIMATION_SPEED_FACTOR;
    const int ANIMATION_PHASES_COUNT;

    int animationPhase_{};
    bool animationPhaseAscending_ = true;
    int stepCounter_{};

    Coordinates coordinates_;
};
