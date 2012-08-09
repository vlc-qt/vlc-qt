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

#include "core/Common.h"

QStringList VlcCommon::args()
{
    QStringList args;

    args << "--intf=dummy"
         << "--no-media-library"
         << "--no-one-instance"
         << "--no-plugins-cache"
         << "--no-stats"
         << "--no-osd"
         << "--no-loop"
         << "--no-video-title-show"
#if defined(Q_OS_MAC)
         << "--vout=macosx"
#endif
         << "--drop-late-frames";

    return args;
}
