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

#include "core/VideoFrameYUV.h"

VlcVideoFrameYUV::VlcVideoFrameYUV()
    : width(0),
      height(0),
      yPlane(0),
      yPlaneSize(0),
      uPlane(0),
      uPlaneSize(0),
      vPlane(0),
      vPlaneSize(0) { }

void VlcVideoFrameYUV::clear()
{
    width = height = 0;
    yPlane = uPlane = vPlane = 0;
    yPlaneSize = uPlaneSize = vPlaneSize = 0;
}

bool VlcVideoFrameYUV::isValid()
{
    return width > 0 && height > 0;
}

std::shared_ptr<VlcVideoFrameYUV> cloneFrame(const std::shared_ptr<VlcVideoFrameYUV> &from)
{
    std::shared_ptr<VlcVideoFrameYUV> newFrame(new VlcVideoFrameYUV);

    newFrame->frameBuf.resize(from->frameBuf.size());

    newFrame->width = from->width;
    newFrame->height = from->height;

    char* fb = newFrame->frameBuf.data();

    newFrame->yPlane = fb;
    newFrame->yPlaneSize = from->yPlaneSize;

    newFrame->uPlane = fb + newFrame->yPlaneSize;
    newFrame->uPlaneSize = from->uPlaneSize;

    newFrame->vPlane = fb + newFrame->yPlaneSize + newFrame->uPlaneSize;
    newFrame->vPlaneSize = from->vPlaneSize;

    return newFrame;
}
