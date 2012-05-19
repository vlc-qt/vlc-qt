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

#include <QtCore/QDebug>

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
    libvlc_media_list_release(_vlcMediaList);

    VlcError::errmsg();
}

libvlc_media_list_t *VlcMediaList::core()
{
    return _vlcMediaList;
}

int VlcMediaList::count()
{
    lock();
    int count = libvlc_media_list_count(_vlcMediaList);
    unlock();

    VlcError::errmsg();

    return count;
}

void VlcMediaList::addMedia(VlcMedia *media)
{
    lock();
    libvlc_media_list_add_media(_vlcMediaList, media->core());
    unlock();

    VlcError::errmsg();
}

void VlcMediaList::insertMedia(VlcMedia *media,
                               const int &index)
{
    lock();
    libvlc_media_list_insert_media(_vlcMediaList, media->core(), index);
    unlock();

    VlcError::errmsg();
}

void VlcMediaList::removeMedia(const int &index)
{
    lock();
    libvlc_media_list_remove_index(_vlcMediaList, index);
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
