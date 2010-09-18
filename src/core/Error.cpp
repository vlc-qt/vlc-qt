/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Error.cpp: libvlc error handler
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#include "Error.h"

#include <QtCore/QDebug>

void VlcError::errmsg()
{
	// Outputs libvlc error message if there is any
	if(libvlc_errmsg()) {
		qDebug() << "libvlc" << "Error:" << libvlc_errmsg();
		clearerr();
	}
}

void VlcError::clearerr()
{
	// Clears libvlc error message
	libvlc_clearerr();
}
