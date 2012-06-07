/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
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

    VlcError::errmsg();
}

VlcMediaList::~VlcMediaList()
{
    foreach(VlcMedia *m, _list)
        delete m;

    libvlc_media_list_release(_vlcMediaList);

    VlcError::errmsg();
}

VlcMedia* VlcMediaList::operator[] (int i) const
{
    return _list.at(i);
}

libvlc_media_list_t *VlcMediaList::core()
{
    return _vlcMediaList;
}

void VlcMediaList::addMedia(VlcMedia *media)
{
    lock();
    libvlc_media_list_add_media(_vlcMediaList, media->core());
    _list.append(media);
    unlock();

    VlcError::errmsg();
}

VlcMedia *VlcMediaList::at(const int &index)
{
    return _list[index];
}

int VlcMediaList::count()
{
    lock();
    int count = libvlc_media_list_count(_vlcMediaList);
    unlock();

    VlcError::errmsg();

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

    VlcError::errmsg();

    return index;
}

void VlcMediaList::insertMedia(VlcMedia *media,
                               const int &index)
{
    lock();
    libvlc_media_list_insert_media(_vlcMediaList, media->core(), index);
    _list.insert(index, media);
    unlock();

    VlcError::errmsg();
}

void VlcMediaList::removeMedia(const int &index)
{
    lock();
    libvlc_media_list_remove_index(_vlcMediaList, index);
    delete _list[index];
    _list.removeAt(index);
    unlock();

    VlcError::errmsg();
}

void VlcMediaList::lock()
{
    libvlc_media_list_lock(_vlcMediaList);
}

void VlcMediaList::unlock()
{
    libvlc_media_list_unlock(_vlcMediaList);
}
