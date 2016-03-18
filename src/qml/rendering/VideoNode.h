/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
*
* This file is based on QmlVlc and Phonon multimedia library
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

#ifndef VLCQT_QMLRENDERING_VIDEONODE_H_
#define VLCQT_QMLRENDERING_VIDEONODE_H_

#include <memory>

#include <QtQuick/QSGGeometryNode>

#include "rendering/VideoMaterial.h"

class VideoNode : public QSGGeometryNode
{
public:
    VideoNode();

    void setFrame(const std::shared_ptr<const VlcVideoFrameYUV> &frame);
    void setRect(const QRectF &rect,
                 const QRectF &sourceRect);

private:
    QSGGeometry _geometry;
    VideoMaterial _material;
};

#endif // VLCQT_QMLRENDERING_VIDEONODE_H_
