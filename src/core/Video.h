/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Video.h: libvlc video controls
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

#ifndef VLCQT_VIDEO_H_
#define VLCQT_VIDEO_H_

#include <QtCore/QString>

/*!
	\class VlcVideo Video.h vlc-qt/Video.h
	\brief Video controls

	A group of video controls functions.
*/
class VlcVideo
{
public:
	/*!
		\brief Get current video aspect ratio.

		\return current video aspect-ratio or NULL if not specified (QString)
	*/
	static QString aspectRatio();

	/*!
		\brief Get current crop filter geometry.

		\return current crop filter geometry or NULL if not set (QString)
	*/
	static QString cropGeometry();

	/*!
		\brief Set new video aspect ratio.

		\param ratio new video aspect-ratio or NULL to reset to default (QString)
	*/
	static void setAspectRatio(const QString &ratio);

	/*!
		\brief Set new crop filter geometry.

		\param ratio new crop filter geometry or NULL to reset to default (QString)
	*/
	static void setCropGeometry(const QString &crop);

	/*!
		\brief Enable or disable deinterlace filter.

		\param filter type of deinterlace filter or NULL to reset to default (QString)
	*/
	static void setDeinterlace(const QString &filter);

	/*!
		\brief Set new teletext page to retrieve.

		\param page new teletext page number (int)
	*/
	static void setTeletextPage(const int &page);

	/*!
		\brief Get current teletext page requested.

		\return current teletext page number (int)
	*/
	static int teletextPage();

	/*!
		\brief Toggle teletext transparent status on video output.
	*/
	static void toggleTeletext();
};

#endif // VLCQT_VIDEO_H_
