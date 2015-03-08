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

#ifndef VLCQT_PHONON_GLPAINTER_H_
#define VLCQT_PHONON_GLPAINTER_H_

#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLContext>
#include <QtGui/QPainter>

#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        #include <QtGui/QOpenGLFunctions_ES2>
    #else
        #include <QtGui/QOpenGLFunctions_1_1>
    #endif
#else
    #include <QtGui/QOpenGLFunctions>
#endif

#include "core/VideoFrame.h"

class GlPainter
{
    typedef struct {
        GLenum target;
        GLint internalFormat;
        GLenum format;
        GLenum type;
    } GlTextureDescriptor;

    typedef struct {
        GLsizei width;
        GLsizei height;
    } GlTextureSize;

public:
    virtual ~GlPainter();

    void setFrame(const VlcVideoFrame *frame) { _frame = frame; }
    bool inited() const { return _inited; }

    void setContext(QOpenGLContext *context);

    void initColorMatrix();
    void initTextures();
    void initYv12();

protected:
    GlPainter();

    const VlcVideoFrame *_frame;
    bool _inited;

    QOpenGLContext *_context;
    QOpenGLFunctions *_gl;
#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        QOpenGLFunctions_ES2 *_glF;
    #else
        QOpenGLFunctions_1_1 *_glF;
    #endif
#else
    QOpenGLFunctions *_glF;
#endif

    int _textureCount;
    GLuint _textureIds[3];

    GlTextureDescriptor _texDescriptor;
    GlTextureSize _texSize[3];

    QMatrix4x4 _colorMatrix;

    bool _texturesInited;
};

#endif // VLCQT_PHONON_GLPAINTER_H_
