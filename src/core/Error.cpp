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

#include <QtCore/QDebug>
#include <vlc/vlc.h>

#include "core/Error.h"

QString VlcError::errmsg()
{
    QString error;
    if(libvlc_errmsg()) {
        error = QString::fromUtf8(libvlc_errmsg());
        libvlc_clearerr();
    }

    return error;
}

void VlcError::showErrmsg()
{
	// Outputs libvlc error message if there is any
    QString error = errmsg();
    if(!error.isEmpty()) {
        qWarning() << "libvlc" << "Error:" << error;
	}
}
