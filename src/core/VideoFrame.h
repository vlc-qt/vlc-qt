/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2012 Harald Sitter <sitter@kde.org>
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

#ifndef VLCQT_VIDEOFRAME_H_
#define VLCQT_VIDEOFRAME_H_

#include <QtCore/QByteArray>

#include "SharedExportCore.h"

struct VLCQT_CORE_EXPORT VideoFrame {
    VideoFrame() : width(0), height(0)
    {
        for (int i = 0; i < 4; ++i) {
            pitch[i] = 0;
            visiblePitch[i] = 0;
            lines[i] = 0;
            visibleLines[i] = 0;
        }
    }

    unsigned int width;
    unsigned int height;

    unsigned int planeCount;

    QByteArray plane[4];

    int pitch[4];
    int visiblePitch[4];
    int lines[4];
    int visibleLines[4];
};

#endif // VLCQT_VIDEOFRAME_H_
