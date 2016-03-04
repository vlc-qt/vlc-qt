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
    QStringList args_list;

    QString args = qgetenv("VLC_ARGS");
    if (!args.isEmpty())
        args_list << args.split(" ", QString::SkipEmptyParts);
    else
    {
        args_list << "--intf=dummy"
             << "--no-media-library"
             << "--no-stats"
             << "--no-osd"
             << "--no-loop"
             << "--no-video-title-show"
        #if defined(Q_OS_DARWIN)
             << "--vout=macosx"
        #endif
             << "--drop-late-frames";
    }

    return args_list;
}

bool VlcCommon::setPluginPath(const QString &path)
{
    if (qgetenv("VLC_PLUGIN_PATH").isEmpty()) {
        return qputenv("VLC_PLUGIN_PATH", path.toLocal8Bit());
    }

    return false;
}
