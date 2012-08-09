/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_MEDIALIST_H_
#define VLCQT_MEDIALIST_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include "Enums.h"

class VlcInstance;
class VlcMedia;

struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;
struct libvlc_media_list_t;

/*!
    \class VlcMediaList Media.h vlc-qt/Media.h
    \brief Media list item

    VlcMediaList holds multiple VlcMedia items to play in sequence.
*/
class VlcMediaList : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcMediaList constructor.

        This constructor creates a new media list instance.

        \param instance main libvlc instance
    */
    explicit VlcMediaList(VlcInstance *instance);

    /*!
        \brief VlcMediaList destructor
    */
    ~VlcMediaList();

    /*!
        \brief libvlc media list item
        \return libvlc media list item (libvlc_media_list_t *)
    */
    libvlc_media_list_t *core();

    /*!
        \brief Add media item to the list
        \param media media item
    */
    void addMedia(VlcMedia *media);

    /*!
        \brief Get media item at selected index
        \param index item position
        \return media item (VlcMedia)
    */
    VlcMedia *at(const int &index);

    /*!
        \brief libvlc media list item
        \return items count (int)
    */
    int count();

    /*!
        \brief Index of media item
        \param media media item
        \return media item index (int)
    */
    int indexOf(VlcMedia *media);

    /*!
        \brief Index of media item (core)
        \param media media item
        \return media item index (int)
    */
    int indexOf(libvlc_media_t *media);

    /*!
        \brief Insert media item at the specific position of the list.
        \param media media item
        \param index item position
    */
    void insertMedia(VlcMedia *media,
                     const int &index);

    /*!
        \brief Remove media item from the specific position of the list.
        \param index item position
    */
    void removeMedia(const int &index);


signals:
    /*!
        \brief Signal sent on item added
        \param libvlc_media_t * item
        \param int index
    */
    void itemAdded(libvlc_media_t *,
                   const int &);

    /*!
        \brief Signal sent when item will be added
        \param libvlc_media_t * item
        \param int index
    */
    void willAddItem(libvlc_media_t *,
                     const int &);

    /*!
        \brief Signal sent on item deleted
        \param libvlc_media_t * item
        \param int index
    */
    void itemDeleted(libvlc_media_t *,
                     const int &);

    /*!
        \brief Signal sent when item will be deleted
        \param libvlc_media_t * item
        \param int index
    */
    void willDeleteItem(libvlc_media_t *,
                        const int &);


private:
    void lock();
    void unlock();

    static void libvlc_callback(const libvlc_event_t *event,
                                void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_list_t * _vlcMediaList;
    libvlc_event_manager_t *_vlcEvents;

    QList<VlcMedia *> _list;
};

#endif // VLCQT_MEDIALIST_H_
