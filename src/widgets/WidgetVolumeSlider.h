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
#include <QSlider>

#include "SharedExportWidgets.h"

class QTimer;

class VlcAudio;
class VlcMediaPlayer;

/*!
    \class VlcWidgetVolumeSlider WidgetVolumeSlider.h VLCQtWidgets/WidgetVolumeSlider.h
    \ingroup VLCQtWidgets
    \brief Volume slider widget

    This is one of VLC-Qt GUI classes.
    It provides graphical volume control and also visual display of current volume.
*/
class VLCQT_WIDGETS_EXPORT VlcWidgetVolumeSlider : public QSlider
{
Q_OBJECT
public:
    /*!
        \brief VlcWidgetVolumeSlider constructor

        \param player media player
        \param parent volume slider's parent GUI widget
    */
    explicit VlcWidgetVolumeSlider(VlcMediaPlayer *player,
                                   QWidget *parent = 0);

    /*!
        \brief VlcWidgetVolumeSlider constructor
        \param parent volume slider's parent GUI widget
    */
    explicit VlcWidgetVolumeSlider(QWidget *parent = 0);

    /*!
        \brief VlcWidgetVolumeSlider destructor
    */
    ~VlcWidgetVolumeSlider();


    /*!
        \brief Set media player if initialised without it
        \param player media player
    */
    void setMediaPlayer(VlcMediaPlayer *player);

public slots:
    /*!
        \brief Mute status
        \return bool current mute status
    */
    bool mute() const;

    /*!
        \brief Toggle mute
        \param enabled new mutte status
    */
    void setMute(bool enabled);

    /*!
        \brief Set volume for current media
        \param volume number from 0 to 200
    */
    void setVolume(int volume);

    /*!
        \brief Get volume for current media
        \return volume number from 0 to 200
    */
    int volume() const;

    /*!
        \brief Decreases or increases volume for 1, depending on the parameter.

        Limits from 0 to 200 apply to this function.

        \param up if true increases the volume
    */
    void volumeControl(bool up);

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
        \param volume new volume
    */
    void newVolume(int volume);

protected:
    /*!
        \brief Mouse press event override
        \param event mouse event
    */
    void mousePressEvent(QMouseEvent *event);

    /*!
        \brief Mouse release event override
        \param event mouse event
    */
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

    QTimer *_timer;
};

#endif // VLCQT_WIDGETVOLUMESLIDER_H_
