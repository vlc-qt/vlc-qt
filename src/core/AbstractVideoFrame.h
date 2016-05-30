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

#ifndef VLCQT_ABSTRACTVIDEOFRAME_H_
#define VLCQT_ABSTRACTVIDEOFRAME_H_

#include <memory>
#include <vector>

#include <QtCore/QByteArray>

#include "Enums.h"
#include "SharedExportCore.h"

/*!
    \struct VlcAbstractVideoFrame AbstractVideoFrame.h VLCQtCore/AbstractVideoFrame.h
    \ingroup VLCQtCore
    \brief Abstract video frame data container
    \since VLC-Qt 1.1
*/
struct VLCQT_CORE_EXPORT VlcAbstractVideoFrame {
    /*!
        \brief VlcVideoFrame constructor.
        \param planeCount
    */
    VlcAbstractVideoFrame(int planeCount);
    virtual ~VlcAbstractVideoFrame() = 0;

    /*!
        \brief Reset frame to default values
     */
    void clear();

    /*!
        \brief Validate frame
        \return true if frame has size greater than 0 in both dimensions
     */
    bool isValid();

    /*!
        \brief Set pitches and lines helper
        \param pitches
        \param lines
     */
    void setPitchesAndLines(unsigned *pitches,
                            unsigned *lines);

    /*!
        \brief Set pitches and lines helper
        \param frame frame to copy from
     */
    void setPitchesAndLines(const std::shared_ptr<VlcAbstractVideoFrame> &frame);

    QByteArray frameBuffer; /*!< frame buffer */

    quint16 width;  /*!< frame width */
    quint16 height; /*!< frame height */

    std::vector<char *> planes;      /*!< planes */
    std::vector<quint32> planeSizes; /*!< plane sizes */
};

#endif // VLCQT_ABSTRACTVIDEOFRAME_H_
