/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_ENUMS_H_
#define VLCQT_ENUMS_H_

#include <QtCore/QStringList>

/*!
	\namespace Vlc Enums.h vlc-qt/Enums.h
	\brief Common enumerations
*/
namespace Vlc
{
	// Enums
	/*!
		\enum ActionsType
		\brief Actions types identifiers
	*/
	enum ActionsType {
		AudioTrack,
		Subtitles,
		VideoTrack,
		Other
	};

	/*!
		\enum AudioCodec
		\brief Audio codecs list
	*/
	enum AudioCodec {
		MPEG2Audio,
		MP3,
		MPEG4Audio,
		Vorbis,
		Flac
	};

	/*!
		\enum Deinterlacing
		\brief Supported deinterlacing modes
	*/
	enum Deinterlacing {
		Disabled,
		Discard,
		Blend,
		Mean,
		Bob,
		Linear,
		X
	};

	/*!
		\enum Mux
		\brief Recording output file mux
	*/
	enum Mux {
		TS,
		PS,
		MP4,
		OGG,
		AVI
	};

	/*!
		\enum Ratio
		\brief Supported aspect and crop ratios
	*/
	enum Ratio {
		Original,
		R_16_9,
		R_16_10,
		R_185_100,
		R_221_100,
		R_235_100,
		R_239_100,
		R_4_3,
		R_5_4,
		R_5_3,
		R_1_1
	};

	/*!
		\enum State
		\brief VLC-Qt playback states
	*/
	enum State {
		Idle,
		Opening,
		Buffering,
		Playing,
		Paused,
		Stopped,
		Ended,
		Error
	};

	/*!
		\enum VideoCodec
		\brief Video codecs list
	*/
	enum VideoCodec {
		MPEG2Video,
		MPEG4Video,
		x264,
		Theora
	};

    // Functions
    /*!
        \brief Audio codecs strings
        \return audio codecs strings (QStringList)
    */
    QStringList audioCodec();

    /*!
        \brief Deinterlacing modes strings
        \return deinterlacing strings (QStringList)
    */
    QStringList deinterlacing();

    /*!
        \brief Mux strings
        \return mux strings (QStringList)
    */
    QStringList mux();

    /*!
        \brief Aspect and crop ratios strings
        \return ratios strings (QStringList)
    */
    QStringList ratio();

    /*!
        \brief Aspect and crop ratios strings in readable form
        \return ratios strings (QStringList)
    */
    QStringList ratioHuman();

    /*!
        \brief Video codecs strings
        \return video codecs strings (QStringList)
    */
    QStringList videoCodec();
}

#endif // VLCQT_ENUMS_H_
