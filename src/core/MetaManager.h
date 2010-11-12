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

#ifndef VLCQT_METAMANAGER_H_
#define VLCQT_METAMANAGER_H_

#include <QtCore/QDate>
#include <QtCore/QString>

class VlcMedia;

/*!
	\class VlcMetaManager MetaManager.h vlc-qt/MetaManager.h
	\brief Media meta information manager

	A manager and editor of media's meta information.
*/
class VlcMetaManager
{
public:
	/*!
		\brief VlcMetaManager constructor.
		\param media selected media for meta information (VlcMedia*)

		This constructor creates a new media instance from a media location.
	*/
	VlcMetaManager(VlcMedia *media);

	/*!
		\brief VlcMetaManager destructor
	*/
	~VlcMetaManager();


	/*!
		\brief Get current track title.
		\return current track title (QString)
	*/
	QString title() const;

	/*!
		\brief Set track title.
		\param title new track title (QString)
	*/
	void setTitle(const QString &title);

	/*!
		\brief Get current track artist.
		\return current track artist (QString)
	*/
	QString artist() const;

	/*!
		\brief Set track artist.
		\param artist new track artist (QString)
	*/
	void setArtist(const QString &artist);

	/*!
		\brief Get current track genre.
		\return current track genre (QString)
	*/
	QString genre() const;

	/*!
		\brief Set track genre.
		\param genre new track genre (QString)
	*/
	void setGenre(const QString &genre);

	/*!
		\brief Get current track copyright.
		\return current track copyright (QString)
	*/
	QString copyright() const;

	/*!
		\brief Set track copyright.
		\param copyright new track copyright (QString)
	*/
	void setCopyright(const QString &copyright);

	/*!
		\brief Get current track album.
		\return current track album (QString)
	*/
	QString album() const;

	/*!
		\brief Set track album.
		\param album new track album (QString)
	*/
	void setAlbum(const QString &album);

	/*!
		\brief Get current track number.
		\return current track number (int)
	*/
	int number() const;

	/*!
		\brief Set track number.
		\param number new track number (int)
	*/
	void setNumber(const int &number);

	/*!
		\brief Get current track description.
		\return current track description (QString)
	*/
	QString description() const;

	/*!
		\brief Set track description.
		\param description new track description (QString)
	*/
	void setDescription(const QString &description);

	/*!
		\brief Get current track rating.
		\return current track rating (float)
	*/
	float rating() const;

	/*!
		\brief Set track rating.
		\param rating new track rating (float)
	*/
	void setRating(const float &rating);

	/*!
		\brief Get current track date.
		\return current track date (QDate)
	*/
	QDate date() const;

	/*!
		\brief Set track date.
		\param date new track date (QDate)
	*/
	void setDate(const QDate &date);

	/*!
		\brief Get current track setting.
		\return current track setting (QString)
	*/
	QString setting() const;

	/*!
		\brief Set track setting.
		\param setting new track setting (QString)
	*/
	void setSetting(const QString &setting);

	/*!
		\brief Get current track URL.
		\return current track URL (QString)
	*/
	QString url() const;

	/*!
		\brief Set track URL.
		\param url new track URL (QString)
	*/
	void setUrl(const QString &url);

	/*!
		\brief Get current track language.
		\return current track language (QString)
	*/
	QString language() const;

	/*!
		\brief Set track language.
		\param language new track language (QString)
	*/
	void setLanguage(const QString &language);

	/*!
		\brief Get current track now playing status.
		\return current track now playing status (bool)
	*/
	bool playing() const;

	/*!
		\brief Set track now playing status.
		\param status new track now playing status (bool)
	*/
	void setPlaying(const bool &status);

	/*!
		\brief Get current track publisher.
		\return current track publisher (QString)
	*/
	QString publisher() const;

	/*!
		\brief Set track publisher.
		\param publisher new track publisher (QString)
	*/
	void setPublisher(const QString &publisher);

	/*!
		\brief Get current track encoder.
		\return current track encoder (QString)
	*/
	QString encoder() const;

	/*!
		\brief Set track encoder.
		\param encoder new track encoder (QString)
	*/
	void setEncoder(const QString &encoder);

	/*!
		\brief Get current track artwork URL.
		\return current track artwork URL (QString)
	*/
	QString artwork() const;

	/*!
		\brief Set track artwork URL.
		\param url new track artwork URL (QString)
	*/
	void setArtwork(const QString &url);

	/*!
		\brief Get current track ID.
		\return current track ID (QString)
	*/
	QString id() const;

	/*!
		\brief Set track ID.
		\param id new track ID (QString)
	*/
	void setId(const QString &id);


	/*!
		\brief Save the meta previously set.
		\return true if the write operation was successfull (bool)
	*/
	bool saveMeta() const;

private:
	VlcMedia *_media;
};

#endif // VLCQT_METAMANAGER_H_
