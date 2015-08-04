#ifndef VLCQT_WIDGETSEEK_H_
#define VLCQT_WIDGETSEEK_H_

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QWidget>
#else
    #include <QtGui/QWidget>
#endif

#include "SharedExportWidgets.h"

class QLabel;
class QProgressBar;
class QTimer;
class QWidget;
class QAbstractSlider;

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
        \param slider widget to be used as slider (QWidget *)
        \param connectSlider connect the slider to relevant sigals. Set to false if you want to handle everything yourself. (bool)
        \param parent seek widget's parent GUI widget (QWidget *)
    */
    explicit VlcWidgetSeek(VlcMediaPlayer *player, QWidget *slider = 0, bool connectSlider = true,
                           QWidget *parent = 0);

    /*!
        \brief VlcWidgetSeek constructor
        \param slider widget to be used as slider (QWidget *)
        \param connectSlider connect the slider to relevant sigals. Set to false if you want to handle everything yourself. (bool)
        \param parent seek widget's parent GUI widget (QWidget *)
    */
    explicit VlcWidgetSeek(QWidget *slider, bool connectSlider,
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
    virtual void setMediaPlayer(VlcMediaPlayer *player);

    /*!
        \brief Set slider widget.
        \param slider widget to be used as slider (QWidget *)
        \param connectSlider connect the slider to relevant sigals. Set to false if you want to handle everything yourself. (bool)
    */
    virtual void setSliderWidget(QWidget *slider, bool updateSlider = true);

protected slots:
    void end();
    virtual void updateCurrentTime(int time);
    virtual void updateFullTime(int time);

protected:
    void initWidgetSeek(QWidget *slider);

    VlcMediaPlayer *_vlcMediaPlayer;

    bool _autoHide;
    QWidget * _sliderWidget;
    QAbstractSlider *_slider;
    QProgressBar *_progress;
    bool _connectSlider;
    QLabel *_labelElapsed;
    QLabel *_labelFull;
};

#endif // VLCQT_WIDGETSEEK_H_
