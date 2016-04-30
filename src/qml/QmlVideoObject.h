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

#ifndef VLCQT_QMLVIDEOOBJECT_H_
#define VLCQT_QMLVIDEOOBJECT_H_

#include <QtCore/QMap>
#include <QtCore/QMutex>
#include <QtQuick/QQuickPaintedItem>

#include <VLCQtCore/Enums.h>
#include <VLCQtCore/VideoFrame.h>
#include <VLCQtCore/VideoMemoryStream.h>

#include "SharedExportQml.h"

class VlcMediaPlayer;

class GlslPainter;

/*!
    \class VlcQmlVideoObject QmlVideoObject.h VLCQtQml/QmlVideoObject.h
    \ingroup VLCQtQml
    \brief QML video object (deprecated)

    A basic QML video object for painting video. It acts as a replacement for video widget.

    \deprecated Deprecated since VLC-Qt 1.1, will be removed in 2.0
 */
class Q_DECL_DEPRECATED VLCQT_QML_EXPORT VlcQmlVideoObject : public QQuickPaintedItem,
                                           public VlcVideoMemoryStream
{
Q_OBJECT
public:
    /*!
        \brief VlcQmlVideoObject constructor.
        \param parent parent item
     */
    explicit VlcQmlVideoObject(QQuickItem *parent = 0);

    /*!
        VlcMediaPlayer destructor
     */
    virtual ~VlcQmlVideoObject();


    /*!
        \brief Connect to media player
        \param player media player
     */
    void connectToMediaPlayer(VlcMediaPlayer *player);

    /*!
        \brief Disconnect from media player
        \param player media player
     */
    void disconnectFromMediaPlayer(VlcMediaPlayer *player);


    /*!
        \brief Get current aspect ratio
        \return aspect ratio
     */
    Vlc::Ratio aspectRatio() const;

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio
     */
    void setAspectRatio(const Vlc::Ratio &aspectRatio);

    /*!
        \brief Get current crop ratio
        \return crop ratio
     */
    Vlc::Ratio cropRatio() const;

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio
     */
    void setCropRatio(const Vlc::Ratio &cropRatio);

protected:
    /*!
        \brief Core media player
     */
    VlcMediaPlayer *_player;

private slots:
    void frameReady();
    void reset();

private:
    virtual void *lockCallback(void **planes);
    virtual void unlockCallback(void *picture,void *const *planes);
    virtual void displayCallback(void *picture);

    virtual unsigned formatCallback(char *chroma,
                                    unsigned *width, unsigned *height,
                                    unsigned *pitches,
                                    unsigned *lines);
    virtual void formatCleanUpCallback();

    virtual QRectF boundingRect() const;
    void geometryChanged(const QRectF &newGeometry,
                         const QRectF &oldGeometry);

    void paint(QPainter *painter);

    void lock();
    bool tryLock();
    void unlock();

    void updateBoundingRect();
    void updateAspectRatio();
    void updateCropRatio();

    QMutex _mutex;
    VlcVideoFrame _frame;

    QRectF _geometry;
    QRectF _boundingRect;
    QSize _frameSize;

    GlslPainter *_graphicsPainter;

    bool _paintedOnce;
    bool _gotSize;

    Vlc::Ratio _aspectRatio;
    Vlc::Ratio _cropRatio;
};

#endif // VLCQT_QMLVIDEOOBJECT_H_
