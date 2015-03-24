#include "WidgetSeekSlider.h"
#include "MediaPlayer.h"

VlcWidgetSeekSlider::VlcWidgetSeekSlider(Qt::Orientation q, QWidget *_parent, bool _classic)
    : SeekSlider(q, _parent, _classic),
      _duration(0)
{
}

void VlcWidgetSeekSlider::setDuration(int duration)
{
    _duration = duration / 1000;
    setPosition(0.0, 0, _duration);
}

void VlcWidgetSeekSlider::setPosition(float pos)
{
    setPosition(pos, 0, _duration);
}

void VlcWidgetSeekSlider::setTime(int time)
{
    if (_duration == 0)
        setPosition(0.0, 0, 0);
    else
        setPosition(float(time)/float(_duration), 0, _duration);
}

void VlcWidgetSeekSlider::updateBuffering100(float f)
{
    updateBuffering(f / 100.0);
}

void VlcWidgetSeekSlider::connectMediaPlayer(VlcMediaPlayer *player)
{
    connect(player, SIGNAL(lengthChanged(int)), this, SLOT(setDuration(int)));
    connect(player, SIGNAL(positionChanged(float)), this, SLOT(setPosition(float)));
    connect(this, SIGNAL(sliderDragged(float)), player, SLOT(setPosition(float)));
    connect(player, SIGNAL(buffering(float)), this, SLOT(updateBuffering100(float)));
    connect(player, SIGNAL(seekableChanged(bool)), this, SLOT(setSeekable(bool)));
}

void VlcWidgetSeekSlider::disconnectMediaPlayer(VlcMediaPlayer *player)
{
    disconnect(player, SIGNAL(lengthChanged(int)), this, SLOT(setDuration(int)));
    disconnect(player, SIGNAL(positionChanged(float)), this, SLOT(setPosition(float)));
    disconnect(this, SIGNAL(sliderDragged(float)), player, SLOT(setPosition(float)));
    disconnect(player, SIGNAL(buffering(float)), this, SLOT(updateBuffering100(float)));
    disconnect(player, SIGNAL(seekableChanged(bool)), this, SLOT(setSeekable(bool)));
}
