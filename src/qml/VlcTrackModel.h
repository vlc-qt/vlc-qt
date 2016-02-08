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

#ifndef VLC_TRACK_MODEL_H
#define VLC_TRACK_MODEL_H

#include <QAbstractListModel>

class VlcTrackModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole
    };

    explicit VlcTrackModel(QObject *parent = 0);
    explicit VlcTrackModel(const QMap<int, QString> &tracks, QObject *parent = 0);
    explicit VlcTrackModel(const VlcTrackModel &other);

    int rowCount(const QModelIndex &parent) const;
    QHash<int, QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant data(const int row, int role) const;

    void clear();
    void load(const QMap<int, QString> &data);
    void insert(const int id, const QString &title);
    int count() const;
private:
    QMap<int, QString> _tracks;
signals:
    void countChanged();
};
Q_DECLARE_METATYPE(VlcTrackModel)
#endif // VLC_TRACK_MODEL_H
