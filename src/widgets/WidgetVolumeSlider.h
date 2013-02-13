/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_WIDGETVOLUMESLIDER_H_
#define VLCQT_WIDGETVOLUMESLIDER_H_

// QtGui/QtWidget
#include <QWidget>

#include "SharedExportWidgets.h"

class QLabel;
class QSlider;
class QTimer;

class VlcAudio;
class VlcMediaPlayer;

/*!
    \class VlcWidgetVolumeSlider WidgetVolumeSlider.h vlc-qt/WidgetVolumeSlider.h
    \brief Volume slider widget

    This is one of VLC-Qt GUI classes.
    It provides graphical volume control and also visual display of current volume.
*/
class VLCQT_WIDGETS_EXPORT VlcWidgetVolumeSlider : public QWidget
{
Q_OBJECT
public:
    /*!
        \brief VlcWidgetVolumeSlider constructor

        \param player media player (VlcMediaPlayer *)
        \param parent volume slider's parent GUI widget (QWidget)
    */
    explicit VlcWidgetVolumeSlider(VlcMediaPlayer *player,
                                   QWidget *parent = 0);

    /*!
        \brief VlcWidgetVolumeSlider constructor
        \param parent volume slider's parent GUI widget (QWidget)
    */
    explicit VlcWidgetVolumeSlider(QWidget *parent = 0);

    /*!
        \brief VlcWidgetVolumeSlider destructor
    */
    ~VlcWidgetVolumeSlider();


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
    void initWidgetVolumeSlider();

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

#endif // VLCQT_WIDGETVOLUMESLIDER_H_
