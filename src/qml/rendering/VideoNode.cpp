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

#include "rendering/VideoNode.h"

VideoNode::VideoNode()
    : _geometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4)
{
    setGeometry(&_geometry);
    setMaterial(&_material);
}

void VideoNode::setFrame(const std::shared_ptr<const VlcVideoFrameYUV> &frame)
{
    _material.setFrame(frame);
    markDirty(QSGNode::DirtyMaterial);
}

void VideoNode::setRect(const QRectF &rect,
                        const QRectF &sourceRect)
{
    QSGGeometry::updateTexturedRectGeometry(&_geometry, rect, sourceRect);
    markDirty(QSGNode::DirtyGeometry);
}
