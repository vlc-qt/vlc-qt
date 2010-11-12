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

#include <vlc/vlc.h>

#include "core/Media.h"
#include "core/MetaManager.h"

VlcMetaManager::VlcMetaManager(VlcMedia *media)
	: _media(media)
{

}

VlcMetaManager::~VlcMetaManager() { }

QString VlcMetaManager::title() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Title));
	return meta;
}

void VlcMetaManager::setTitle(const QString &title)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Title, title.toAscii().data());
}

QString VlcMetaManager::artist() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Artist));
	return meta;
}

void VlcMetaManager::setArtist(const QString &artist)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Artist, artist.toAscii().data());
}

QString VlcMetaManager::genre() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Genre));
	return meta;
}

void VlcMetaManager::setGenre(const QString &genre)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Genre, genre.toAscii().data());
}

QString VlcMetaManager::copyright() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Copyright));
	return meta;
}

void VlcMetaManager::setCopyright(const QString &copyright)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Copyright, copyright.toAscii().data());
}

QString VlcMetaManager::album() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Album));
	return meta;
}

void VlcMetaManager::setAlbum(const QString &album)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Album, album.toAscii().data());
}

int VlcMetaManager::number() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_TrackNumber));
	return meta.toInt();
}

void VlcMetaManager::setNumber(const int &number)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_TrackNumber, QString().number(number).toAscii().data());
}

QString VlcMetaManager::description() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Description));
	return meta;
}

void VlcMetaManager::setDescription(const QString &description)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Description, description.toAscii().data());
}

float VlcMetaManager::rating() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Rating));
	return meta.toFloat();
}

void VlcMetaManager::setRating(const float &rating)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Rating, QString().number(rating).toAscii().data());
}

QDate VlcMetaManager::date() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Date));
	//return meta.toFloat();
}

void VlcMetaManager::setDate(const QDate &date)
{
	//libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Date, QString().number(rating).toAscii().data());
}

QString VlcMetaManager::setting() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Setting));
	return meta;
}

void VlcMetaManager::setSetting(const QString &setting)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Setting, setting.toAscii().data());
}

QString VlcMetaManager::url() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_URL));
	return meta;
}

void VlcMetaManager::setUrl(const QString &url)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_URL, url.toAscii().data());
}

QString VlcMetaManager::language() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Language));
	return meta;
}

void VlcMetaManager::setLanguage(const QString &language)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Language, language.toAscii().data());
}

bool VlcMetaManager::playing() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_NowPlaying));
	//return meta;
}

void VlcMetaManager::setPlaying(const bool &status)
{
	//libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_URL, url.toAscii().data());
}

QString VlcMetaManager::publisher() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Publisher));
	return meta;
}

void VlcMetaManager::setPublisher(const QString &publisher)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Publisher, publisher.toAscii().data());
}

QString VlcMetaManager::encoder() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_EncodedBy));
	return meta;
}

void VlcMetaManager::setEncoder(const QString &encoder)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_EncodedBy, encoder.toAscii().data());
}

QString VlcMetaManager::artwork() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_ArtworkURL));
	return meta;
}

void VlcMetaManager::setArtwork(const QString &url)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_ArtworkURL, url.toAscii().data());
}

QString VlcMetaManager::id() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_TrackID));
	return meta;
}

void VlcMetaManager::setId(const QString &id)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_TrackID, id.toAscii().data());
}

bool VlcMetaManager::saveMeta() const
{

}
