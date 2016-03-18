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

#ifndef VLCQT_VIDEOFRAMEYUV_H_
#define VLCQT_VIDEOFRAMEYUV_H_

#include <memory>

#include <QtCore/QByteArray>

#include "SharedExportCore.h"

/*!
    \struct VlcVideoFrameYUV VideoFrameYUV.h VLCQtCore/VideoFrameYUV.h
    \ingroup VLCQtCore
    \brief Video YUV frame data container
    \since VLC-Qt 1.1
*/
struct VLCQT_CORE_EXPORT VlcVideoFrameYUV
{
    /*!
        \brief VlcVideoFrame constructor.

        This construction ensures default data is set.
    */
    VlcVideoFrameYUV();

    /*!
        \brief Reset frame to default values
     */
    void clear();

    /*!
        \brief Validate frame
        \return true if frame has size greater than 0 in both dimensions
     */
    bool isValid();


    QByteArray frameBuf  /*!< frame buffer */;

    quint16 width; /*!< frame width */
    quint16 height; /*!< frame height */

    void* yPlane; /*!< pointer to Y plane */
    quint32 yPlaneSize; /*!< Y plane size */

    void* uPlane; /*!< pointer to U plane */
    quint32 uPlaneSize; /*!< Y plane size */

    void* vPlane; /*!< pointer to V plane */
    quint32 vPlaneSize; /*!< Y plane size */
};


/*!
    \brief Clone frame
    \param from frame to clone
 */
std::shared_ptr<VlcVideoFrameYUV> cloneFrame(const std::shared_ptr<VlcVideoFrameYUV> &from);


#endif // VLCQT_VIDEOFRAMEYUV_H_
