/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Error.h: libvlc error handler
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

#ifndef VLCQT_ERROR_H_
#define VLCQT_ERROR_H_

#include <vlc/vlc.h>

/*!
	\class VlcError Error.h vlc-qt/Error.h
	\brief Error handler

	A basic error handler for VLC-Qt library.
*/
class VlcError
{
public:
	/*!
		\brief A human-readable error message for the last libvlc error in the calling thread.

		The resulting string is valid until another error occurs.
		\warning There may be no output, if there is no error.
	*/
	static void errmsg();

	/*!
		\brief Clears the libvlc error status for the current thread.

		This is optional. By default, the error status is automatically overriden when a new error occurs, and destroyed when the thread exits.
	*/
	static void clearerr();
};

#endif // VLCQT_ERROR_H_
