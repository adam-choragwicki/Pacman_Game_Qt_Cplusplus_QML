#pragma once

template<typename T>
AbstractPelletsModel<T>::AbstractPelletsModel(const T& pelletsManager) : pelletsManager_(pelletsManager)
{}

template<typename T>
void AbstractPelletsModel<T>::reset()
{
    beginResetModel();
    endResetModel();
}

template<typename T>
int AbstractPelletsModel<T>::rowCount(const QModelIndex&) const
{
    return static_cast<int>(pelletsManager_.getPellets().size());
}

template<typename T>
QVariant AbstractPelletsModel<T>::data(const QModelIndex& index, const int role) const
{
    const auto& pellet = pelletsManager_.getPellets().at(index.row());

    if (!index.isValid())
    {
        qFatal() << "Invalid index";
    }

    switch (role)
    {
        case XRole: return pellet.x();
        case YRole: return pellet.y();
        case WidthRole: return pellet.width();
        case HeightRole: return pellet.height();
        case AliveRole: return pellet.isAlive();
    }

    return {};
}

template<typename T>
QHash<int, QByteArray> AbstractPelletsModel<T>::roleNames() const
{
    return {
        {XRole, "xRole"}, {YRole, "yRole"}, {WidthRole, "widthRole"}, {HeightRole, "heightRole"}, {AliveRole, "aliveRole"}
    };
}

template<typename T>
void AbstractPelletsModel<T>::pelletChanged(const size_t index)
{
    const QModelIndex idx = createIndex(static_cast<int>(index), 0);
    emit dataChanged(idx, idx, {AliveRole});
}
