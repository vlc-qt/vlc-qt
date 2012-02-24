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

VlcMedia::VlcMedia(const QString &location,
                   const bool &localFile,
                   VlcInstance *instance)
    : QObject(instance)
{
    initMedia(location, localFile, instance);
}

VlcMedia::VlcMedia(const QString &location,
                   VlcInstance *instance)
    : QObject(instance)
{
    initMedia(location, false, instance);
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

void VlcMedia::initMedia(const QString &location,
                         const bool &localFile,
                         VlcInstance *instance)
{
    QString l = location;
#if defined(Q_WS_WIN)
    if (localFile)
        l.replace("/", "\\");
#endif

    // Create a new libvlc media descriptor from location
    if (localFile)
        _vlcMedia = libvlc_media_new_path(instance->core(), l.toAscii().data());
    else
        _vlcMedia = libvlc_media_new_location(instance->core(), l.toAscii().data());

    VlcError::errmsg();

    qDebug() << "libvlc" << "Media:" << location << "Local:" << localFile;
}
