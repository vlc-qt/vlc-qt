/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2010 Tadej Novak <tadej@tano.si>
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

#include "core/Common.h"

QStringList VlcCommon::args()
{
	QStringList args;

	args << "--intf=dummy"
		 << "--no-media-library"
		 << "--reset-plugins-cache"
		 << "--no-stats"
		 << "--no-osd"
#if defined(Q_WS_MAC)
		 << "--vout=macosx"
#endif
		 << "--no-video-title-show";

	return args;
}

QStringList VlcCommon::recorderArgs(const QString &file)
{
	QStringList args;

	args << "--demux"
		 << "dump"
		 << "--demuxdump-file"
		 << file;

	return args;
}
