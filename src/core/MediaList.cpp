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

#include <vlc/vlc.h>

#include "core/Error.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/MediaList.h"

VlcMediaList::VlcMediaList(VlcInstance *instance)
    : QObject(instance)
{
    _vlcMediaList = libvlc_media_list_new(instance->core());
    _vlcEvents = libvlc_media_list_event_manager(_vlcMediaList);

    createCoreConnections();

    VlcError::showErrmsg();
}

VlcMediaList::~VlcMediaList()
{
    foreach(VlcMedia *m, _list)
        delete m;

    removeCoreConnections();

    libvlc_media_list_release(_vlcMediaList);

    VlcError::showErrmsg();
}

libvlc_media_list_t *VlcMediaList::core()
{
    return _vlcMediaList;
}

void VlcMediaList::createCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListItemAdded
         << libvlc_MediaListWillAddItem
         << libvlc_MediaListItemDeleted
         << libvlc_MediaListWillDeleteItem;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_attach(_vlcEvents, event, libvlc_callback, this);
    }
}

void VlcMediaList::removeCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaListItemAdded
         << libvlc_MediaListWillAddItem
         << libvlc_MediaListItemDeleted
         << libvlc_MediaListWillDeleteItem;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_detach(_vlcEvents, event, libvlc_callback, this);
    }
}

void VlcMediaList::addMedia(VlcMedia *media)
{
    lock();
    libvlc_media_list_add_media(_vlcMediaList, media->core());
    _list.append(media);
    unlock();

    VlcError::showErrmsg();
}

VlcMedia *VlcMediaList::at(int index)
{
    return _list[index];
}

int VlcMediaList::count()
{
    lock();
    int count = libvlc_media_list_count(_vlcMediaList);
    unlock();

    VlcError::showErrmsg();

    return count;
}

int VlcMediaList::indexOf(VlcMedia *media)
{
    return _list.indexOf(media);
}

int VlcMediaList::indexOf(libvlc_media_t *media)
{
    int index;
    lock();
    index = libvlc_media_list_index_of_item(_vlcMediaList, media);
    unlock();

    VlcError::showErrmsg();

    return index;
}

void VlcMediaList::insertMedia(VlcMedia *media,
                               int index)
{
    lock();
    libvlc_media_list_insert_media(_vlcMediaList, media->core(), index);
    _list.insert(index, media);
    unlock();

    VlcError::showErrmsg();
}

void VlcMediaList::removeMedia(int index)
{
    lock();
    libvlc_media_list_remove_index(_vlcMediaList, index);
    delete _list[index];
    _list.removeAt(index);
    unlock();

    VlcError::showErrmsg();
}

void VlcMediaList::lock()
{
    libvlc_media_list_lock(_vlcMediaList);
}

void VlcMediaList::unlock()
{
    libvlc_media_list_unlock(_vlcMediaList);
}

void VlcMediaList::libvlc_callback(const libvlc_event_t *event,
                               void *data)
{
    VlcMediaList *core = (VlcMediaList *)data;

    switch(event->type)
    {
    case libvlc_MediaListItemAdded:
        emit core->itemAdded(event->u.media_list_item_added.item, event->u.media_list_item_added.index);
        break;
    case libvlc_MediaListWillAddItem:
        emit core->willAddItem(event->u.media_list_will_add_item.item, event->u.media_list_will_add_item.index);
        break;
    case libvlc_MediaListItemDeleted:
        emit core->itemDeleted(event->u.media_list_item_deleted.item, event->u.media_list_item_deleted.index);
        break;
    case libvlc_MediaListWillDeleteItem:
        emit core->willDeleteItem(event->u.media_list_will_delete_item.item, event->u.media_list_will_delete_item.index);
        break;
    default:
        break;
    }
}
