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

#include <QtGui/QImage>
#include <QtGui/QPainter>

#include "QPainterPainter.h"

QPainterPainter::QPainterPainter() { }

QPainterPainter:: ~QPainterPainter() { }

QList<VideoFrame::Format> QPainterPainter::supportedFormats() const
{
    return QList<VideoFrame::Format>() << VideoFrame::Format_RGB32;
}

void QPainterPainter::init()
{
    _inited = true;
}

void QPainterPainter::paint(QPainter *painter, QRectF target)
{
    // QImage can only handle packed formats.
    if (_frame->planeCount != 1 || _frame->format != VideoFrame::Format_RGB32) {
        painter->drawImage(target, QImage());
    } else {
        painter->drawImage(target,
                           QImage(reinterpret_cast<const uchar *>(_frame->plane[0].constData()),
                                  _frame->width, _frame->height,
                                  QImage::Format_RGB32));
    }
}
