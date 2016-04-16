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

#ifndef VLCQT_QMLRENDERING_VIDEOMATERIAL_H_
#define VLCQT_QMLRENDERING_VIDEOMATERIAL_H_

#include <memory>

#include <QtQuick/QSGMaterial>
#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        #include <QtGui/QOpenGLFunctions_ES2>
    #else
        #include <QtGui/QOpenGLFunctions_1_3>
    #endif
#else
    #include <QtGui/QOpenGLFunctions>
#endif

struct VlcYUVVideoFrame;

class VideoMaterial : public QSGMaterial
{
public:
    VideoMaterial();
    ~VideoMaterial();

    virtual QSGMaterialType *type() const;
    virtual QSGMaterialShader *createShader() const;
    virtual int compare(const QSGMaterial *other) const;

    void setFrame(const std::shared_ptr<const VlcYUVVideoFrame> &frame);

    void bindPlanes();

private:
    void bindPlane(GLenum texUnit,
                   GLuint texId,
                   const void *plane,
                   quint16 width,
                   quint16 height);

private:
#if QT_VERSION < 0x050300
    #if defined(QT_OPENGL_ES_2)
        QOpenGLFunctions_ES2 *_glF;
    #else
        QOpenGLFunctions_1_3 *_glF;
    #endif
#else
    QOpenGLFunctions *_glF;
#endif

    std::shared_ptr<const VlcYUVVideoFrame> _frame;
    GLuint _planeTexIds[3];
};

#endif // VLCQT_QMLRENDERING_VIDEOMATERIAL_H_
