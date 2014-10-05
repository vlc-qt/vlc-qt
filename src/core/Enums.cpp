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

#include "core/Enums.h"

Vlc::Vlc(QObject *parent)
    : QObject(parent) { }

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
         << "x"
         << "yadif"
         << "yadif2x"
         << "phosphor"
         << "ivtc";

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

QSizeF Vlc::ratioSize(const Vlc::Ratio &ratio)
{
    switch(ratio)
    {
        default:
        case Vlc::Original:
            return QSizeF(0,0);
            break;
        case Vlc::R_16_9:
            return QSizeF(16,9);
            break;
        case Vlc::R_16_10:
            return QSizeF(16,10);
            break;
        case Vlc::R_185_100:
            return QSizeF(185,100);
            break;
        case Vlc::R_221_100:
            return QSizeF(221,100);
            break;
        case Vlc::R_235_100:
            return QSizeF(235,100);
            break;
        case Vlc::R_239_100:
            return QSizeF(239,100);
            break;
        case Vlc::R_4_3:
            return QSizeF(4,3);
            break;
        case Vlc::R_5_4:
            return QSizeF(5,4);
            break;
        case Vlc::R_5_3:
            return QSizeF(5,3);
            break;
        case Vlc::R_1_1:
            return QSizeF(1,1);
            break;
    }

    return QSizeF(0,0);
}

QList<float> Vlc::scale()
{
    QList<float> list;
    list << (float) 0
         << (float) 1.05
         << (float) 1.1
         << (float) 1.2
         << (float) 1.3
         << (float) 1.4
         << (float) 1.5
         << (float) 1.6
         << (float) 1.7
         << (float) 1.8
         << (float) 1.9
         << (float) 2.0;

    return list;
}

QStringList Vlc::videoCodec()
{
    QStringList list;
    list << "none"
         << "mpgv"
         << "mp4v"
         << "h264"
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
#elif defined(Q_OS_WIN32)
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
#elif defined(Q_OS_WIN32)
    list << "DirectX"
         << "Direct3D"
         << "OpenGL";
#endif

    list << "default";

    return list;
}
