#pragma once

#include "abstract_pellets_manager.h"
#include "standard_pellet.h"
#include <algorithm>

class StandardPelletsManager : public QObject, public AbstractPelletsManager<StandardPellet>
{
    Q_OBJECT

signals:
    void resetRequested();

public:
    explicit StandardPelletsManager(const std::set<Coordinates>& standardPelletPositions) : AbstractPelletsManager(standardPelletPositions)
    {}

    void reset() override
    {
        AbstractPelletsManager::reset();

        emit resetRequested();
    }

    [[nodiscard]] int getAliveStandardPelletsCount() const
    {
        return static_cast<int>(std::ranges::count_if(getPellets(),
                                                      [](const StandardPellet& standardPellet)
                                                      {
                                                          return standardPellet.isAlive();
                                                      }));
    }
};
