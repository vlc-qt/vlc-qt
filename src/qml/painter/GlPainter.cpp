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

#include "qml/painter/GlPainter.h"

GlPainter::GlPainter()
    : _frame(0),
      _inited(false),
      _context(0),
      _texturesInited(false) { }

GlPainter::~GlPainter() { }

void GlPainter::setContext(QOpenGLContext *context)
{
    _context = context;
}

void GlPainter::initYv12()
{
    Q_ASSERT(_frame->planeCount == 3);
    _textureCount = _frame->planeCount;

    _texDescriptor.target = GL_TEXTURE_2D;
    _texDescriptor.internalFormat = GL_LUMINANCE;
    _texDescriptor.format = GL_LUMINANCE;
    _texDescriptor.type = GL_UNSIGNED_BYTE;
}

void GlPainter::initColorMatrix()
{
    _colorMatrix = QMatrix4x4(1.0, 0.0, 0.0, 0.0,
                               0.0, 1.0, 0.0, 0.0,
                               0.0, 0.0, 1.0, 0.0,
                               0.0, 0.0, 0.0, 1.0);
    QMatrix4x4 colorSpaceMatrix;
    if (_frame->height > 576)
        colorSpaceMatrix =
                QMatrix4x4(
                    1.164383561643836,  0.000000000000000,  1.792741071428571, -0.972945075016308,
                    1.164383561643836, -0.213248614273730, -0.532909328559444,  0.301482665475862,
                    1.164383561643836,  2.112401785714286,  0.000000000000000, -1.133402217873451,
                    0.000000000000000,  0.000000000000000,  0.000000000000000,  1.000000000000000);
    else
        colorSpaceMatrix =
                QMatrix4x4(
                    1.164383561643836,  0.000000000000000,  1.596026785714286, -0.874202217873451,
                    1.164383561643836, -0.391762290094914, -0.812967647237771,  0.531667823499146,
                    1.164383561643836,  2.017232142857142,  0.000000000000000, -1.085630789302022,
                    0.000000000000000,  0.000000000000000,  0.000000000000000,  1.000000000000000);
    _colorMatrix = _colorMatrix * colorSpaceMatrix;
}

void GlPainter::initTextures()
{
    if (!_texturesInited) {
        for (unsigned i = 0; i < _frame->planeCount; ++i) {
            _gl->glBindTexture(_texDescriptor.target, _textureIds[i]);
            _gl->glTexImage2D(_texDescriptor.target,
                         0,
                         _texDescriptor.internalFormat,
                         _frame->visiblePitch[i],
                         _frame->visibleLines[i],
                         0,
                         _texDescriptor.format,
                         _texDescriptor.type,
                         0);
            // Scale appropriately so we can change to target geometry without
            // much hassle.
            _gl->glTexParameterf(_texDescriptor.target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            _gl->glTexParameterf(_texDescriptor.target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            _gl->glTexParameterf(_texDescriptor.target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            _gl->glTexParameterf(_texDescriptor.target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            _texturesInited = true;
        }
    }

    for (unsigned i = 0; i < _frame->planeCount; ++i) {
        _gl->glBindTexture(_texDescriptor.target, _textureIds[i]);

// Based on vlc/src/video_output/opengl.c
#ifndef GL_UNPACK_ROW_LENGTH
#define ALIGN(x, y) (((x) + ((y) - 1)) & ~((y) - 1))
        int dst_pitch = ALIGN(_frame->visiblePitch[i], 4);
        char *new_plane = (char *) malloc(dst_pitch * _frame->visibleLines[i]);
        const char *source = _frame->plane[i].data();
        char *destination = new_plane;
        for (int y = 0; y < _frame->visibleLines[i]; y++) {
            memcpy(destination, source, _frame->visiblePitch[i]);
            source += _frame->pitch[i];
            destination += dst_pitch;
        }

        _gl->glTexSubImage2D(_texDescriptor.target, 0,
                                    0, 0,
                                    _frame->visiblePitch[i],
                                    _frame->visibleLines[i],
                                    _texDescriptor.format,
                                    _texDescriptor.type,
                                    new_plane);
        free(new_plane);
#else
        _gl->glPixelStorei(GL_UNPACK_ROW_LENGTH, _frame->pitch[i]);
        _gl->glTexSubImage2D(_texDescriptor.target, 0,
                        0, 0,
                        _frame->visiblePitch[i],
                        _frame->visibleLines[i],
                        _texDescriptor.format,
                        _texDescriptor.type,
                        _frame->plane[i].data());
        _gl->glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // reset to default
#endif
    }
}
