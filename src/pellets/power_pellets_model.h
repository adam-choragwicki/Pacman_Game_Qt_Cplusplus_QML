#pragma once

#include "abstract_pellets_model.h"
#include "power_pellets_manager.h"

class PowerPelletsModel : public AbstractPelletsModel<PowerPelletsManager>
{
    Q_OBJECT

public:
    explicit PowerPelletsModel(const PowerPelletsManager& powerPelletsManager) : AbstractPelletsModel(powerPelletsManager)
    {
        connect(&pelletsManager_, &PowerPelletsManager::resetRequested, this, &PowerPelletsModel::reset);
    }

    void reset() override
    {
        AbstractPelletsModel::reset();
    }
};
