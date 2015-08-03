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

#ifndef VLCQT_VIDEODELEGATE_H_
#define VLCQT_VIDEODELEGATE_H_

#include <QtCore/QObject>
#include <QtGui/qwindowdefs.h>

#include "SharedExportCore.h"

class VlcMediaPlayer;

/*!
    \class VlcVideoDelegate VideoDelegate.h VLCQtCore/VideoDelegate.h
    \brief Video delegate

    This is a helper class, to separate core from display.
*/
class VLCQT_CORE_EXPORT VlcVideoDelegate
{
public:
    /*!
        \brief VlcVideoDelegate constructor
    */
    VlcVideoDelegate() { }

    /*!
        \brief VlcVideoDelegate destructor
    */
    virtual ~VlcVideoDelegate() { }

    /*!
        \brief Request new video frame.

        Request new video frame and its widget ID to set it in the instance.
        \return widget ID (WId)
        \sa VlcMediaPlayer::VlcMediaPlayer()
    */
    virtual WId request() = 0;

    /*!
        \brief Release current video frame.
    */
    virtual void release() = 0;
};

#endif // VLCQT_VIDEODELEGATE_H_
