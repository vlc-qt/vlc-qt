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

#include "core/MediaPlayer.h"

#include "AbstractVideoGraphicsPainter.h"
#include "GlslPainter.h"
#include "QPainterPainter.h"
#include "VideoGraphicsObject.h"

QMap<GraphicsPainterType, QList<VideoFrame::Format> > VideoGraphicsPainterMetaFactory::detectTypes()
{
    QMap<GraphicsPainterType, QList<VideoFrame::Format> > map;
    map.insert(GraphicsPainterGlsl, GlslPainter().supportedFormats());
    map.insert(GraphicsPainterQPainter, QPainterPainter().supportedFormats());
    return map;
}

class PrivatePainterFactory
{
public:
    AbstractVideoGraphicsPainter *factorize(QList<VideoFrame::Format> choices,
                                            QMap<GraphicsPainterType, QList<VideoFrame::Format> > formats)
    {
        // Try to find a matching format.
        // Iterate the painters in order glsl>glarb>qpainter, foreach painter check
        // if it supports one of the choosen formats in the order from the backend.
        // That way we get to choose our most preferred (e.g. reliable) painter,
        // while honoring the backends priorization. Painting is weighted more
        // because a bad painter in Qt Quick 1 will cause insanely bad quality (QPainter...)
        GraphicsPainterType painterType = GraphicsPainterNone;
        QMap<GraphicsPainterType,QList<VideoFrame::Format> >::const_iterator it = formats.constBegin();
        while (it != formats.constEnd()) {
            foreach (VideoFrame::Format format, choices) {
                if (it.value().contains(format)) {
                    chosenFormat = format;
                    painterType = it.key();
                    break;
                }
            }
            if (painterType != GraphicsPainterNone)
                break;
            ++it;
        }

        switch(painterType)
        {
        case GraphicsPainterNone:
            // TODO: what to do what to do? :(
            Q_ASSERT(painterType != GraphicsPainterNone);
        case GraphicsPainterGlsl:
            return new GlslPainter;
        case GraphicsPainterQPainter:
            return new QPainterPainter;
        }

        // Cannot reach.
        Q_ASSERT(false);
        return 0;
    }

    VideoFrame::Format chosenFormat;
};


void VideoGraphicsObject::updateBoundingRect()
{
    emit prepareGeometryChange();

    // keep aspect
    QSizeF scaledFrameSize = _frameSize;
    scaledFrameSize.scale(_geometry.size(), Qt::KeepAspectRatio);

    _boundingRect = QRectF(0, 0, scaledFrameSize.width(), scaledFrameSize.height());
    _boundingRect.moveCenter(_geometry.center());
}

/**
 * @brief VideoGraphicsObjectPrivate::_p_negotiateFormat
 * Super spooky function. There are two ways formats can be known to the VGO:
 *  * Previously detected by a (QML) Spy
 *  * This function is called by paint() allowing us to introspect capabilities.
 *
 * Once the supported painters & formats were detected the actual negotiation starts.
 * Currently this function always returns a painter, or it goes down in flames.
 *
 * @return Painter to use.
 */
void VideoGraphicsObject::negotiateFormat()
{
    QMap<GraphicsPainterType,QList<VideoFrame::Format> > formats;
    formats = VideoGraphicsPainterMetaFactory::detectTypes();

    QList<VideoFrame::Format> formatList;
    QMap<GraphicsPainterType,QList<VideoFrame::Format> >::const_iterator it = formats.constBegin();
    while (it != formats.constEnd()) {
        foreach (VideoFrame::Format format, it.value()) {
            if (!formatList.contains(format))
                formatList.append(format);
        }
        ++it;
    }

    _graphicsPainter = new GlslPainter;
    //_graphicsPainter = new QPainterPainter;
    _chosenFormat = VideoFrame::Format_YV12;
}

// --------------------------------- PUBLIC --------------------------------- //

VideoGraphicsObject::VideoGraphicsObject(QGraphicsItem *parent) :
    QGraphicsObject(parent),
        _geometry(0, 0, 320, 240),
        _boundingRect(0, 0, 0, 0),
        _frameSize(0, 0),
        _graphicsPainter(0),
        _paintedOnce(false),
        _gotSize(false),
        _ready(false)
{
    setFlag(ItemHasNoContents, false);
}

VideoGraphicsObject::~VideoGraphicsObject()
{
    if (_graphicsPainter)
        delete _graphicsPainter;
}

QRectF VideoGraphicsObject::boundingRect() const
{
    return _boundingRect;
}

