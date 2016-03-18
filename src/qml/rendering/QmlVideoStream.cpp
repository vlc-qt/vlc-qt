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

#include "qml/QmlVideoOutput.h"
#include "qml/rendering/QmlVideoStream.h"

VlcQmlVideoStream::VlcQmlVideoStream(QObject *parent)
    : VlcVideoStream(parent) { }

VlcQmlVideoStream::~VlcQmlVideoStream() { }

void VlcQmlVideoStream::frameUpdated()
{
    // convert to shared pointer to const frame to avoid crash
    std::shared_ptr<const VlcVideoFrameYUV> frame = renderFrame();

    std::for_each(_attachedOutputs.begin(), _attachedOutputs.end(),
                  std::bind2nd(std::mem_fun(&VlcQmlVideoOutput::presentFrame), frame));
}

void VlcQmlVideoStream::registerVideoOutput(VlcQmlVideoOutput *output)
{
    Q_ASSERT(_attachedOutputs.count(output) <= 1);

    if (_attachedOutputs.contains(output))
        return;

    _attachedOutputs.append(output);
}

void VlcQmlVideoStream::deregisterVideoOutput(VlcQmlVideoOutput *output)
{
    Q_ASSERT(_attachedOutputs.count(output) <= 1);

    _attachedOutputs.removeOne(output);
}
