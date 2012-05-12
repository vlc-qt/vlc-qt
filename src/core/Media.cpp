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
    _currentLocation = location;
    QString l = location;
#if defined(Q_OS_WIN32)
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

QString VlcMedia::currentLocation() const
{
    return _currentLocation;
}

QString VlcMedia::record(const QString &name,
                         const QString &path,
                         const Vlc::Mux &mux,
                         const bool &duplicate)
{
    QString option1, option2, parameters;
    QString l = path + "/" + name;
#if defined(Q_OS_WIN32)
    l.replace("/", "\\");
#endif

    parameters = "std{access=file,mux=%1,dst='%2'}}";
    parameters = parameters.arg(Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    if (duplicate) {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    } else {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::errmsg();

    return l + "." + Vlc::mux()[mux];
}

QString VlcMedia::record(const QString &name,
                         const QString &path,
                         const Vlc::Mux &mux,
                         const Vlc::AudioCodec &audioCodec,
                         const Vlc::VideoCodec &videoCodec,
                         const bool &duplicate)
{
    QString option1, option2, parameters;
    QString l = path + "/" + name;
#if defined(Q_OS_WIN32)
    l.replace("/", "\\");
#endif

    parameters = "transcode{vcodec=%1,acodec=%2}:std{access=file,mux=%3,dst='%4'}}";
    parameters = parameters.arg(Vlc::videoCodec()[videoCodec], Vlc::audioCodec()[audioCodec], Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    if (duplicate) {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    } else {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::errmsg();

    return l + "." + Vlc::mux()[mux];
}

QString VlcMedia::record(const QString &name,
                         const QString &path,
                         const Vlc::Mux &mux,
                         const Vlc::AudioCodec &audioCodec,
                         const Vlc::VideoCodec &videoCodec,
                         const int &bitrate,
                         const int &fps,
                         const int &scale,
                         const bool &duplicate)
{
    QString option1, option2, parameters;
    QString l = path + "/" + name;
#if defined(Q_OS_WIN32)
    l.replace("/", "\\");
#endif

    parameters = "transcode{vcodec=%1,vb=%2,fps=%3,scale=%4,acodec=%5}:std{access=file,mux=%6,dst='%7'}}";
    parameters = parameters.arg(Vlc::videoCodec()[videoCodec], QString::number(bitrate), QString::number(fps), QString::number(scale), Vlc::audioCodec()[audioCodec], Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    if (duplicate) {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    } else {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::errmsg();

    return l + "." + Vlc::mux()[mux];
}

void VlcMedia::setOption(const QString &option)
{
    libvlc_media_add_option(_vlcMedia, option.toAscii().data());

    VlcError::errmsg();
}

void VlcMedia::setOptions(const QStringList &options)
{
    foreach(QString option, options) {
        libvlc_media_add_option(_vlcMedia, option.toAscii().data());
    }

    VlcError::errmsg();
}
