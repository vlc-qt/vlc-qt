/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
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

/*!
	\namespace Vlc Enums.h vlc-qt/Enums.h
	\brief Common enumerations
*/
namespace Vlc
{
	/*!
		\enum ActionsType
		\brief Actions types identifiers
	*/
	enum ActionsType {
		AudioTrack, /*!< audio tracks */
		Subtitles, /*!< subtitles */
		VideoTrack /*!< video tracks */
	};
};

#endif // VLCQT_ENUMS_H_
