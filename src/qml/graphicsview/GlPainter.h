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
// Not forward included, because we need platform specific GL typedefs for structs.
#include <QtOpenGL/QGLContext>

#include "AbstractVideoGraphicsPainter.h"
#include "VideoFrame.h"

class GlPainter : public AbstractVideoGraphicsPainter
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
    /** Destructor. */
    virtual ~GlPainter();

    /** \param context the QGLContext to use for this painter. */
    void setContext(QGLContext *context);

    /** Initialize for an RGB32/RGBA frame. */
    void initRgb32();

    /** Initialize for an YV12 frame. */
    void initYv12();

    /** Initalize the color matrix to be used for YUV->RGB color conversion. */
    void initColorMatrix();

    /**
     * Initialize all textures (amount of texture is dependent on what count was
     * decided in the specific init functions.
     */
    void initTextures();

protected:
    GlPainter();

    QGLContext *_context;
    int _textureCount;
    GLuint _textureIds[3];

    GlTextureDescriptor _texDescriptor;
    GlTextureSize _texSize[3];

    QMatrix4x4 _colorMatrix;

    bool _texturesInited;
};

#endif // VLCQT_PHONON_GLPAINTER_H_
