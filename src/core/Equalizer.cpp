/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#include <cmath>
#include <vlc/vlc.h>

#include "core/Equalizer.h"
#include "core/Error.h"
#include "core/MediaPlayer.h"

VlcEqualizer::VlcEqualizer(VlcMediaPlayer *vlcMediaPlayer)
    : QObject(vlcMediaPlayer),
      _vlcMediaPlayer(vlcMediaPlayer),
      _vlcEqualizer(libvlc_audio_equalizer_new()) { }

VlcEqualizer::~VlcEqualizer()
{
    if (_vlcEqualizer) {
        libvlc_audio_equalizer_release(_vlcEqualizer);
    }
}

float VlcEqualizer::amplificationForBandAt(uint bandIndex) const
{
    if (_vlcEqualizer) {
        float ret = libvlc_audio_equalizer_get_amp_at_index(_vlcEqualizer, bandIndex);
        if (!std::isnan(ret)) {
            return ret;
        }
    }
    return -1.0;
}

uint VlcEqualizer::bandCount() const
{
    if (_vlcEqualizer) {
        return libvlc_audio_equalizer_get_band_count();
    } else {
        return 0;
    }
}

float VlcEqualizer::bandFrequency(uint bandIndex) const
{
    if (_vlcEqualizer) {
        return libvlc_audio_equalizer_get_band_frequency(bandIndex);
    } else {
        return -1.0;
    }
}

float VlcEqualizer::preamplification() const
{
    if (_vlcEqualizer) {
        return libvlc_audio_equalizer_get_preamp(_vlcEqualizer);
    } else {
        return 0.0;
    }
}

uint VlcEqualizer::presetCount() const
{
    return libvlc_audio_equalizer_get_preset_count();
}

QString VlcEqualizer::presetNameAt(uint index) const
{
    const char *name = libvlc_audio_equalizer_get_preset_name(index);
    if (name == NULL) {
        return QString();
    } else {
        return QString(name);
    }
}

void VlcEqualizer::loadFromPreset(uint index)
{
    if (_vlcEqualizer) {
        libvlc_audio_equalizer_release(_vlcEqualizer);
    }
    _vlcEqualizer = libvlc_audio_equalizer_new_from_preset(index);
    VlcError::showErrmsg();
    if (_vlcEqualizer) {
        emit presetLoaded();
    }
}

void VlcEqualizer::setAmplificationForBandAt(float amp, uint bandIndex)
{
    if (!_vlcEqualizer) {
        return;
    }
    libvlc_audio_equalizer_set_amp_at_index(_vlcEqualizer, amp, bandIndex);
    libvlc_media_player_set_equalizer(_vlcMediaPlayer->core(), _vlcEqualizer);
    VlcError::showErrmsg();
}

void VlcEqualizer::setEnabled(bool b)
{
    if (b && _vlcEqualizer != NULL) {
        libvlc_media_player_set_equalizer(_vlcMediaPlayer->core(), _vlcEqualizer);
    } else {
        libvlc_media_player_set_equalizer(_vlcMediaPlayer->core(), NULL);
    }
}

void VlcEqualizer::setPreamplification(float value)
{
    if (!_vlcEqualizer) {
        return;
    }
    libvlc_audio_equalizer_set_preamp(_vlcEqualizer, value);
    libvlc_media_player_set_equalizer(_vlcMediaPlayer->core(), _vlcEqualizer);
    VlcError::showErrmsg();
}
