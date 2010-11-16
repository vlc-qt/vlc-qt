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
	libvlc_media_parse(media->libvlcMedia());
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

QString VlcMetaManager::rating() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Rating));
	return meta;
}

int VlcMetaManager::year() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Date));
	return meta.toInt();
}

void VlcMetaManager::setYear(const int &year)
{
	libvlc_media_set_meta(_media->libvlcMedia(), libvlc_meta_Date, QString().number(year).toAscii().data());
}

QString VlcMetaManager::setting() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_Setting));
	return meta;
}

QString VlcMetaManager::url() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_URL));
	return meta;
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

QString VlcMetaManager::id() const
{
	QString meta(libvlc_media_get_meta(_media->libvlcMedia(), libvlc_meta_TrackID));
	return meta;
}

bool VlcMetaManager::saveMeta() const
{
	return libvlc_media_save_meta(_media->libvlcMedia());
}
