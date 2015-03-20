#include "WidgetSeekSlider.h"

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
