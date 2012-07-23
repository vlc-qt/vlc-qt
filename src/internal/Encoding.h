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

#ifndef VLCQT_ENCODING_H_
#define VLCQT_ENCODING_H_

#include <QtCore/QString>
#include <QtCore/QStringList>

namespace VlcInternal
{
	namespace Encoding
	{
		QString fromUtf8(const QString &string);
		const char *fromUtf8C(const QString &string);
	}
}

#endif // VLCQT_ENCODING_H_
