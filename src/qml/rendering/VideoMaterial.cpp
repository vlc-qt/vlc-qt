/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
*
* This file is based on QmlVlc and Phonon multimedia library
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

#include "core/YUVVideoFrame.h"

#include "rendering/VideoMaterial.h"
#include "rendering/VideoMaterialShader.h"

VideoMaterial::VideoMaterial()
    : _frame(0)
{
    memset(_planeTexIds, 0, sizeof(_planeTexIds));
    setFlag(Blending, false);

#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        _glF = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_ES2>();
    #else
        _glF = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_1_3>();
    #endif
        Q_ASSERT(_glF);

        _glF->initializeOpenGLFunctions();
#else
    _glF = QOpenGLContext::currentContext()->functions();
#endif
}

VideoMaterial::~VideoMaterial()
{
    if (_planeTexIds[0] || _planeTexIds[1] || _planeTexIds[2])
        _glF->glDeleteTextures(3, _planeTexIds);
}

QSGMaterialType* VideoMaterial::type() const
{
    static QSGMaterialType theType;
    return &theType;
}

QSGMaterialShader* VideoMaterial::createShader() const
{
    return new VideoMaterialShader;
}

int VideoMaterial::compare(const QSGMaterial *other) const
{
    const VideoMaterial *material = static_cast<const VideoMaterial *>(other);
    const unsigned texCount = sizeof(_planeTexIds) / sizeof(_planeTexIds[0]);

    for (unsigned i = 0; i < texCount; ++i) {
        if (_planeTexIds[i] != material->_planeTexIds[i])
            return _planeTexIds[i] - material->_planeTexIds[i];
    }

    return 0;
}

void VideoMaterial::setFrame(const std::shared_ptr<const VlcYUVVideoFrame> &frame)
{
    _frame = frame;
}

void VideoMaterial::bindPlanes()
{
    if (_planeTexIds[0] == 0 && _planeTexIds[1] == 0 && _planeTexIds[2] == 0)
        _glF->glGenTextures(3, _planeTexIds);

    std::shared_ptr<const VlcYUVVideoFrame> tmpFrame;
    _frame.swap(tmpFrame);

    if (tmpFrame) {
        Q_ASSERT((tmpFrame->width & 1) == 0 && (tmpFrame->height & 1) == 0); // width and height should be even
        const quint16 tw = tmpFrame->width;
        const quint16 th = tmpFrame->height;

        bindPlane(GL_TEXTURE1, _planeTexIds[1], tmpFrame->planes[1], tw / 2, th / 2);
        bindPlane(GL_TEXTURE2, _planeTexIds[2], tmpFrame->planes[2], tw / 2, th / 2);
        bindPlane(GL_TEXTURE0, _planeTexIds[0], tmpFrame->planes[0], tw, th);
    } else {
        bindPlane(GL_TEXTURE1, _planeTexIds[1], 0, 0, 0);
        bindPlane(GL_TEXTURE2, _planeTexIds[2], 0, 0, 0);
        bindPlane(GL_TEXTURE0, _planeTexIds[0], 0, 0, 0);
    }
}

void VideoMaterial::bindPlane(GLenum texUnit,
                              GLuint texId,
                              const void *plane,
                              quint16 width,
                              quint16 height)
{
    _glF->glActiveTexture(texUnit);
    _glF->glBindTexture(GL_TEXTURE_2D, texId);
    if (plane) {
        _glF->glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE,
                           width, height, 0,
                           GL_LUMINANCE, GL_UNSIGNED_BYTE, plane);
        _glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        _glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        _glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        _glF->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
}
