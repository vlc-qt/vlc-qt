/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
*
* This file is based on QmlVlc library
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

#ifndef VLCQT_YUVVIDEOFRAME_H_
#define VLCQT_YUVVIDEOFRAME_H_

#include "AbstractVideoFrame.h"
#include "SharedExportCore.h"

/*!
    \struct VlcYUVVideoFrame YUVVideoFrame.h VLCQtCore/YUVVideoFrame.h
    \ingroup VLCQtCore
    \brief Video YUV frame data container
    \since VLC-Qt 1.1
*/
struct VLCQT_CORE_EXPORT VlcYUVVideoFrame : VlcAbstractVideoFrame
{
    /*!
        \brief VlcVideoFrame constructor.
        This construction ensures data is set and containers prepared.
        \param width
        \param height
        \param pitches
        \param lines
    */
    VlcYUVVideoFrame(unsigned *width,
                     unsigned *height,
                     unsigned *pitches,
                     unsigned *lines);

    /*!
        \brief VlcVideoFrame constructor.
        This construction copies an existing frame into a new one.
        \param frame existing shared pointer to a frame
    */
    VlcYUVVideoFrame(const std::shared_ptr<VlcYUVVideoFrame> &frame);

    ~VlcYUVVideoFrame();
};


#endif // VLCQT_YUVVIDEOFRAME_H_
