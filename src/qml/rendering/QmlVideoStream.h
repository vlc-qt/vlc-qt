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

#ifndef VLCQT_QMLRENDERING_QMLVIDEOSTREAM_H_
#define VLCQT_QMLRENDERING_QMLVIDEOSTREAM_H_

#include "core/VideoStream.h"

class VlcQmlVideoOutput;

class VlcQmlVideoStream : public VlcVideoStream
{
    Q_OBJECT
public:
    explicit VlcQmlVideoStream(QObject* parent = 0);
    ~VlcQmlVideoStream();

    void registerVideoOutput(VlcQmlVideoOutput *output);
    void deregisterVideoOutput(VlcQmlVideoOutput *output);

    QList<VlcQmlVideoOutput *> attachedOutputs() const { return _attachedOutputs; }

private:
    Q_INVOKABLE virtual void frameUpdated();

    QList<VlcQmlVideoOutput *> _attachedOutputs;
};

#endif // VLCQT_QMLRENDERING_QMLVIDEOSTREAM_H_
