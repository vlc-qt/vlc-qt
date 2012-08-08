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

#ifndef VLCQT_SEEKWIDGET_H_
#define VLCQT_SEEKWIDGET_H_

#include <QtCore/QPoint>
#include <QWidget>

class QLabel;
class QProgressBar;
class QTimer;

class VlcMediaPlayer;

/*!
    \class VlcSeekWidget SeekWidget.h vlc-qt/SeekWidget.h
    \brief Seek widget

    This is one of VLC-Qt GUI classes.
    It provides only a display of elapsed time and full time of the media.
*/
class VlcSeekWidget : public QWidget
{
Q_OBJECT
public:
    /*!
        \brief VlcSeekWidget constructor
        \param player media player (VlcMediaPlayer *)
        \param parent seek widget's parent GUI widget (QWidget *)
    */
    explicit VlcSeekWidget(VlcMediaPlayer *player,
                           QWidget *parent = 0);

    /*!
        \brief VlcSeekWidget constructor
        \param parent seek widget's parent GUI widget (QWidget *)
    */
    explicit VlcSeekWidget(QWidget *parent = 0);

    /*!
        \brief VlcSeekWidget destructor
    */
    ~VlcSeekWidget();

    /*!
        \brief Get auto-hide option.
        \return auto-hide option status, true if enabled (bool)
    */
    bool autoHide() const { return _autoHide; }

    /*!
        \brief Set auto-hide option.

        This option will automatically hide seek widget, if enabled.

        \param autoHide new auto-hide option (bool)
    */
    void setAutoHide(const bool &autoHide);

    /*!
        \brief Set media player if initialised without it
        \param player media player (VlcMediaPlayer *)
    */
    void setMediaPlayer(VlcMediaPlayer *player);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void end();
    void updateCurrentTime(const int &time);
    void updateFullTime(const int &time);

private:
    void initSeekWidget();
    void updateEvent(const QPoint &pos);

    void lock();
    void unlock();

    bool _lock;

    VlcMediaPlayer *_vlcMediaPlayer;

    bool _autoHide;
    QProgressBar *_seek;
    QLabel *_labelElapsed;
    QLabel *_labelFull;
};

#endif // VLCQT_SEEKWIDGET_H_
