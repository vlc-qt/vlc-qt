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

#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

#include "core/VideoFrame.h"
#include "qml/painter/GlslPainter.h"

GlslPainter::GlslPainter()
    : _program(0) { }

GlslPainter::~GlslPainter()
{
    if (_program && QOpenGLContext::currentContext()) {
        _program->removeAllShaders();
        _program->deleteLater();
    }
}

void GlslPainter::init()
{
    _context = const_cast<QOpenGLContext *>(QOpenGLContext::currentContext());
    Q_ASSERT(_context);

    _gl = _context->functions();
#if defined(QT_OPENGL_ES_2)
    _glF = _context->versionFunctions<QOpenGLFunctions_ES2>();
#else
    _glF = _context->versionFunctions<QOpenGLFunctions_1_1>();
#endif
    Q_ASSERT(_glF);

    _glF->initializeOpenGLFunctions();

    if (!_program)
        _program = new QOpenGLShaderProgram();

    const char *vertexProgram =
            "attribute highp vec4 targetVertex;\n"
            "attribute highp vec2 textureCoordinates;\n"
            "uniform highp mat4 positionMatrix;\n"
            "varying highp vec2 textureCoord;\n"
            "void main(void)\n"
            "{\n"
            "    gl_Position = positionMatrix * targetVertex;\n"
            "    textureCoord = textureCoordinates;\n"
            "}\n";

    static const char *vertexShader =
            "uniform sampler2D texY;\n"
            "uniform sampler2D texU;\n"
            "uniform sampler2D texV;\n"
            "uniform mediump mat4 colorMatrix;\n"
            "varying highp vec2 textureCoord;\n"
            "uniform lowp float opacity;"
            "void main(void)\n"
            "{\n"
            "    highp vec4 color = vec4(\n"
            "           texture2D(texY, textureCoord.st).r,\n"
            "           texture2D(texV, textureCoord.st).r,\n" // !!!! mind the swp
            "           texture2D(texU, textureCoord.st).r,\n"
            "           1.0);\n"
            "    gl_FragColor = colorMatrix * color * opacity;\n"
            "}\n";

    initYv12();
    initColorMatrix();

    if (!_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexProgram))
        qFatal("couldnt add vertex shader");
    else if (!_program->addShaderFromSourceCode(QOpenGLShader::Fragment, vertexShader))
        qFatal("couldnt add fragment shader");
    else if (!_program->link())
        qFatal("couldnt link shader");

    _glF->glGenTextures(_textureCount, _textureIds);

    _inited = true;
}

void GlslPainter::paint(QPainter *painter,
                        QRectF target,
                        QQuickWindow *window)
{
    // Need to reenable those after native painting has begun, otherwise we might
    // not be able to paint anything.
    bool stencilTestEnabled = _glF->glIsEnabled(GL_STENCIL_TEST);
    bool scissorTestEnabled = _glF->glIsEnabled(GL_SCISSOR_TEST);

    painter->beginNativePainting();

    if (stencilTestEnabled)
        _glF->glEnable(GL_STENCIL_TEST);
    if (scissorTestEnabled)
        _glF->glEnable(GL_SCISSOR_TEST);

    //////////////////////////////////////////////////////////////
    initTextures();
    //////////////////////////////////////////////////////////////

    // As seen on the telly
#ifdef __GNUC__
#warning DUPLICATED CODE
#endif

    const float textureCoordinates[] = {
        0, 1, // bottom left
        1, 1, // bottom right
        0, 0, // top left
        1, 0, // top right
    };

    const GLfloat targetVertex[] =
    {
        GLfloat(target.left()), GLfloat(target.bottom()),
        GLfloat(target.right()), GLfloat(target.bottom()),
        GLfloat(target.left()) , GLfloat(target.top()),
        GLfloat(target.right()), GLfloat(target.top())
    };
    //

    const int width = window->width();
    const int height = window->height();

    const QTransform transform = painter->deviceTransform();

    const GLfloat wfactor = 2.0 / width;
    const GLfloat hfactor = -2.0 / height;

    const GLfloat positionMatrix[4][4] = {
        {
            GLfloat(wfactor * transform.m11() - transform.m13()),
            GLfloat(hfactor * transform.m12() + transform.m13()),
            0.0,
            GLfloat(transform.m13())
        }, {
            GLfloat(wfactor * transform.m21() - transform.m23()),
            GLfloat(hfactor * transform.m22() + transform.m23()),
            0.0,
            GLfloat(transform.m23())
        }, {
            0.0,
            0.0,
            -1.0,
            0.0
        }, {
            GLfloat(wfactor * transform.dx() - transform.m33()),
            GLfloat(hfactor * transform.dy() + transform.m33()),
            0.0,
            GLfloat(transform.m33())
        }
    };

    _program->bind();

    _program->enableAttributeArray("targetVertex");
    _program->enableAttributeArray("textureCoordinates");
    _program->setAttributeArray("targetVertex", targetVertex, 2);
    _program->setAttributeArray("textureCoordinates", textureCoordinates, 2);
    _program->setUniformValue("positionMatrix", positionMatrix);

    if (_textureCount == 3) {
        _gl->glActiveTexture(GL_TEXTURE0);
        _glF->glBindTexture(GL_TEXTURE_2D, _textureIds[0]);
        _gl->glActiveTexture(GL_TEXTURE1);
        _glF->glBindTexture(GL_TEXTURE_2D, _textureIds[1]);
        _gl->glActiveTexture(GL_TEXTURE2);
        _glF->glBindTexture(GL_TEXTURE_2D, _textureIds[2]);
        _gl->glActiveTexture(GL_TEXTURE0);

        _program->setUniformValue("texY", 0);
        _program->setUniformValue("texU", 1);
        _program->setUniformValue("texV", 2);
    }
    _program->setUniformValue("colorMatrix", _colorMatrix);
    _program->setUniformValue("opacity", GLfloat(painter->opacity()));

    _glF->glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    _program->release();
    painter->endNativePainting();

    calculateFPS();
}

void GlslPainter::calculateFPS()
{
    if (_fps.lastTime.isNull())
        _fps.lastTime = QTime::currentTime();
    QTime time = QTime::currentTime();

    int delta = _fps.lastTime.msecsTo(time);
    if (delta > 2000) {
        _fps.value = 1000.0 * _fps.frames / qreal(delta);
        if (_fps.value < 20.0)
            qWarning() << "Drawing less than 20 frames per second!";
        _fps.lastTime = time;
        _fps.frames = 0;
    }

    ++_fps.frames;
}
