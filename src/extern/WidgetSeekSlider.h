#ifndef VLCQT_WIDGETSEEKSLIDER_H_
#define VLCQT_WIDGETSEEKSLIDER_H_

#include <QtCore/QPoint>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QWidget>
#else
    #include <QtGui/QWidget>
#endif

#include "SharedExportExtern.h"
#include "util/input_slider.hpp"

class VlcMediaPlayer;

class VLCQT_EXTERN_EXPORT VlcWidgetSeekSlider : public SeekSlider
{
Q_OBJECT
public:
    VlcWidgetSeekSlider(Qt::Orientation q, QWidget *_parent = 0, bool _classic = false);

    using SeekSlider::setPosition;
public slots:
    void setDuration(int duration);
    void setPosition(float pos);
    void setTime(int time);
    void updateBuffering100(float f);
    void connectMediaPlayer(VlcMediaPlayer * player);
    void disconnectMediaPlayer(VlcMediaPlayer * player);

private:
    int _duration;
};

#endif // VLCQT_WIDGETSEEKSLIDER_H_
