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

#include "core/Enums.h"

QStringList Vlc::audioCodec()
{
    QStringList list;
    list << "none"
         << "mpga"
         << "mp3"
         << "mp4a"
         << "vorb"
         << "flac";

    return list;
}

QStringList Vlc::audioOutput()
{
    QStringList list;

    list << "default";

    return list;
}

QStringList Vlc::audioOutputHuman()
{
    QStringList list;

    list << "default";

    return list;
}

QStringList Vlc::deinterlacing()
{
    QStringList list;
    list << ""
         << "discard"
         << "blend"
         << "man"
         << "bob"
         << "linear"
         << "x";

    return list;
}

QStringList Vlc::mux()
{
    QStringList list;
    list << "ts"
         << "ps"
         << "mp4"
         << "ogg"
         << "avi";

    return list;
}

QStringList Vlc::ratio()
{
    QStringList list;
    list << ""
         << "16:9"
         << "16:10"
         << "185:100"
         << "221:100"
         << "235:100"
         << "239:100"
         << "4:3"
         << "5:4"
         << "5:3"
         << "1:1";

    return list;
}

QStringList Vlc::ratioHuman()
{
    QStringList list;
    list << ""
         << "16:9"
         << "16:10"
         << "1.85:1"
         << "2.21:1"
         << "2.35:1"
         << "2.39:1"
         << "4:3"
         << "5:4"
         << "5:3"
         << "1:1";

    return list;
}

QList<float> Vlc::scale()
{
    QList<float> list;
    list << 0
         << 1.05
         << 1.1
         << 1.2
         << 1.3
         << 1.4
         << 1.5
         << 1.6
         << 1.7
         << 1.8
         << 1.9
         << 2.0;

    return list;
}

QStringList Vlc::videoCodec()
{
    QStringList list;
    list << "none"
         << "mpgv"
         << "mp4v"
         << "x264"
         << "theora";

    return list;
}

QStringList Vlc::videoOutput()
{
    QStringList list;

#if defined(Q_OS_LINUX)
    list << "x11"
         << "xvideo"
         << "glx";
#elif defined(Q_OS_WIN)
    list << "directx"
         << "direct3d"
         << "opengl";
#endif

    list << "default";

    return list;
}

QStringList Vlc::videoOutputHuman()
{
    QStringList list;

#if defined(Q_OS_LINUX)
    list << "X11"
         << "XVideo"
         << "OpenGL";
#elif defined(Q_OS_WIN)
    list << "DirectX"
         << "Direct3D"
         << "OpenGL";
#endif

    list << "default";

    return list;
}

