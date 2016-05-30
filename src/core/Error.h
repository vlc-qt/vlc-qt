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

#ifndef VLCQT_ERROR_H_
#define VLCQT_ERROR_H_

#include "SharedExportCore.h"

/*!
    \class VlcError Error.h VLCQtCore/Error.h
    \ingroup VLCQtCore
	\brief Error handler

	A basic error handler for VLC-Qt library.
*/
class VLCQT_CORE_EXPORT VlcError
{
public:
    /*!
        \brief A human-readable error message for the last libvlc error in the calling thread.

        The resulting string is valid until another error occurs.
        \return error message (QString)
        \warning There may be no output, if there is no error.
    */
    static QString errmsg();

    /*!
        \brief A human-readable error message displayed into standard output for the last libvlc error in the calling thread.

		The resulting string is valid until another error occurs.
		\warning There may be no output, if there is no error.
	*/
    static void showErrmsg();

    /*!
		\brief Clears the libvlc error status for the current thread.

        This does nothing.

        \deprecated Deprecated since VLC-Qt 1.1, will be removed in 2.0
	*/
    Q_DECL_DEPRECATED static void clearerr();
};

#endif // VLCQT_ERROR_H_
