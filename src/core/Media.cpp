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

VlcMedia::VlcMedia(const QUrl &location,
                   VlcInstance *instance)
    : QObject(instance)
{
    // Create a new libvlc media descriptor from location (URL)
    _vlcMedia = libvlc_media_new_location(instance->core(), location.toString().toAscii().data());

    VlcError::errmsg();

    qDebug() << "libvlc" << "Media URL:" << location;
}

VlcMedia::VlcMedia(const QString &localPath,
                   VlcInstance *instance)
    : QObject(instance)
{
    // Create a new libvlc media descriptor from local path
    _vlcMedia = libvlc_media_new_path(instance->core(), localPath.toAscii().data());

    VlcError::errmsg();

    qDebug() << "libvlc" << "Local media path:" << localPath;
}

VlcMedia::VlcMedia(libvlc_media_t *media)
{
    // Create a new libvlc media descriptor from existing one
    _vlcMedia = libvlc_media_duplicate(media);

    VlcError::errmsg();
}

VlcMedia::~VlcMedia()
{
    libvlc_media_release(_vlcMedia);

    VlcError::errmsg();
}

libvlc_media_t *VlcMedia::core()
{
    return _vlcMedia;
}
