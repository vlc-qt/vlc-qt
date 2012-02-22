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

#ifndef VLCQT_VIDEOWIDGET_H_
#define VLCQT_VIDEOWIDGET_H_

#include <QtCore/QTimer>
#include <QtGui/QWidget>
#if defined(Q_WS_MAC)
 #include <QMacCocoaViewContainer>
#endif

#include "Enums.h"

class VlcMediaPlayer;
class VlcVideo;

/*!
    \class VlcVideoWidget VideoWidget.h vlc-qt/VideoWidget.h
    \brief Video widget

    This is one of VLC-Qt GUI classes.
    It provides video display and mouse control.
*/
#if defined(Q_WS_MAC)
class VlcVideoWidget : public QMacCocoaViewContainer
#else
class VlcVideoWidget : public QWidget
#endif
{
Q_OBJECT
public:
    /*!
        \brief VlcVideoWidget constructor
        \param player media player (VlcMediaPlayer *)
        \param parent video widget's parent GUI widget (QWidget)
    */
    VlcVideoWidget(VlcMediaPlayer *player,
                   QWidget *parent = 0);

    /*!
        \brief VlcVideoWidget constructor
        \param parent video widget's parent GUI widget (QWidget)
    */
    VlcVideoWidget(QWidget *parent = 0);

    /*!
        \brief VlcVideoWidget destructor
    */
    ~VlcVideoWidget();

    /*!
        \brief Get current aspect ratio setting
        \return current aspect ratio (const Vlc::Ratio)
    */
    inline Vlc::Ratio currentAspectRatio() const { return _currentAspectRatio; }

    /*!
        \brief Get default aspect ratio setting
        \return default aspect ratio (const Vlc::Ratio)
    */
    inline Vlc::Ratio defaultAspectRatio() const { return _defaultAspectRatio; }

    /*!
        \brief Set default aspect ratio setting
        \param ratio default aspect ratio (const Vlc::Ratio)
    */
    void setDefaultAspectRatio(const Vlc::Ratio &ratio);

    /*!
        \brief Get current crop ratio setting
        \return current crop ratio (const Vlc::Ratio)
    */
    inline Vlc::Ratio currentCropRatio() const { return _currentCropRatio; }

    /*!
        \brief Get default crop ratio setting
        \return default crop ratio (const Vlc::Ratio)
    */
    inline Vlc::Ratio defaultCropRatio() const { return _defaultCropRatio; }

    /*!
        \brief Set default crop ratio setting
        \param ratio default crop ratio (const Vlc::Ratio)
    */
    void setDefaultCropRatio(const Vlc::Ratio &ratio);

    /*!
        \brief Get current deinterlacing filter setting
        \return current deinterlacing filter (const Vlc::Deinterlacing)
    */
    inline Vlc::Deinterlacing currentDeinterlacing() const { return _currentDeinterlacing; }

    /*!
        \brief Get default deinterlacing filter setting
        \return current deinterlacing filter (const Vlc::Deinterlacing)
    */
    inline Vlc::Deinterlacing defaultDeinterlacing() const { return _defaultDeinterlacing; }

    /*!
        \brief Set default deinterlacing filter setting
        \param ratio default deinterlacing filter (const Vlc::Deinterlacing)
    */
    void setDefaultDeinterlacing(const Vlc::Deinterlacing &deinterlacing);

    /*!
        \brief Set media player if initialised without it
        \param player media player (VlcMediaPlayer *)
    */
    void setMediaPlayer(VlcMediaPlayer *player);

    /*!
        \brief Get unique video widget ID to set it in the instance
        \return widget ID (const WId)
        \sa VlcMediaPlayer::VlcMediaPlayer()
    */
#if defined(Q_WS_MAC)
    inline WId widgetId() const { return WId(cocoaView()); }
#else
    inline WId widgetId() const { return _widget->winId(); }
#endif

protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

signals:
    /*!
        \brief Signal sending fullscreen request
    */
    void fullscreen();

    /*!
        \brief Signal sending right click and it's location
        \param QPoint right click location
    */
    void rightClick(const QPoint);

    /*!
        \brief Signal sending mouse wheel direction
        \param bool true if up
    */
    void wheel(const bool);

    /*!
        \brief Signal sending if mouse moved and cursor is showed
        \param QPoint global position
    */
    void mouseShow(const QPoint);

    /*!
        \brief Signal sending if mouse cursor is hidden
    */
    void mouseHide();


public slots:
    /*!
        \brief Enable mouse hide
    */
    inline void enableMouseHide() { _hide = true; }
    /*!
        \brief Disable mouse hide
    */
    inline void disableMouseHide() { _hide = false; }

    /*!
        \brief Toggle fullscreen
    */
    void toggleFullscreen();

    /*!
        \brief Enable default video settings

        crop, ratio, deinterlacing filter
    */
    void enableDefaultSettings();

    /*!
        \brief Enable previous video settings

        crop, ratio, deinterlacing filter
    */
    void enablePreviousSettings();

    /*!
        \brief Initialize default video settings

        Set but not apply crop, ratio, deinterlacing filter
    */
    void initDefaultSettings();

    /*!
        \brief Set aspect ratio
        \param ratio aspect ratio (const Vlc::Ratio)
    */
    void setAspectRatio(const Vlc::Ratio &ratio);

    /*!
        \brief Set crop ratio
        \param ratio crop ratio (const Vlc::Ratio)
    */
    void setCropRatio(const Vlc::Ratio &ratio);

    /*!
        \brief Set deinterlace filter
        \param ratio crop ratio (const Vlc::Deinterlacing)
    */
    void setDeinterlacing(const Vlc::Deinterlacing &deinterlacing);


private slots:
    void hideMouse();
    void applyPreviousSettings();

private:
    VlcVideo *_vlcVideo;

    QWidget *_widget;
    QTimer *_timerMouse;
    QTimer *_timerSettings;

    bool _hide;

    Vlc::Ratio _defaultAspectRatio;
    Vlc::Ratio _defaultCropRatio;
    Vlc::Deinterlacing _defaultDeinterlacing;

    Vlc::Ratio _currentAspectRatio;
    Vlc::Ratio _currentCropRatio;
    Vlc::Deinterlacing _currentDeinterlacing;
};

#endif // VLCQ_VIDEOWIDGET_H_
