/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_QMLPLAYER_H_
#define VLCQT_QMLPLAYER_H_

#include <QtCore/QUrl>

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;
class VlcVideo;

#include "QmlSource.h"

/*!
    \class VlcQmlPlayer QmlPlayer.h VLCQtQml/QmlPlayer.h
    \ingroup VLCQtQml
    \brief QML player

    A QML media player that can play multimedia files inside QML interface.
    You need VlcQmlVideoOutput to display video.

    \see VlcQmlVideoOutput
 */
class VlcQmlPlayer : public VlcQmlSource
{
    Q_OBJECT

    /*!
        \brief Current media URL
        \see url
        \see setUrl
        \see urlChanged
     */
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
public:
    /*!
        \brief VlcQmlPlayer constructor
        \param parent parent object
     */
    explicit VlcQmlPlayer(QObject *parent = 0);
    ~VlcQmlPlayer();

    /*!
        \brief Get current media URL
        \return current media URL

        Used as property in QML.
     */
    QUrl url() const;

    /*!
        \brief Set media URL
        \param url new media URL

        Used as property in QML.
     */
    void setUrl(const QUrl &url);


signals:
    /*!
        \brief URL changed signal
    */
    void urlChanged();


private:
    void openInternal();

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
    VlcVideo *_video;
};

#endif // VLCQT_QMLPLAYER_H_
