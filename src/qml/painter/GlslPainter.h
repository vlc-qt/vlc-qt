/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
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

#ifndef VLCQT_PHONON_GLSLPAINTER_H_
#define VLCQT_PHONON_GLSLPAINTER_H_

#include <QtCore/QRectF>
#include <QtQuick/QQuickWindow>

#if !defined(Q_OS_WIN32)
    #include <QtCore/QTime>
#endif

#include "qml/painter/GlPainter.h"

class QGLShaderProgram;
class QPainter;
class QQuickWindow;

struct VideoFrame;

class GlslPainter : public GlPainter
{
public:
    GlslPainter();
    virtual ~GlslPainter();

    void init();
    void paint(QPainter *painter,
               QRectF target,
               QQuickWindow *window);

private:
    QGLShaderProgram *_program;

#if !defined(Q_OS_WIN32)
    void calculateFPS();
    void addFPSOverlay();

    struct FPS {
        FPS() : value(0),
            imagedValue(0),
            frames(0),
            img(32, 32, QImage::Format_ARGB32) { }

        qreal value;
        qreal imagedValue;
        quint64 frames;
        QTime lastTime;
        QImage img;
    };

    struct FPS _fps;
#endif
};

#endif // VLCQT_PHONON_GLSLPAINTER_H_
