#pragma once

#include "abstract_pellets_model.h"
#include "standard_pellets_manager.h"

class StandardPelletsModel : public AbstractPelletsModel<StandardPelletsManager>
{
    Q_OBJECT

public:
    explicit StandardPelletsModel(const StandardPelletsManager& standardPelletsManager) : AbstractPelletsModel(standardPelletsManager)
    {
        connect(&pelletsManager_, &StandardPelletsManager::resetRequested, this, &StandardPelletsModel::reset);
    }

    void reset() override
    {
        AbstractPelletsModel::reset();
    }
};
