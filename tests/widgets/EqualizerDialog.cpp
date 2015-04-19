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

#include "core/Audio.h"
#include "core/Equalizer.h"
#include "core/MediaPlayer.h"

#include "EqualizerDialog.h"

EqualizerDialog::EqualizerDialog(QWidget *parent)
    : QDialog(parent),
      _mediaPlayer(0)
{
    this->setupUi(this);

    // Default equalizer has ten bands
    _mapSliders.insert(firstBand, 0);
    _mapSliders.insert(secondBand, 1);
    _mapSliders.insert(thirdBand, 2);
    _mapSliders.insert(fourthBand, 3);
    _mapSliders.insert(fifthBand, 4);
    _mapSliders.insert(sixthBand, 5);
    _mapSliders.insert(seventhBand, 6);
    _mapSliders.insert(eighthBand, 7);
    _mapSliders.insert(ninethBand, 8);
    _mapSliders.insert(tenthBand, 9);

    // Set sliders value with unit
    for (QSlider *slider : findChildren<QSlider*>()) {
        QLabel *valueLabel = findChild<QLabel*>(slider->objectName() + "Label");
        connect(slider, &QSlider::valueChanged, this, [=](int value) {
            valueLabel->setText(QString::number(value) + " dB");
        });
    }

    connect(toggleEqualizer, &QCheckBox::toggled, this, &EqualizerDialog::toggle);
}

void EqualizerDialog::setMediaPlayer(VlcMediaPlayer *mediaPlayer)
{
    _mediaPlayer = mediaPlayer;
    auto equalizer = _mediaPlayer->equalizer();
    for (uint i = 0; i < equalizer->presetCount(); i++) {
        presetComboBox->addItem(equalizer->presetNameAt(i));
    }

    // Create local connections
    connect(presetComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), _mediaPlayer->equalizer(), &VlcEqualizer::loadFromPreset);
    connect(_mediaPlayer->equalizer(), &VlcEqualizer::presetLoaded, this, &EqualizerDialog::applySelectedPreset);

    connect(preamp, &QSlider::valueChanged, equalizer, &VlcEqualizer::setPreamplification);
    for (QSlider *slider : findChildren<QSlider*>()) {
        if (slider != preamp) {
            connect(slider, &QSlider::valueChanged, this, &EqualizerDialog::applyChangesForBand);
        }
    }
}

void EqualizerDialog::applyChangesForBand(int value)
{
    int bandIndex = _mapSliders.value(static_cast<QSlider*>(sender()));
    _mediaPlayer->equalizer()->setAmplificationForBandAt((float)value, bandIndex);
}

void EqualizerDialog::applySelectedPreset()
{
    auto equalizer = _mediaPlayer->equalizer();

    disconnect(preamp, 0, equalizer, 0);
    for (QSlider *slider : findChildren<QSlider*>()) {
        if (slider == preamp) {
            slider->setValue(equalizer->preamplification());
        } else {
            disconnect(slider, &QSlider::valueChanged, this, &EqualizerDialog::applyChangesForBand);
            slider->setValue(equalizer->amplificationForBandAt(_mapSliders.value(slider)));
            connect(slider, &QSlider::valueChanged, this, &EqualizerDialog::applyChangesForBand);
        }
    }
    connect(preamp, &QSlider::valueChanged, equalizer, &VlcEqualizer::setPreamplification);
}

void EqualizerDialog::toggle(bool checked)
{
    for (QSlider *slider : findChildren<QSlider*>()) {
        slider->setEnabled(checked);
    }
    presetComboBox->setEnabled(checked);
    _mediaPlayer->equalizer()->setEnabled(checked);
}

