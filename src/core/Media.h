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

#ifndef VLCQT_MEDIA_H_
#define VLCQT_MEDIA_H_

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include "Enums.h"

class VlcInstance;

struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;

/*!
    \class VlcMedia Media.h vlc-qt/Media.h
    \brief Media item

    An abstract representation of a playable media.
    It consists of a media location and various optional meta data.
*/
class VlcMedia : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcMedia constructor.

        This constructor creates a new media instance from a media location.

        \param location location of the media (QString)
        \param localFile true, if media is local file (bool)
        \param instance main libvlc instance (VlcInstance *)
    */
    explicit VlcMedia(const QString &location,
                      const bool &localFile,
                      VlcInstance *instance);

    /*!
        \brief VlcMedia constructor.

        This constructor creates a new media instance from a remote media location.
        Provided for convenience.

        \param location remote location of the media (QString)
        \param instance main libvlc instance (VlcInstance *)
    */
    explicit VlcMedia(const QString &location,
                      VlcInstance *instance);

    /*!
        \brief VlcMedia constructor.

        This constructor creates a new media instance from an existing one.

        \param media libvlc media item (libvlc_media_t *)
    */
    VlcMedia(libvlc_media_t *media);

    /*!
        \brief VlcMedia destructor
    */
    ~VlcMedia();

    /*!
        \brief libvlc media item
        \return libvlc media item (libvlc_media_t *)
    */
    libvlc_media_t *core();

    /*!
        \brief Current media location

        \return QString media location
    */
    QString currentLocation() const;

    /*!
        \brief Duplicate (provided for convenience)

        Apply duplicate options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \return QString output file
        \sa record()
    */
    QString duplicate(const QString &name,
                      const QString &path,
                      const Vlc::Mux &mux);

    /*!
        \brief Duplicate (provided for convenience)

        Apply duplicate options with desired mux and transcoding (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \return QString output file
        \sa record()
    */
    QString duplicate(const QString &name,
                      const QString &path,
                      const Vlc::Mux &mux,
                      const Vlc::AudioCodec &audioCodec,
                      const Vlc::VideoCodec &videoCodec);

    /*!
        \brief Duplicate (provided for convenience)

        Apply duplicate options with desired mux, transcoding
        and some other options (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \param bitrate video bitrate (int)
        \param fps frames per second (int)
        \param scale video scale (int)
        \return QString output file
        \sa record()
    */
    QString duplicate(const QString &name,
                      const QString &path,
                      const Vlc::Mux &mux,
                      const Vlc::AudioCodec &audioCodec,
                      const Vlc::VideoCodec &videoCodec,
                      const int &bitrate,
                      const int &fps,
                      const int &scale);


    /*!
        \brief Merge

        Apply merge options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \return QString output file
    */
    QString merge(const QString &name,
                  const QString &path,
                  const Vlc::Mux &mux);

    /*!
        \brief Record

        Apply recording options with desired mux but without transcoding.

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const Vlc::Mux &mux,
                   const bool &duplicate = false);

    /*!
        \brief Record

        Apply recording options with desired mux and transcoding (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const Vlc::Mux &mux,
                   const Vlc::AudioCodec &audioCodec,
                   const Vlc::VideoCodec &videoCodec,
                   const bool &duplicate = false);

    /*!
        \brief Record

        Apply recording options with desired mux, transcoding
        and some other options (experimental).

        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \param bitrate video bitrate (int)
        \param fps frames per second (int)
        \param scale video scale (int)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    QString record(const QString &name,
                   const QString &path,
                   const Vlc::Mux &mux,
                   const Vlc::AudioCodec &audioCodec,
                   const Vlc::VideoCodec &videoCodec,
                   const int &bitrate,
                   const int &fps,
                   const int &scale,
                   const bool &duplicate = false);

    /*!
        \brief Set media option
        \param option media option (QString)
    */
    void setOption(const QString &option);

    /*!
        \brief Set media options
        \param options media options (QStringList)
    */
    void setOptions(const QStringList &options);

    /*!
        \brief Get media track type
        \return track type (Vlc::TrackType)
    */
    Vlc::TrackType trackType();


signals:
    /*!
        \brief Signal sent on meta change
        \param libvlc_meta_t * meta
    */
    void metaChanged(const Vlc::Meta &);

    /*!
        \brief Signal sent on subitem added
        \param libvlc_media_t * subitem
    */
    void subitemAdded(libvlc_media_t *);

    /*!
        \brief Signal sent on duration change
        \param int duration
    */
    void durationChanged(const int &);

    /*!
        \brief Signal sent on parsed change
        \param int status
    */
    void parsedChanged(const int &);

    /*!
        \brief Signal sent on freed
        \param libvlc_media_t * media
    */
    void freed(libvlc_media_t *);

    /*!
        \brief Signal sent on state change
        \param Vlc::State state
    */
    void stateChanged(const Vlc::State &);


private:
    void initMedia(const QString &location,
                   const bool &localFile,
                   VlcInstance *instance);

    static void libvlc_callback(const libvlc_event_t *event,
                                void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_t * _vlcMedia;
    libvlc_event_manager_t *_vlcEvents;

    QString _currentLocation;
};

#endif // VLCQT_MEDIA_H_
