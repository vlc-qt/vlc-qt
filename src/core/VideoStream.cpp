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
#include "core/YUVVideoFrame.h"

VlcVideoStream::VlcVideoStream(Vlc::RenderFormat format,
                               QObject *parent)
    : QObject(parent),
      _format(format) { }

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
    switch (_format)
    {
    case Vlc::YUVFormat:
        qstrcpy(chroma, "I420");
        _frames.emplace(_frames.end(), new VlcYUVVideoFrame(width, height, pitches, lines));
        return 3;
    }

    return -1; // LCOV_EXCL_LINE
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

    std::shared_ptr<VlcAbstractVideoFrame>& frame = *frameIt;
    for (size_t i = 0; i < frame->planes.size(); i++) {
        planes[i] = frame->planes[i];
    }

    _lockedFrames.emplace_back(frame);

    return reinterpret_cast<void *>(frameIt - _frames.begin());
}

void VlcVideoStream::unlockCallback(void *picture, void * const * planes)
{
    Q_UNUSED(planes)

    auto frameNo = reinterpret_cast<decltype(_frames)::size_type>(picture);
    if (frameNo >= _frames.size()) {
        return; // LCOV_EXCL_LINE
    }

    std::shared_ptr<VlcAbstractVideoFrame>& frame = _frames[frameNo];

    _lockedFrames.erase(std::find(_lockedFrames.begin(), _lockedFrames.end(), frame));
}

void VlcVideoStream::displayCallback(void *picture)
{
    auto frameNo = reinterpret_cast<decltype(_frames)::size_type>(picture);
    if (frameNo >= _frames.size()) {
        Q_ASSERT(false);
        return; // LCOV_EXCL_LINE
    }

    std::shared_ptr<VlcAbstractVideoFrame>& frame = _frames[frameNo];

    _renderFrame = frame;

    QMetaObject::invokeMethod(this, "frameUpdated");
}

std::shared_ptr<VlcAbstractVideoFrame> VlcVideoStream::cloneFrame(std::shared_ptr<VlcAbstractVideoFrame> frame)
{
    switch (_format)
    {
    case Vlc::YUVFormat:
        std::shared_ptr<VlcYUVVideoFrame> from = std::dynamic_pointer_cast<VlcYUVVideoFrame>(frame);
        if (from) {
            return std::make_shared<VlcYUVVideoFrame>(from);
        }
    }

    return 0; // LCOV_EXCL_LINE
}
