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

#ifndef VLCQT_WIDGETVIDEO_H_
#define VLCQT_WIDGETVIDEO_H_

#include <QtCore/QTimer>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QFrame>
#else
    #include <QtGui/QFrame>
#endif

#if defined(Q_OS_MAC)
    #include <QMacCocoaViewContainer>
#endif

#include "Enums.h"
#include "SharedExportWidgets.h"
#include "VideoDelegate.h"

class VlcMediaPlayer;

/*!
    \class VlcWidgetVideo WidgetVideo.h vlc-qt/WidgetVideo.h
    \brief Video widget

    This is one of VLC-Qt GUI classes.
    It provides video display and mouse control.
*/
#if defined(Q_OS_MAC)
class VLCQT_WIDGETS_EXPORT VlcWidgetVideo : public QMacCocoaViewContainer, public VlcVideoDelegate
#else
class VLCQT_WIDGETS_EXPORT VlcWidgetVideo : public QFrame, public VlcVideoDelegate
#endif
{
Q_OBJECT
public:
    /*!
        \brief VlcWidgetVideo constructor
        \param player media player (VlcMediaPlayer *)
        \param parent video widget's parent GUI widget (QWidget)
    */
    explicit VlcWidgetVideo(VlcMediaPlayer *player,
                            QWidget *parent = 0);

    /*!
        \brief VlcWidgetVideo constructor
        \param parent video widget's parent GUI widget (QWidget)
    */
    explicit VlcWidgetVideo(QWidget *parent = 0);

    /*!
        \brief VlcWidgetVideo destructor
    */
    ~VlcWidgetVideo();

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
        \brief Set current aspect ratio setting
        \param ratio current aspect ratio (const Vlc::Ratio)
    */
    void setCurrentAspectRatio(const Vlc::Ratio &ratio);

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
        \brief Set current crop ratio setting
        \param ratio current crop ratio (const Vlc::Ratio)
    */
    void setCurrentCropRatio(const Vlc::Ratio &ratio);

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
        \brief Set current deinterlacing filter setting
        \param ratio current deinterlacing filter (const Vlc::Deinterlacing)
    */
    void setCurrentDeinterlacing(const Vlc::Deinterlacing &deinterlacing);

    /*!
        \brief Set default deinterlacing filter setting
        \param ratio default deinterlacing filter (const Vlc::Deinterlacing)
    */
    void setDefaultDeinterlacing(const Vlc::Deinterlacing &deinterlacing);

    /*!
        \brief Get current scale ratio setting
        \return current scale ratio (const Vlc::Scale)
    */
    inline Vlc::Scale currentScale() const { return _currentScale; }

    /*!
        \brief Get default scale ratio setting
        \return default scale ratio (const Vlc::Scale)
    */
    inline Vlc::Scale defaultScale() const { return _defaultScale; }

    /*!
        \brief Set current scale ratio setting
        \param scale current scale ratio (const Vlc::Scale)
    */
    void setCurrentScale(const Vlc::Scale &scale);

    /*!
        \brief Set default scale ratio setting
        \param scale default scale ratio (const Vlc::Scale)
    */
    void setDefaultScale(const Vlc::Scale &scale);

    /*!
        \brief Set media player if initialised without it
        \param player media player (VlcMediaPlayer *)
    */
    void setMediaPlayer(VlcMediaPlayer *player);

    /*!
        \brief Request new video frame.

        Request new video frame and its widget ID to set it in the instance.
        \return widget ID (WId)
        \sa VlcMediaPlayer::VlcMediaPlayer()
    */
    WId request();

    /*!
        \brief Release current video frame.
    */
    void release();


public slots:
    /*!
        \brief Enable default video settings

        crop, ratio, deinterlacing filter, scale
    */
    void enableDefaultSettings();

    /*!
        \brief Enable previous video settings

        crop, ratio, deinterlacing filter, scale
    */
    void enablePreviousSettings();

    /*!
        \brief Initialize default video settings

        Set but not apply crop, ratio, deinterlacing filter, scale
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

    /*!
        \brief Set scale ratio
        \param scale scale ratio (const Vlc::Scale)
    */
    void setScale(const Vlc::Scale &scale);


private slots:
    void applyPreviousSettings();

private:
    void initWidgetVideo();
    void sync();

    VlcMediaPlayer *_vlcMediaPlayer;

#if !defined(Q_OS_MAC)
    QWidget *_video;
    QLayout *_layout;
#endif

    bool _enableSettings;

    Vlc::Ratio _defaultAspectRatio;
    Vlc::Ratio _defaultCropRatio;
    Vlc::Deinterlacing _defaultDeinterlacing;
    Vlc::Scale _defaultScale;

    Vlc::Ratio _currentAspectRatio;
    Vlc::Ratio _currentCropRatio;
    Vlc::Deinterlacing _currentDeinterlacing;
    Vlc::Scale _currentScale;
};

#endif // VLCQ_WIDGETVIDEO_H_
