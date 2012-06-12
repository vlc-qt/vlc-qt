/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_VOLUMESLIDER_H_
#define VLCQT_VOLUMESLIDER_H_

#include <QWidget>

class QLabel;
class QSlider;
class QTimer;

class VlcAudio;
class VlcMediaPlayer;

/*!
    \class VlcVolumeSlider VolumeSlider.h vlc-qt/VolumeSlider.h
    \brief Volume slider widget

    This is one of VLC-Qt GUI classes.
    It provides graphical volume control and also visual display of current volume.
*/
class VlcVolumeSlider : public QWidget
{
Q_OBJECT
public:
    /*!
        \brief VlcVolumeSlider constructor

        \param player media player (VlcMediaPlayer *)
        \param parent volume slider's parent GUI widget (QWidget)
    */
    explicit VlcVolumeSlider(VlcMediaPlayer *player,
                             QWidget *parent = 0);

    /*!
        \brief VlcVolumeSlider constructor
        \param parent volume slider's parent GUI widget (QWidget)
    */
    explicit VlcVolumeSlider(QWidget *parent = 0);

    /*!
        \brief VlcVolumeSlider destructor
    */
    ~VlcVolumeSlider();


    /*!
        \brief Set media player if initialised without it
        \param player media player (VlcMediaPlayer *)
    */
    void setMediaPlayer(VlcMediaPlayer *player);

public slots:
    /*!
        \brief Mute status
        \return bool current mute status (const bool)
    */
    bool mute() const;

    /*!
        \brief Toggle mute
        \param enabled new mutte status (bool)
    */
    void setMute(const bool &enabled);

    /*!
        \brief Set volume for current media
        \param volume number from 0 to 200 (int)
    */
    void setVolume(const int &volume);

    /*!
        \brief Get volume for current media
        \return volume number from 0 to 200 (const int)
    */
    int volume() const;

    /*!
        \brief Decreases or increases volume for 1, depending on the parameter.

        Limits from 0 to 200 apply to this function.

        \param up if true increases the volume (bool)
    */
    void volumeControl(const bool &up);

    /*!
        \brief Decreases volume for 1.

        This function is provided for convenience.

        \sa volumeControl()
    */
    void volumeDown() { volumeControl(false); }

    /*!
        \brief Increases volume for 1.

        This function is provided for convenience.

        \sa volumeControl()
    */
    void volumeUp() { volumeControl(true); }

signals:
    /*!
        \brief Signal for new volume
        \param int new volume (int)
    */
    void newVolume(const int &);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void updateVolume();

private:
    void initVolumeSlider();

    bool _lock;

    void lock();
    void unlock();

    VlcAudio *_vlcAudio;
    VlcMediaPlayer *_vlcMediaPlayer;

    int _currentVolume;

    QSlider *_slider;
    QLabel *_label;
    QTimer *_timer;
};

#endif // VLCQT_VOLUMESLIDER_H_
