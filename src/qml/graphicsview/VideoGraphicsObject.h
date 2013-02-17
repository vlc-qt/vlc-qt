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

#ifndef VLCQT_PHONON_VIDEOGRAPHICSOBJECT_H_
#define VLCQT_PHONON_VIDEOGRAPHICSOBJECT_H_

#include <QtCore/QMap>
#include <QtCore/QMutex>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QGraphicsObject>
#else
    #include <QtGui/QGraphicsObject>
#endif

#include "VideoFrame.h"
#include "VideoMemoryStream.h"

class VlcMediaPlayer;

class AbstractVideoGraphicsPainter;

enum GraphicsPainterType {
    GraphicsPainterNone,
    GraphicsPainterGlsl,
    GraphicsPainterQPainter
};

class VideoGraphicsPainterMetaFactory
{
public:
    static QMap<GraphicsPainterType, QList<VideoFrame::Format> > detectTypes();
};

class VideoGraphicsObject : public QGraphicsObject,
                            public VideoMemoryStream
{
    Q_OBJECT
public:
    /** Constructor. \param parent the parent of the object. */
    explicit VideoGraphicsObject(QGraphicsItem *parent = 0);

    /** Destructor. */
    virtual ~VideoGraphicsObject();

    /**
     * \returns the rectangle in which the object will paint, either equal
     * or smaller than the set .
     */
    virtual QRectF boundingRect() const;

    /** \param newGeometry the geometry this object should at most occupy. */
    void setGeometry(const QRectF &newGeometry);

    /** \reimp */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    /**
     * Whether the VideoGraphicsObject is ready to begin playback.
     * Usually it would only be ready when it negotiated the format to use. To do
     * this it most of the time requires at least one paint call. Before the VGO
     * is ready a connected MediaObject will refuse to start playback!
     *
     * Should play be called before the VideoGraphicsObject the MediaObject will
     * put the command on a pending list and wait for the ready signal to be
     * emitted.
     *
     * \see ready()
     */
    bool isReady() const;


    // VLC
    virtual void connectToMediaPlayer(VlcMediaPlayer *mediaObject);
    virtual void disconnectFromMediaPlayer(VlcMediaPlayer *mediaObject);

    void lock();
    bool tryLock();
    void unlock();

    virtual void *lockCallback(void **planes);
    virtual void unlockCallback(void *picture,void *const *planes);
    virtual void displayCallback(void *picture);

    virtual unsigned formatCallback(char *chroma,
                                    unsigned *width, unsigned *height,
                                    unsigned *pitches,
                                    unsigned *lines);
    virtual void formatCleanUpCallback();


signals:
    void ready();

    // FIXME: ew?!
    void gotPaint();

    // TODO: make Q_PRIVATE
private slots:
    void frameReady();
    void reset();

protected:
    QMutex _mutex;

    VideoFrame _frame;

    VideoFrame::Format _chosenFormat;

private:
    void updateBoundingRect();
    void negotiateFormat();

    QRectF _geometry;
    QRectF _boundingRect;
    QSize _frameSize;

    AbstractVideoGraphicsPainter *_graphicsPainter;

    bool _paintedOnce;
    bool _gotSize;
    bool _ready;
};

#endif // VLCQT_PHONON_VIDEOGRAPHICSOBJECT_H_
