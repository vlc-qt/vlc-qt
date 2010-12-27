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

#ifndef VLCQT_COMMON_H_
#define VLCQT_COMMON_H_

#include <QtCore/QString>
#include <QtCore/QStringList>

/*!
	\namespace VlcCommon Common.h vlc-qt/Common.h
	\brief Common functions
*/
namespace VlcCommon
{
	/*!
		\brief Common libvlc arguments

		\param global use global VLC settings or not (bool)
		\return libvlc arguments (QStringList)
	*/
	QStringList args(const bool &global = false);

	/*!
		\brief Recorder libvlc arguments

		\param file full output file path (QString)
		\return libvlc arguments (QStringList)
	*/
	QStringList recorderArgs(const QString &file);
};

#endif // VLCQT_COMMON_H_
