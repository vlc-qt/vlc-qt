/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Audio.h: libvlc audio controls
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#ifndef VLCQT_AUDIO_H_
#define VLCQT_AUDIO_H_

#include <QtCore/QStringList>

/*!
	\class VlcAudio Audio.h vlc-qt/Audio.h
	\brief Audio controls

	A group of audio controls functions.
*/
class VlcAudio
{
public:
	/*!
		\brief Get current mute status.

		\return current mute status (bool)
	*/
	static bool getMute();

	/*!
		\brief Set current audio level.

		\param volume new audio level (int)
	*/
	static void setVolume(const int &volume);

	/*!
		\brief Set current audio track.

		\param track new audio track (int)
	*/
	static void setTrack(const int &track);

	/*!
		\brief Toggle mute status.

		\return new mute status (bool)
	*/
	static bool toggleMute();

	/*!
		\brief Get current audio track.

		\return the number of current audio track, or -1 if none (int)
	*/
	static int track();

	/*!
		\brief Get number of available audio tracks.

		\return the number of available audio tracks, or -1 if unavailable (int)
	*/
	static int trackCount();

	/*!
		\brief Get the description of available audio tracks.

		\return list with description of available audio tracks (QStringList)
	*/
	static QStringList trackDescription();

	/*!
		\brief Get current audio level.

		\return current audio level, -1 if media is not playing (int)
	*/
	static int volume();
};

#endif // VLCQT_AUDIO_H_
