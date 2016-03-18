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

#include "rendering/VideoMaterial.h"
#include "rendering/VideoMaterialShader.h"

char const * const *VideoMaterialShader::attributeNames() const
{
    static const char *names[] = {
        "targetVertex",
        "textureCoordinates",
        0
    };
    return names;
}

const char *VideoMaterialShader::vertexShader() const
{
    return
        "attribute highp vec4 targetVertex;"
        "attribute highp vec2 textureCoordinates;"
        "uniform highp mat4 positionMatrix;"
        "varying highp vec2 textureCoord;"
        "void main(void)"
        "{"
        "    gl_Position = positionMatrix * targetVertex;"
        "    textureCoord = textureCoordinates;"
        "}";
}

const char *VideoMaterialShader::fragmentShader() const
{
    return
        "uniform sampler2D texY;"
        "uniform sampler2D texU;"
        "uniform sampler2D texV;"
        "uniform mediump mat4 colorMatrix;"
        "varying highp vec2 textureCoord;"
        "uniform lowp float opacity;"
        "void main(void)"
        "{"
        "    highp vec4 color = vec4("
        "           texture2D(texY, textureCoord.st).r,"
        "           texture2D(texU, textureCoord.st).r,"
        "           texture2D(texV, textureCoord.st).r,"
        "           1.0);"
        "    gl_FragColor = colorMatrix * color * opacity;"
        "}";
}

void VideoMaterialShader::initialize()
{
    _positionMatrixId = program()->uniformLocation("positionMatrix");
    _colorMatrixId = program()->uniformLocation("colorMatrix");
    _opacityId = program()->uniformLocation("opacity");
    _texYId = program()->uniformLocation("texY");
    _texUId = program()->uniformLocation("texU");
    _texVId = program()->uniformLocation("texV");
}

void VideoMaterialShader::updateState(const RenderState &state,
                                      QSGMaterial *newMaterial,
                                      QSGMaterial *oldMaterial)
{
    Q_UNUSED(oldMaterial)

    if (state.isOpacityDirty())
        program()->setUniformValue(_opacityId, GLfloat(state.opacity()));

    if (state.isMatrixDirty())
        program()->setUniformValue(_positionMatrixId, state.combinedMatrix());

    static const QMatrix4x4 colorMatrix(
            1.164383561643836,  0.000000000000000,  1.792741071428571, -0.972945075016308,
            1.164383561643836, -0.213248614273730, -0.532909328559444,  0.301482665475862,
            1.164383561643836,  2.112401785714286,  0.000000000000000, -1.133402217873451,
            0.000000000000000,  0.000000000000000,  0.000000000000000,  1.000000000000000);



    program()->setUniformValue(_colorMatrixId, colorMatrix);

    VideoMaterial *material = static_cast<VideoMaterial *>(newMaterial);

    program()->setUniformValue(_texYId, 0);
    program()->setUniformValue(_texUId, 1);
    program()->setUniformValue(_texVId, 2);

    material->bindPlanes();
}
