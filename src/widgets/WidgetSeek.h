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

#ifndef VLCQT_WIDGETSEEK_H_
#define VLCQT_WIDGETSEEK_H_

#include <QtCore/QPoint>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QWidget>
#else
    #include <QtGui/QWidget>
#endif

#include "SharedExportWidgets.h"

class QLabel;
class QProgressBar;
class QTimer;

class VlcMediaPlayer;

/*!
    \class VlcWidgetSeek WidgetSeek.h vlc-qt/WidgetSeek.h
    \brief Seek widget

    This is one of VLC-Qt GUI classes.
    It provides only a display of elapsed time and full time of the media.
*/
class VLCQT_WIDGETS_EXPORT VlcWidgetSeek : public QWidget
{
Q_OBJECT
public:
    /*!
        \brief VlcWidgetSeek constructor
        \param player media player (VlcMediaPlayer *)
        \param parent seek widget's parent GUI widget (QWidget *)
    */
    explicit VlcWidgetSeek(VlcMediaPlayer *player,
                           QWidget *parent = 0);

    /*!
        \brief VlcWidgetSeek constructor
        \param parent seek widget's parent GUI widget (QWidget *)
    */
    explicit VlcWidgetSeek(QWidget *parent = 0);

    /*!
        \brief VlcWidgetSeek destructor
    */
    ~VlcWidgetSeek();

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
    void setAutoHide(bool autoHide);

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
    void updateCurrentTime(int time);
    void updateFullTime(int time);

private:
    void initWidgetSeek();
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

#endif // VLCQT_WIDGETSEEK_H_
