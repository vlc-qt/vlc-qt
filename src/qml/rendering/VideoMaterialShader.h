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

#ifndef VLCQT_QMLRENDERING_VIDEOMATERIALSHADER_H_
#define VLCQT_QMLRENDERING_VIDEOMATERIALSHADER_H_

#include <memory>

#include <QtQuick/QSGMaterial>

class VideoMaterialShader : public QSGMaterialShader // LCOV_EXCL_LINE
{
public:
    virtual char const *const *attributeNames() const;
    virtual const char *vertexShader() const;
    virtual const char *fragmentShader() const;
    virtual void initialize();

    virtual void updateState(const RenderState &state,
                             QSGMaterial *newMaterial,
                             QSGMaterial *oldMaterial);

private:
    int _positionMatrixId;
    int _colorMatrixId;
    int _opacityId;
    int _texYId;
    int _texUId;
    int _texVId;
};

#endif // VLCQT_QMLRENDERING_VIDEOMATERIALSHADER_H_