void VideoGraphicsObject::paint(QPainter *painter,
                                const QStyleOptionGraphicsItem *option,
                                QWidget *widget)
{
    lock();

    if (!_graphicsPainter)
        negotiateFormat();

    Q_ASSERT(_graphicsPainter);

    if (_frame.format != VideoFrame::Format_Invalid && !_gotSize) {
        // TODO: do scaling ourselfs?
        _gotSize = true;
        _frameSize = QSize(_frame.width, _frame.height);
        updateBoundingRect();
    }

    if (_frame.format == VideoFrame::Format_Invalid || !_paintedOnce) {
        painter->fillRect(_boundingRect, Qt::black);
        if (!_paintedOnce) // Must not ever block here!
            QMetaObject::invokeMethod(this, "gotPaint", Qt::QueuedConnection);
        _paintedOnce = true;
    } else {
        Q_ASSERT(_graphicsPainter);
        _graphicsPainter->setFrame(&_frame);
        if (!_graphicsPainter->inited())
            _graphicsPainter->init();
        _graphicsPainter->paint(painter, _boundingRect);
    }

    unlock();
}

void VideoGraphicsObject::setGeometry(const QRectF &newGeometry)
{
    _geometry = newGeometry;
    updateBoundingRect();
}

void VideoGraphicsObject::frameReady()
{
    update(_boundingRect);
}

void VideoGraphicsObject::reset()
{
    // Do not reset the spyFormats as they will not change.
    _paintedOnce = false;
    _gotSize = false;

    // The painter is reset because the backend may choose another format for
    // another file (better conversion for some codec etc.)
    if (_graphicsPainter) {
        delete _graphicsPainter;
        _graphicsPainter = 0;
    }
}

void VideoGraphicsObject::connectToMediaPlayer(VlcMediaPlayer *mediaObject)
{
    setCallbacks(mediaObject);
}

void VideoGraphicsObject::disconnectFromMediaPlayer(VlcMediaPlayer *mediaObject)
{
    // Try to prevent callbacks called after this object is being deleted
    if (mediaObject) {
        mediaObject->stop();
    }

    unsetCallbacks(mediaObject);
}

void VideoGraphicsObject::lock()
{
    _mutex.lock();
}

bool VideoGraphicsObject::tryLock()
{
    return _mutex.tryLock();
}

void VideoGraphicsObject::unlock()
{
    _mutex.unlock();
}

void *VideoGraphicsObject::lockCallback(void **planes)
{
    lock();

    for (unsigned int i = 0; i < _frame.planeCount; ++i) {
        planes[i] = reinterpret_cast<void *>(_frame.plane[i].data());
    }

    return 0; // There is only one buffer, so no need to identify it.
}

void VideoGraphicsObject::unlockCallback(void *picture, void *const*planes)
{
    Q_UNUSED(picture);
    Q_UNUSED(planes);
    unlock();
    // To avoid thread polution do not call frameReady directly, but via the
    // event loop.
    QMetaObject::invokeMethod(this, "frameReady", Qt::QueuedConnection);
}

void VideoGraphicsObject::displayCallback(void *picture)
{
    Q_UNUSED(picture); // There is only one buffer.
}

unsigned int VideoGraphicsObject::formatCallback(char *chroma,
                                                 unsigned *width, unsigned *height,
                                                 unsigned *pitches, unsigned *lines)
{
    qDebug() << "Format:"
             << "chroma:" << chroma
             << "width:" << *width
             << "height:" << *height
             << "pitches:" << *pitches
             << "lines:" << *lines;

    if (_chosenFormat == VideoFrame::Format_Invalid)
        negotiateFormat();

    Q_ASSERT(_chosenFormat != VideoFrame::Format_Invalid);

    const vlc_chroma_description_t *chromaDesc = 0;
    switch(_chosenFormat)
    {
    case VideoFrame::Format_RGB32:
        _frame.format = VideoFrame::Format_RGB32;
        qstrcpy(chroma, "RV32");
        chromaDesc = vlc_fourcc_GetChromaDescription(VLC_CODEC_RGB32);
        break;
    case VideoFrame::Format_YV12:
        _frame.format = VideoFrame::Format_YV12;
        qstrcpy(chroma, "YV12");
        chromaDesc = vlc_fourcc_GetChromaDescription(VLC_CODEC_YV12);
        break;
    case VideoFrame::Format_I420:
        _frame.format = VideoFrame::Format_I420;
        qstrcpy(chroma, "I420");
        chromaDesc = vlc_fourcc_GetChromaDescription(VLC_CODEC_I420);
        break;
    case VideoFrame::Format_Invalid:
    default:
        break;
    }

    Q_ASSERT(chromaDesc);

    _frame.width = *width;
    _frame.height = *height;
    _frame.planeCount = chromaDesc->plane_count;

    qDebug() << chroma << chromaDesc->plane_count << *lines;

    const unsigned int bufferSize = setPitchAndLines(chromaDesc,
                                                     *width, *height,
                                                     pitches, lines,
                                                     (unsigned *) &_frame.visiblePitch, (unsigned *)&_frame.visibleLines);
    for (unsigned int i = 0; i < _frame.planeCount; ++i) {
        _frame.pitch[i] = pitches[i];
        _frame.lines[i] = lines[i];
        _frame.plane[i].resize(pitches[i] * lines[i]);
    }

    return bufferSize;
}

void VideoGraphicsObject::formatCleanUpCallback()
{
    // To avoid thread polution do not call reset directly but via the event loop.
    QMetaObject::invokeMethod(this, "reset", Qt::QueuedConnection);
}
