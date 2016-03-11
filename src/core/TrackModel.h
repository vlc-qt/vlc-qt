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

#include "SharedExportCore.h"

/*!
    \class VlcTrackModel TrackModel.h VLCQtCore/TrackModel.h
    \ingroup VLCQtCore
    \brief Track model

    A model for displaying audio, video and other tracks
*/
class VLCQT_CORE_EXPORT VlcTrackModel: public QAbstractListModel // LCOV_EXCL_LINE
{
    Q_OBJECT
    /*!
        \brief Current tracks count
        \see count
        \see countChanged
     */
    Q_PROPERTY(int count READ count NOTIFY countChanged)
public:
    /*!
        \enum Roles
        \brief Model data roles
    */
    enum Roles {
        IdRole = Qt::UserRole + 1,
        TitleRole
    };

    /*!
        \brief VlcTrackModel constructor.
        \param parent parent object
    */
    explicit VlcTrackModel(QObject *parent = 0);

    /*!
        \brief VlcTrackModel constructor.
        \param tracks tracks map
        \param parent parent object
    */
    explicit VlcTrackModel(const QMap<int, QString> &tracks,
                           QObject *parent = 0);

    /*!
        \brief VlcTrackModel constructor.
        \param other another VlcTrackModel instance
    */
    explicit VlcTrackModel(const VlcTrackModel &other);

    /*!
        \brief Get row count
        \param parent parent model index
        \return count
    */
    int rowCount(const QModelIndex &parent) const;

    /*!
        \brief Model role names
        \return role names hash
    */
    QHash<int, QByteArray> roleNames() const;

    /*!
        \brief Read data from model
        \param index model index
        \param role required role
    */
    QVariant data(const QModelIndex &index, int role) const;

    /*!
        \brief Read data from model
        \param row model row
        \param role required role
    */
    QVariant data(const int row, int role) const;


    /*!
        \brief Clear the model
    */
    void clear();

    /*!
        \brief Load tracks into model
        \param data tracks map id-title
    */
    void load(const QMap<int, QString> &data);

    /*!
        \brief Insert track into model
        \param id track id
        \param title track title
    */
    void insert(const int id, const QString &title);

    /*!
        \brief Get tracks count
        \return count
    */
    int count() const;


signals:
    /*!
        \brief Count changed signal
    */
    void countChanged();

private:
    QMap<int, QString> _tracks;
};

Q_DECLARE_METATYPE(VlcTrackModel)

#endif // VLC_TRACK_MODEL_H
