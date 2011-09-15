/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_AUDIO_H_
#define VLCQT_AUDIO_H_

#include <QtCore/QObject>
#include <QtCore/QStringList>

class VlcMediaPlayer;

struct libvlc_media_player_t;

/*!
    \class VlcAudio Audio.h vlc-qt/Audio.h
    \brief Audio controls

    A group of audio controls functions.
*/
class VlcAudio : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcAudio constructor.

        This constructor creates a new audio manager.

        \param player media player (VlcMediaPlayer *)
    */
    VlcAudio(VlcMediaPlayer *player);

    /*!
        \brief VlcAudio destructor
    */
    ~VlcAudio();

    /*!
        \brief Get current mute status.

        \return current mute status (const bool)
    */
    bool getMute() const;

    /*!
        \brief Set current audio level.

        \param volume new audio level (int)
    */
    void setVolume(const int &volume);

    /*!
        \brief Set current audio track.

        \param track new audio track (int)
    */
    void setTrack(const int &track);

    /*!
        \brief Toggle mute status.

        \return new mute status (const bool)
    */
    bool toggleMute() const;

    /*!
        \brief Get current audio track.

        \return the number of current audio track, or -1 if none (const int)
    */
    int track() const;

    /*!
        \brief Get number of available audio tracks.

        \return the number of available audio tracks, or -1 if unavailable (const int)
    */
    int trackCount() const;

    /*!
        \brief Get the description of available audio tracks.

        \return list with description of available audio tracks (const QStringList)
    */
    QStringList trackDescription() const;

    /*!
        \brief Get current audio level.

        \return current audio level, -1 if media is not playing (const int)
    */
    int volume() const;

private:
    libvlc_media_player_t *_vlcMediaPlayer;
};

#endif // VLCQT_AUDIO_H_
