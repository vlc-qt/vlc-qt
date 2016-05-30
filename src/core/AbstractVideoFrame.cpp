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

#include "core/AbstractVideoFrame.h"

VlcAbstractVideoFrame::VlcAbstractVideoFrame(int planeCount)
    : width(0),
      height(0)
{
    planes.resize(planeCount);
    planeSizes.resize(planeCount);
}

VlcAbstractVideoFrame::~VlcAbstractVideoFrame() {}

void VlcAbstractVideoFrame::clear()
{
    width = height = 0;

    size_t planeCount = planes.size();

    planes.clear();
    planeSizes.clear();
    planes.resize(planeCount);
    planeSizes.resize(planeCount);
}

bool VlcAbstractVideoFrame::isValid()
{
    return width > 0 && height > 0;
}

void VlcAbstractVideoFrame::setPitchesAndLines(unsigned *pitches,
                                               unsigned *lines)
{
    for (size_t i = 0; i < planes.size(); i++) {
        if (i > 0)
            planes[i] = planes[i - 1] + planeSizes[i - 1];
        else
            planes[0] = frameBuffer.data();

        planeSizes[i] = pitches[i] * lines[i];
    }
}

void VlcAbstractVideoFrame::setPitchesAndLines(const std::shared_ptr<VlcAbstractVideoFrame> &frame)
{
    for (size_t i = 0; i < planes.size(); i++) {
        if (i > 0)
            planes[i] = planes[i - 1] + planeSizes[i - 1];
        else
            planes[0] = frameBuffer.data();

        planeSizes[i] = frame->planeSizes[i];
    }
}
