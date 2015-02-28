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

#ifndef VLCQT_COMMON_H_
#define VLCQT_COMMON_H_

#include <QtCore/QString>
#include <QtCore/QStringList>

#include "SharedExportCore.h"

/*!
	\namespace VlcCommon Common.h vlc-qt/Common.h
	\brief Common functions
*/
namespace VlcCommon
{
	/*!
		\brief Common libvlc arguments
		\return libvlc arguments (QStringList)
	*/
    VLCQT_CORE_EXPORT QStringList args();

    /*!
        \brief Set plugin path
        \param path plugin path (QString)
        \return success status
    */
    VLCQT_CORE_EXPORT bool setPluginPath(const QString &path);
}

#endif // VLCQT_COMMON_H_
