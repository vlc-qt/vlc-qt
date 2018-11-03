/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2014-2015, Sergey Radionov <rsatom_gmail.com>
*
* This file is based on QmlVlc library
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

#ifndef VLCQT_VIDEOSTREAM_H_
#define VLCQT_VIDEOSTREAM_H_

#include <deque>
#include <list>
#include <memory>

#include <QtCore/QObject>

#include "AbstractVideoFrame.h"
#include "AbstractVideoStream.h"
#include "Enums.h"
#include "SharedExportCore.h"

class VlcMediaPlayer;

/*!
    \class VlcVideoStream VideoStream.h VLCQtCore/VideoStream.h
    \ingroup VLCQtCore
    \brief Video memory stream

    VlcVideoStream sets proper callbacks to get YUV frames from libVLC.
    This class should be subclassed and implement frameUpdated to specify what to do with the frame.

    \see VlcQmlVideoStream
    \see VlcAbstractVideoFrame
    \since VLC-Qt 1.1
 */
class VLCQT_CORE_EXPORT VlcVideoStream : public QObject,
                                         public VlcAbstractVideoStream
{
    Q_OBJECT
public:
    /*!
        \brief VlcVideoStream constructor
        \param format rendering format
        \param parent parent object
     */
    explicit VlcVideoStream(Vlc::RenderFormat format,
                            QObject *parent = 0);
    ~VlcVideoStream();

    /*!
        \brief Rendering format
        \return current rendering format
     */
    Vlc::RenderFormat format() const { return _format; } // LCOV_EXCL_LINE

    /*!
        \brief Initialise video memory stream with player
        \param player media player
     */
    void init(VlcMediaPlayer *player);

    /*!
        \brief Prepare video memory stream for deletion
     */
    void deinit();

    /*!
        \brief Get current frame
        \return current frame
     */
    std::shared_ptr<const VlcAbstractVideoFrame> renderFrame() const { return _renderFrame; } // LCOV_EXCL_LINE

    /*!
        \brief Get the current player
        \return current player
     */
    VlcMediaPlayer *player() const { return _player; }
private:
    Q_INVOKABLE virtual void frameUpdated() = 0;

    unsigned formatCallback(char *chroma,
                            unsigned *width,
                            unsigned *height,
                            unsigned *pitches,
                            unsigned *lines);
    void formatCleanUpCallback();

    void *lockCallback(void **planes);
    void unlockCallback(void *picture,
                        void *const *planes);
    void displayCallback(void *picture);

    std::shared_ptr<VlcAbstractVideoFrame> cloneFrame(std::shared_ptr<VlcAbstractVideoFrame> frame);

    Vlc::RenderFormat _format;
    VlcMediaPlayer *_player;

    std::deque<std::shared_ptr<VlcAbstractVideoFrame>> _frames;
    std::list<std::shared_ptr<VlcAbstractVideoFrame>> _lockedFrames;
    std::shared_ptr<VlcAbstractVideoFrame> _renderFrame;
};

#endif // VLCQT_VIDEOSTREAM_H_
