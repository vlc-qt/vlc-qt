/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_VIDEO_H_
#define VLCQT_VIDEO_H_

#include <QtCore/QList>
#include <QtCore/QSize>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>

#include "Enums.h"
#include "SharedExportCore.h"

class VlcMediaPlayer;

struct libvlc_media_player_t;

/*!
    \class VlcVideo Video.h VLCQtCore/Video.h
    \ingroup VLCQtCore
    \brief Video controls

    A group of video controls functions.
*/
class VLCQT_CORE_EXPORT VlcVideo : public QObject
{
    Q_OBJECT
public:
    /*!
        \brief VlcVideo constructor.

        This constructor creates a new video manager.

        \param player media player (VlcMediaPlayer *)
    */
    explicit VlcVideo(VlcMediaPlayer *player);

    /*!
        \brief VlcVideo destructor
    */
    ~VlcVideo();

    /*!
        \brief Get current video aspect ratio.
        \return current video aspect-ratio or NULL if not specified (const Vlc::Ratio)
    */
    Vlc::Ratio aspectRatio() const;

    /*!
        \brief Get current crop filter geometry.
        \return current crop filter geometry or NULL if not specified (const Vlc::Ratio)
    */
    Vlc::Ratio cropGeometry() const;

    /*!
        \brief Hide logo.
    */
    void hideLogo();

    /*!
        \brief Hide marquee.
    */
    void hideMarquee();

    /*!
        \brief Get current scale ratio.
        \return current scale ratio or NULL if not specified (const Vlc::Scale)
    */
    Vlc::Scale scale() const;

    /*!
        \brief Set new video aspect ratio.
        \param ratio new video aspect-ratio or NULL to reset to default (Vlc::Ratio)
    */
    void setAspectRatio(const Vlc::Ratio &ratio);

    /*!
        \brief Set new crop filter geometry.
        \param ratio new crop filter geometry or NULL to reset to default (Vlc::Ratio)
    */
    void setCropGeometry(const Vlc::Ratio &ratio);

    /*!
        \brief Enable or disable deinterlace filter.
        \param filter type of deinterlace filter or NULL to reset to default (Vlc::Deinterlacing)
    */
    void setDeinterlace(const Vlc::Deinterlacing &filter);

    /*!
        \brief Set new scale ratio.
        \param scale scale ratio or NULL to reset to default (Vlc::Scale)
    */
    void setScale(const Vlc::Scale &scale);

    /*!
        \brief Set current video subtitle.
        \param subtitle new video subtitle (int)
    */
    void setSubtitle(int subtitle);

    /*!
        \brief Set new video subtitle file.
        \param subtitle new video subtitle file (QString)
    */
    void setSubtitleFile(const QString &subtitle);

    /*!
        \brief Set new teletext page to retrieve.
        \param page new teletext page number (int)
    */
    void setTeletextPage(int page);

    /*!
        \brief Set current video track.
        \param track new video track (int)
    */
    void setTrack(int track);

    /*!
        \brief Show logo.
        \param file logo file (QString)
        \param x x-coordinate (int)
        \param y y-coordinate (int)
        \param opacity logo opacity (int)
    */
    void showLogo(const QString &file,
                  int x,
                  int y,
                  int opacity = 255);

    /*!
        \brief Show logo.
        \param text text to display (QString)
        \param x x-coordinate (int)
        \param y y-coordinate (int)
        \param timeout marquee timeout
        \param opacity opacity from 0 to 255 (int)
        \param size size (int)
        \param color color in base 16 int (int)
        \param refresh refresh rate (int)
    */
    void showMarquee(const QString &text,
                     int x,
                     int y,
                     int timeout = 0,
                     int opacity = 255,
                     int size = -1,
                     int color = 0xFFFFFF,
                     int refresh = 0);

    /*!
        \brief Get current video size. (currently primary only)
        \return size of the video (QSize)
    */
    QSize size() const;

    /*!
        \brief Get current video subtitle.
        \return the number of current video subtitle, or -1 if none (const int)
    */
    int subtitle() const;

    /*!
        \brief Get number of available video subtitles.
        \return the number of available video subtitles, or -1 if unavailable (const int)
    */
    int subtitleCount() const;

    /*!
        \brief Get the descriptions of available video subtitles.
        \return list with descriptions of available video subtitles (const QStringList)
    */
    QStringList subtitleDescription() const;

    /*!
        \brief Get the ids of available video subtitles.
        \return list with ids of available video subtitles (const QList<int>)
    */
    QList<int> subtitleIds() const;

    /*!
        \brief Get available video subtitles.
        \return dictionary with available video subtitles (const QMap<int, QString>)
        \since VLC-Qt 1.1
    */
    QMap<int, QString> subtitles() const;

    /*!
        \brief Take a snapshot of current video (currently primary only)
        \param path output path (QString)
        \return true if successfull (bool)
    */
    bool takeSnapshot(const QString &path) const;

    /*!
        \brief Get current teletext page requested.
        \return current teletext page number (int)
    */
    int teletextPage() const;

    /*!
        \brief Toggle teletext transparent status on video output.
    */
    void toggleTeletextTransparency();

    /*!
        \brief Get current video track.
        \return the number of current video track, or -1 if none (const int)
    */
    int track() const;

    /*!
        \brief Get number of available video tracks.
        \return the number of available video tracks, or -1 if unavailable (const int)
    */
    int trackCount() const;

    /*!
        \brief Get the description of available video tracks.
        \return list with description of available video tracks (const QStringList)
    */
    QStringList trackDescription() const;

    /*!
        \brief Get the ids of available video tracks.
        \return list with ids of available video tracks (const QList<int>)
    */
    QList<int> trackIds() const;

    /*!
        \brief Get available video tracks.
        \return dictionary with available video tracks (const QMap<int, QString>)
        \since VLC-Qt 1.1
    */
    QMap<int, QString> tracks() const;

private:
    libvlc_media_player_t *_vlcMediaPlayer;
};

#endif // VLCQT_VIDEO_H_
