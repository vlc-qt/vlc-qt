#include "TracksModel.h"

TracksModel::TracksModel(QObject *parent):
    QAbstractListModel(parent)
{
}

TracksModel::TracksModel(const QMap<int, QString> &tracks, QObject *parent):
    QAbstractListModel(parent),
    _tracks(tracks)
{
}

TracksModel::TracksModel(const TracksModel &other)
{
    _tracks = other._tracks;
}

int TracksModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return _tracks.count();
}

QHash<int, QByteArray> TracksModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, "id");
    roles.insert(TitleRole, "title");
    return roles;
}

QVariant TracksModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return data(index.row(), role);
}

QVariant TracksModel::data(const int row, int role) const
{
    if (row > (_tracks.count() - 1))
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
    case TitleRole:
        return QVariant::fromValue(_tracks.value(_tracks.keys().at(row)));
    case IdRole:
        return QVariant::fromValue(_tracks.keys().at(row));
    case Qt::DecorationRole:
    default:
        return QVariant();
    }
}

void TracksModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, _tracks.count() - 1);
    _tracks.clear();
    endRemoveRows();
    emit countChanged();
}

void TracksModel::load(const QMap<int, QString> &data)
{
    QMapIterator<int, QString> i(data);
    while(i.hasNext())
    {
        i.next();
        insert(i.key(), i.value());
    }
}

void TracksModel::insert(const int id, const QString &title)
{
    beginInsertRows(QModelIndex(), _tracks.size(), _tracks.size());
    _tracks.insert(id, title);
    endInsertRows();
    emit countChanged();
}

int TracksModel::count() const
{
    return rowCount(QModelIndex());
}
