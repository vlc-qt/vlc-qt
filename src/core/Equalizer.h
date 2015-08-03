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

#ifndef VLCQT_EQUALIZER_H_
#define VLCQT_EQUALIZER_H_

#include <QtCore/QObject>

#include "SharedExportCore.h"

class VlcMediaPlayer;

struct libvlc_equalizer_t;

/*!
    \class VlcEqualizer Equalizer.h VLCQtCore/Equalizer.h
    \brief VlcEqualizer

    \since libVLC 2.2
*/
class VLCQT_CORE_EXPORT VlcEqualizer : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief VlcEqualizer constructor.
    */
    explicit VlcEqualizer(VlcMediaPlayer *vlcMediaPlayer);

    /*!
        \brief VlcEqualizer destructor
    */
    ~VlcEqualizer();

    /*!
        \brief Get the amplification value for a particular equalizer frequency band.
        \param index, counting from zero, of the frequency band to get
        \return amplification value (Hz); -1.0 if there is no such frequency band
     */
    float amplificationForBandAt(uint bandIndex) const;

    /*!
        \brief Get the number of distinct frequency bands for an equalizer.
        \return number of frequency bands
     */
    uint bandCount() const;

    /*!
        \brief Get a particular equalizer band frequency.
        \details This value can be used, for example, to create a label for an equalizer band control in a user interface.
        \param index of the band, counting from zero
        \return equalizer band frequency (Hz), or -1 if there is no such band
     */
    float bandFrequency(uint bandIndex) const;

    /*!
        \brief Get the current pre-amplification value from an equalizer.
        \return preamp value (Hz)
     */
    float preamplification() const;

    /*!
        \brief Get the number of equalizer presets.
        \return number of presets
     */
    uint presetCount() const;

    /*!
        \brief Get the name of a particular equalizer preset.
        \details This name can be used, for example, to prepare a preset label or menu in a user interface.
        \param index of the preset, counting from zero
        \return preset name, or an empty string if there is no such preset
     */
    QString presetNameAt(uint index) const;

public slots:
    void loadFromPreset(uint index);

    /*!
        \brief Set a new amplification value for a particular equalizer frequency band.
        \details The new equalizer settings are subsequently applied to a media player by invoking libvlc_media_player_set_equalizer().
            The supplied amplification value will be clamped to the -20.0 to +20.0 range.
        \param amp, amplification value (-20.0 to 20.0 Hz)
        \param bandIndex, counting from zero, of the frequency band to set
     */
    void setAmplificationForBandAt(float amp, uint bandIndex);

    void setEnabled(bool b);

    /*!
        \brief Set a new pre-amplification value for an equalizer.
        \details The new equalizer settings are subsequently applied to a media player by invoking libvlc_media_player_set_equalizer().
            The supplied amplification value will be clamped to the -20.0 to +20.0 range.
        \param preamp value in (-20.0 to 20.0 Hz)
     */
    void setPreamplification(float value);

signals:
    void presetLoaded();

private:
    VlcMediaPlayer *_vlcMediaPlayer;
    libvlc_equalizer_t *_vlcEqualizer;
};

#endif // VLCQT_EQUALIZER_H_
