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

#include <functional>

#include "core/VideoStream.h"

VlcVideoStream::VlcVideoStream(QObject *parent)
    : QObject(parent) { }

VlcVideoStream::~VlcVideoStream()
{
    if (_player) {
        unsetCallbacks(_player);
    }
}

void VlcVideoStream::init(VlcMediaPlayer *player)
{
    _player = player;

    setCallbacks(_player);
}

void VlcVideoStream::deinit()
{
    unsetCallbacks(_player);

    _player = 0;
}

unsigned VlcVideoStream::formatCallback(char *chroma,
                                        unsigned *width,
                                        unsigned *height,
                                        unsigned *pitches,
                                        unsigned *lines)
{
    qstrcpy(chroma, "I420");

    uint16_t evenWidth = *width + (*width & 1 ? 1 : 0);
    uint16_t evenHeight = *height + (*height & 1 ? 1 : 0);

    pitches[0] = evenWidth; if (pitches[0] % 4) pitches[0] += 4 - pitches[0] % 4;
    pitches[1] = evenWidth / 2; if (pitches[1] % 4) pitches[1] += 4 - pitches[1] % 4;
    pitches[2] = pitches[1];

    lines[0] = evenHeight;
    lines[1] = evenHeight / 2;
    lines[2] = lines[1];

    std::shared_ptr<VlcVideoFrameYUV>& frame = *_frames.emplace(_frames.end(), new VlcVideoFrameYUV);

    frame->frameBuf.resize(pitches[0] * lines[0] + pitches[1] * lines[1] + pitches[2] * lines[2]);

    frame->width = evenWidth;
    frame->height = evenHeight;

    char* fb = frame->frameBuf.data();

    frame->yPlane = fb;
    frame->yPlaneSize = pitches[0] * lines[0];

    frame->uPlane = fb + frame->yPlaneSize;
    frame->uPlaneSize = pitches[1] * lines[1];

    frame->vPlane = fb + frame->yPlaneSize + frame->uPlaneSize;
    frame->vPlaneSize = pitches[2] * lines[2];

    return 3;
}

void VlcVideoStream::formatCleanUpCallback()
{
    _renderFrame.reset();
    _lockedFrames.clear();
    _frames.clear();

    QMetaObject::invokeMethod(this, "frameUpdated");
}

void* VlcVideoStream::lockCallback(void **planes)
{
    auto frameIt = _frames.begin();
    for ( ; frameIt != _frames.end() && frameIt->use_count() > 1; ++frameIt);

    if (frameIt == _frames.end())
        frameIt = _frames.emplace(_frames.end(), cloneFrame(_frames.front()));

    std::shared_ptr<VlcVideoFrameYUV>& frame = *frameIt;
    planes[0] = frame->yPlane;
    planes[1] = frame->uPlane;
    planes[2] = frame->vPlane;

    _lockedFrames.emplace_back(frame);

    return reinterpret_cast<void *>(frameIt - _frames.begin());
}

void VlcVideoStream::unlockCallback(void *picture, void * const * planes)
{
    Q_UNUSED(planes)

    auto frameNo = reinterpret_cast<decltype(_frames)::size_type>(picture);
    if (frameNo >= _frames.size()) {
        return;
    }

    std::shared_ptr<VlcVideoFrameYUV>& frame = _frames[frameNo];

    _lockedFrames.erase(std::find(_lockedFrames.begin(), _lockedFrames.end(), frame));
}

void VlcVideoStream::displayCallback(void *picture)
{
    auto frameNo = reinterpret_cast<decltype(_frames)::size_type>(picture);
    if (frameNo >= _frames.size()) {
        Q_ASSERT(false);
        return;
    }

    std::shared_ptr<VlcVideoFrameYUV>& frame = _frames[frameNo];

    _renderFrame = frame;

    QMetaObject::invokeMethod(this, "frameUpdated");
}
