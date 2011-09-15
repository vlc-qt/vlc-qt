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

        This constructor creates a new media instance from a media location.

        \param media selected media for meta information (VlcMedia *)
    */
    VlcMetaManager(VlcMedia *media);

    /*!
        \brief VlcMetaManager destructor
    */
    ~VlcMetaManager();


    /*!
        \brief Get current track title.

        \return current track title (const QString)
    */
    QString title() const;

    /*!
        \brief Set track title.

        \param title new track title (QString)
    */
    void setTitle(const QString &title);

    /*!
        \brief Get current track artist.

        \return current track artist (const QString)
    */
    QString artist() const;

    /*!
        \brief Set track artist.
        \param artist new track artist (QString)
    */
    void setArtist(const QString &artist);

    /*!
        \brief Get current track genre.

        \return current track genre (const QString)
    */
    QString genre() const;

    /*!
        \brief Set track genre.

        \param genre new track genre (QString)
    */
    void setGenre(const QString &genre);

    /*!
        \brief Get current track copyright.

        \return current track copyright (const QString)
    */
    QString copyright() const;

    /*!
        \brief Set track copyright.

        \param copyright new track copyright (QString)
    */
    void setCopyright(const QString &copyright);

    /*!
        \brief Get current track album.

        \return current track album (const QString)
    */
    QString album() const;

    /*!
        \brief Set track album.

        \param album new track album (QString)
    */
    void setAlbum(const QString &album);

    /*!
        \brief Get current track number.

        \return current track number (const int)
    */
    int number() const;

    /*!
        \brief Set track number.

        \param number new track number (int)
    */
    void setNumber(const int &number);

    /*!
        \brief Get current track description.

        \return current track description (const QString)
    */
    QString description() const;

    /*!
        \brief Set track description.

        \param description new track description (QString)
    */
    void setDescription(const QString &description);

    /*!
        \brief Get current track rating.

        \return current track rating (const QString)
    */
    QString rating() const;

    /*!
        \brief Get current track year.

        \return current track year (const int)
    */
    int year() const;

    /*!
        \brief Set track year.

        \param year new track year (int)
    */
    void setYear(const int &year);

    /*!
        \brief Get current track setting.

        \return current track setting (const QString)
    */
    QString setting() const;

    /*!
        \brief Get current track URL.

        \return current track URL (const QString)
    */
    QString url() const;

    /*!
        \brief Get current track language.

        \return current track language (const QString)
    */
    QString language() const;

    /*!
        \brief Set track language.

        \param language new track language (QString)
    */
    void setLanguage(const QString &language);

    /*!
        \brief Get current track publisher.

        \return current track publisher (const QString)
    */
    QString publisher() const;

    /*!
        \brief Set track publisher.

        \param publisher new track publisher (QString)
    */
    void setPublisher(const QString &publisher);

    /*!
        \brief Get current track encoder.

        \return current track encoder (const QString)
    */
    QString encoder() const;

    /*!
        \brief Set track encoder.

        \param encoder new track encoder (QString)
    */
    void setEncoder(const QString &encoder);

    /*!
        \brief Get current track artwork URL.

        \return current track artwork URL (const QString)
    */
    QString artwork() const;

    /*!
        \brief Get current track ID.

        \return current track ID (const QString)
    */
    QString id() const;

    /*!
        \brief Save the meta previously set.

        \return true if the write operation was successfull (const bool)
    */
    bool saveMeta() const;

private:
    VlcMedia *_media;
};

#endif // VLCQT_METAMANAGER_H_
