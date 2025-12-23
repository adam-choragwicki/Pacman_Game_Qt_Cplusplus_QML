#pragma once

#include "abstract_pellets_manager.h"
#include "power_pellet.h"

class PowerPelletsManager : public QObject, public AbstractPelletsManager<PowerPellet>
{
    Q_OBJECT

signals:
    void resetRequested();

public:
    explicit PowerPelletsManager(const std::set<Coordinates>& powerPelletPositions) : AbstractPelletsManager(powerPelletPositions)
    {}

    void reset() override
    {
        AbstractPelletsManager::reset();

        emit resetRequested();
    }
};
