/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2010 Tadej Novak <ntadej@users.sourceforge.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_MEDIAMETA_H_
#define VLCQT_MEDIAMETA_H_

class VlcMedia;

/*!
	\class VlcMediaMeta MediaMeta.h vlc-qt/MediaMeta.h
	\brief Media meta information manager

	A manager and editor of media's meta information.
*/
class VlcMediaMeta
{
public:
	/*!
		\brief VlcMediaMeta constructor.

		This constructor creates a new media instance from a media location.
		\param media selected media for meta information (VlcMedia*)
	*/
	VlcMediaMeta(VlcMedia *media);

	/*!
		\brief VlcMediaMeta destructor
	*/
	~VlcMediaMeta();

private:
	VlcMedia *_media;
};

#endif // VLCQT_MEDIAMETA_H_
