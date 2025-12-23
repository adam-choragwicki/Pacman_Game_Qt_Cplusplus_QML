#pragma once

#include <QAbstractListModel>

template<typename T>
class AbstractPelletsModel : public QAbstractListModel
{
public:
    enum Roles { XRole = Qt::UserRole + 1, YRole, WidthRole, HeightRole, AliveRole };

    explicit AbstractPelletsModel(const T& pelletsManager);

    virtual void reset();

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
    void pelletChanged(size_t index);

protected:
    const T& pelletsManager_;
};

#include "abstract_pellets_model_impl.h"
