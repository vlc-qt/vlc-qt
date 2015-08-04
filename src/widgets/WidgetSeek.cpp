#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#if QT_VERSION >= 0x050000
    #include <QtWidgets/QHBoxLayout>
    #include <QtWidgets/QLabel>
    #include <QtWidgets/QSlider>
    #include <QtWidgets/QProgressBar>
#else
    #include <QtGui/QHBoxLayout>
    #include <QtGui/QLabel>
    #include <QtGui/QSlider>
    #include <QtGui/QProgressBar>
#endif

#include "core/Error.h"
#include "core/MediaPlayer.h"

#include "widgets/WidgetSeek.h"

VlcWidgetSeek::VlcWidgetSeek(VlcMediaPlayer *player, QWidget *slider, bool connectSlider,
                             QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(player),
      _sliderWidget(0),
      _slider(0),
      _progress(0),
      _connectSlider(connectSlider),
      _labelElapsed(0),
      _labelFull(0)
{
    initWidgetSeek(slider);
}

VlcWidgetSeek::VlcWidgetSeek(QWidget *slider, bool connectSlider, QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(0),
      _sliderWidget(0),
      _slider(0),
      _progress(0),
      _connectSlider(connectSlider),
      _labelElapsed(0),
      _labelFull(0)
{
    initWidgetSeek(slider);
}

VlcWidgetSeek::VlcWidgetSeek(QWidget *parent)
    : QWidget(parent),
      _vlcMediaPlayer(0),
      _sliderWidget(0),
      _slider(0),
      _progress(0),
      _connectSlider(true),
      _labelElapsed(0),
      _labelFull(0)
{
    initWidgetSeek(0);
}

VlcWidgetSeek::~VlcWidgetSeek()
{
}

void VlcWidgetSeek::initWidgetSeek(QWidget *slider)
{
    _autoHide = false;
    delete _sliderWidget;

    if (slider == 0)
        slider = new QSlider();

    QAbstractSlider * sl = qobject_cast<QAbstractSlider *>(slider);
    _slider = sl;
    if (sl != 0 && _connectSlider) {
        sl->setOrientation(Qt::Horizontal);
        sl->setMaximum(1);
        if (_vlcMediaPlayer != 0)
        {
            connect(sl, SIGNAL(valueChanged(int)), _vlcMediaPlayer, SLOT(setTime(int)));
            connect(_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), sl, SLOT(setEnabled(bool)));
        }
    }
    QProgressBar * bar = qobject_cast<QProgressBar *>(slider);
    _progress = bar;
    if (bar != 0 && _connectSlider)
    {
        bar->setOrientation(Qt::Horizontal);
        bar->setMaximum(1);
        bar->setTextVisible(false);
    }

    if(_labelElapsed == 0)
        _labelElapsed = new QLabel(this);
    _labelElapsed->setText("--:--");

    if(_labelFull == 0)
        _labelFull = new QLabel(this);
    _labelFull->setText("--:--");

    delete layout();
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_labelElapsed);
    layout->addWidget(slider);
    layout->addWidget(_labelFull);
    setLayout(layout);
}

void VlcWidgetSeek::setAutoHide(bool autoHide)
{
    _autoHide = autoHide;

    setVisible(!_autoHide);
}

void VlcWidgetSeek::setMediaPlayer(VlcMediaPlayer *player)
{
    if (_vlcMediaPlayer) {
        disconnect(_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
        disconnect(_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
        disconnect(_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
        disconnect(_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
        if (_slider != 0) {
            disconnect(_slider, SIGNAL(valueChanged(int)), _vlcMediaPlayer, SLOT(setTime(int)));
            disconnect(_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), _slider, SLOT(setEnabled(bool)));
        }
    }

    _vlcMediaPlayer = player;
    if (player == 0)
        return;

    connect(_vlcMediaPlayer, SIGNAL(lengthChanged(int)), this, SLOT(updateFullTime(int)));
    connect(_vlcMediaPlayer, SIGNAL(timeChanged(int)), this, SLOT(updateCurrentTime(int)));
    connect(_vlcMediaPlayer, SIGNAL(end()), this, SLOT(end()));
    connect(_vlcMediaPlayer, SIGNAL(stopped()), this, SLOT(end()));
    if (_slider != 0 && _connectSlider) {
        _slider->setOrientation(Qt::Horizontal);
        _slider->setMaximum(1);
        connect(_slider, SIGNAL(valueChanged(int)), _vlcMediaPlayer, SLOT(setTime(int)));
        connect(_vlcMediaPlayer, SIGNAL(seekableChanged(bool)), _slider, SLOT(setEnabled(bool)));
    }
    else if (_progress != 0 && _connectSlider)
    {
        _progress->setOrientation(Qt::Horizontal);
        _progress->setMaximum(1);
        _progress->setTextVisible(false);
    }
}

void VlcWidgetSeek::setSliderWidget(QWidget *slider, bool updateSlider)
{
    _connectSlider = updateSlider;
    if (slider == 0)
        return;
    if (slider == _slider || slider == _progress)
        return;
    delete _slider;
    delete _progress;
    initWidgetSeek(slider);
}

void VlcWidgetSeek::end()
{
    _labelElapsed->setText("--:--");
    _labelFull->setText("--:--");
    if (_slider != 0 && _connectSlider) {
        _slider->setMaximum(1);
        _slider->setValue(0);
    }
    else if (_progress != 0 && _connectSlider) {
        _progress->setMaximum(1);
        _progress->setValue(0);
    }
}

void VlcWidgetSeek::updateCurrentTime(int time)
{
    QTime currentTime = QTime::fromMSecsSinceStartOfDay(time);

    QString display = "mm:ss";
    if (currentTime.hour() > 0)
        display = "hh:mm:ss";

    _labelElapsed->setText(currentTime.toString(display));
    if (_slider && _connectSlider)
    {
        _slider->blockSignals(true);
        _slider->setValue(time);
        _slider->blockSignals(false);
    }
    else if (_progress && _connectSlider)
        _progress->setValue(time);
}


void VlcWidgetSeek::updateFullTime(int time)
{
    if (time == 0) {
        _labelFull->setText("--:--");
    }
    else {
        QTime fullTime = QTime::fromMSecsSinceStartOfDay(time);

        QString display = "mm:ss";
        if (fullTime.hour() > 0)
            display = "hh:mm:ss";

        _labelFull->setText(fullTime.toString(display));
    }

    if (!time) {
        if (_slider && _connectSlider)
            _slider->setMaximum(1);
        else if (_progress && _connectSlider)
            _progress->setMaximum(1);
        setVisible(!_autoHide);
    } else {
        if (_slider && _connectSlider) {
            _slider->setMaximum(time);
            _slider->setSingleStep(1000);
            _slider->setPageStep(time / 100);
        }
        if (_progress && _connectSlider)
            _progress->setMaximum(time);
        setVisible(true);
    }
}
