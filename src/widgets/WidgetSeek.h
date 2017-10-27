/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#if QT_VERSION >= 0x050000
#include <QtWidgets/QWidget>
#else
#include <QtGui/QWidget>
#endif

#include "SharedExportWidgets.h"

class QAbstractSlider;
class QLabel;
class QProgressBar;
class QTimer;

class VlcMediaPlayer;

/*!
    \class VlcWidgetSeek WidgetSeek.h VLCQtWidgets/WidgetSeek.h
    \ingroup VLCQtWidgets
    \brief Seek widget

    This is one of VLC-Qt GUI classes.
    It provides a display of elapsed time and full time of the media.
*/
class VLCQT_WIDGETS_EXPORT VlcWidgetSeek : public QWidget
{
    Q_OBJECT
public:
    /*!
        \brief VlcWidgetSeek constructor
        \param player media player
        \param slider widget to be used as slider
        \param connectSlider connect the slider to relevant signals, set to false if you want to handle everything yourself
        \param parent seek widget's parent GUI widget
    */
    explicit VlcWidgetSeek(VlcMediaPlayer *player,
                           QWidget *slider = 0,
                           bool connectSlider = true,
                           QWidget *parent = 0);

    /*!
        \brief VlcWidgetSeek constructor
        \param slider widget to be used as slider
        \param connectSlider connect the slider to relevant signals, set to false if you want to handle everything yourself
        \param parent seek widget's parent GUI widget
    */
    explicit VlcWidgetSeek(QWidget *slider,
                           bool connectSlider,
                           QWidget *parent = 0);

    /*!
        \brief VlcWidgetSeek constructor
        \param parent seek widget's parent GUI widget
    */
    explicit VlcWidgetSeek(QWidget *parent = 0);

    /*!
        \brief VlcWidgetSeek destructor
    */
    ~VlcWidgetSeek();

    /*!
        \brief Get auto-hide option.
        \return auto-hide option status, true if enabled
    */
    bool autoHide() const { return _autoHide; }

    /*!
        \brief Set auto-hide option

        This option will automatically hide seek widget, if enabled.

        \param autoHide new auto-hide option
    */
    void setAutoHide(bool autoHide);

    /*!
        \brief Set media player if initialised without it
        \param player media player
    */
    virtual void setMediaPlayer(VlcMediaPlayer *player);

    /*!
        \brief Set slider widget
        \param slider widget to be used as slider
        \param updateSlider connect the slider to relevant sigals, set to false if you want to handle everything yourself
    */
    virtual void setSliderWidget(QWidget *slider,
                                 bool updateSlider = true);

protected slots:
    /*!
        \brief Update current time callback
        \param time current time
    */
    virtual void updateCurrentTime(int time);

    /*!
        \brief Update full time callback
        \param time full time
    */
    virtual void updateFullTime(int time);

protected:
    /*!
     * \brief Media player
     */
    VlcMediaPlayer *_vlcMediaPlayer;

    /*!
     * \brief Progress bar
     */
    QProgressBar *_progress;

    /*!
     * \brief Elapsed time label
     */
    QLabel *_labelElapsed;

    /*!
     * \brief Total time label
     */
    QLabel *_labelTotal;

private slots:
    void end();

private:
    void initWidgetSeek(QWidget *slider);

    bool _autoHide;
    QAbstractSlider *_slider;
    bool _connectSlider;
};

#endif // VLCQT_WIDGETSEEK_H_
