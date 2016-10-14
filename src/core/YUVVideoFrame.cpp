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

#include "core/YUVVideoFrame.h"
#include <stdint.h>

VlcYUVVideoFrame::VlcYUVVideoFrame(unsigned *width,
                                   unsigned *height,
                                   unsigned *pitches,
                                   unsigned *lines)
    : VlcAbstractVideoFrame(3)
{
    uint16_t evenWidth = *width + (*width & 1 ? 1 : 0);
    uint16_t evenHeight = *height + (*height & 1 ? 1 : 0);

    pitches[0] = evenWidth;
    if (pitches[0] % 4)
        pitches[0] += 4 - pitches[0] % 4;
    pitches[1] = evenWidth / 2;
    if (pitches[1] % 4)
        pitches[1] += 4 - pitches[1] % 4;
    pitches[2] = pitches[1];

    lines[0] = evenHeight;
    lines[1] = evenHeight / 2;
    lines[2] = lines[1];

    frameBuffer.resize(pitches[0] * lines[0] + pitches[1] * lines[1] + pitches[2] * lines[2]);

    this->width = evenWidth;
    this->height = evenHeight;

    setPitchesAndLines(pitches, lines);
}

VlcYUVVideoFrame::~VlcYUVVideoFrame() {}

VlcYUVVideoFrame::VlcYUVVideoFrame(const std::shared_ptr<VlcYUVVideoFrame> &frame)
    : VlcAbstractVideoFrame(3)
{
    frameBuffer.resize(frame->frameBuffer.size());

    width = frame->width;
    height = frame->height;

    setPitchesAndLines(frame);
}
