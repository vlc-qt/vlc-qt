/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "core/TrackModel.h"

VlcTrackModel::VlcTrackModel(QObject *parent):
    QAbstractListModel(parent)
{
}

VlcTrackModel::VlcTrackModel(const QMap<int, QString> &tracks, QObject *parent):
    QAbstractListModel(parent),
    _tracks(tracks)
{
}

VlcTrackModel::VlcTrackModel(const VlcTrackModel &other)
{
    _tracks = other._tracks;
}

int VlcTrackModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return _tracks.count();
}

QHash<int, QByteArray> VlcTrackModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(IdRole, "id");
    roles.insert(TitleRole, "title");
    return roles;
}

QVariant VlcTrackModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    return data(index.row(), role);
}

QVariant VlcTrackModel::data(const int row, int role) const
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

void VlcTrackModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, _tracks.count() - 1);
    _tracks.clear();
    endRemoveRows();
    emit countChanged();
}

void VlcTrackModel::load(const QMap<int, QString> &data)
{
    QMapIterator<int, QString> i(data);
    while(i.hasNext())
    {
        i.next();
        insert(i.key(), i.value());
    }
}

void VlcTrackModel::insert(const int id, const QString &title)
{
    beginInsertRows(QModelIndex(), _tracks.size(), _tracks.size());
    _tracks.insert(id, title);
    endInsertRows();
    emit countChanged();
}

int VlcTrackModel::count() const
{
    return rowCount(QModelIndex());
}
