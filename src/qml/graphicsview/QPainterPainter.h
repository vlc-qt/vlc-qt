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

#ifndef VLCQT_PHONON_QPAINTERPAINTER_H_
#define VLCQT_PHONON_QPAINTERPAINTER_H_

#include "AbstractVideoGraphicsPainter.h"

class QPainterPainter : public AbstractVideoGraphicsPainter
{
public:
    QPainterPainter();
    virtual ~QPainterPainter();

    virtual QList<VideoFrame::Format> supportedFormats() const;
    void init();
    void paint(QPainter *painter, QRectF target);
};

#endif // VLCQT_PHONON_QPAINTERPAINTER_H_
