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

#include <QtCore/QDebug>
#include <QtCore/QDir>

#include <vlc/vlc.h>

#include "core/Error.h"
#include "core/Instance.h"
#include "core/Media.h"
#include "core/Stats.h"

VlcMedia::VlcMedia(const QString &location,
                   bool localFile,
                   VlcInstance *instance)
    : QObject(instance)
{
    initMedia(location, localFile, instance);
}

VlcMedia::VlcMedia(const QString &location,
                   VlcInstance *instance)
    : QObject(instance)
{
    initMedia(location, false, instance);
}

VlcMedia::VlcMedia(libvlc_media_t *media)
{
    // Create a new libvlc media descriptor from existing one
    _vlcMedia = libvlc_media_duplicate(media);

    VlcError::showErrmsg();
}

VlcMedia::~VlcMedia()
{
    removeCoreConnections();

    libvlc_media_release(_vlcMedia);

    VlcError::showErrmsg();
}

libvlc_media_t *VlcMedia::core()
{
    return _vlcMedia;
}

void VlcMedia::initMedia(const QString &location,
                         bool localFile,
                         VlcInstance *instance)
{
    _currentLocation = location;
    QString l = location;
    if (localFile)
        l = QDir::toNativeSeparators(l);

    // Create a new libvlc media descriptor from location
    if (localFile)
        _vlcMedia = libvlc_media_new_path(instance->core(), l.toUtf8().data());
    else
        _vlcMedia = libvlc_media_new_location(instance->core(), l.toUtf8().data());

    _vlcEvents = libvlc_media_event_manager(_vlcMedia);

    createCoreConnections();

    VlcError::showErrmsg();

    qDebug() << "libvlc" << "Media:" << location << "Local:" << localFile;
}

void VlcMedia::createCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaMetaChanged
         << libvlc_MediaSubItemAdded
         << libvlc_MediaDurationChanged
         << libvlc_MediaParsedChanged
         << libvlc_MediaFreed
         << libvlc_MediaStateChanged;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_attach(_vlcEvents, event, libvlc_callback, this);
    }
}

void VlcMedia::removeCoreConnections()
{
    QList<libvlc_event_e> list;
    list << libvlc_MediaMetaChanged
         << libvlc_MediaSubItemAdded
         << libvlc_MediaDurationChanged
         << libvlc_MediaParsedChanged
         << libvlc_MediaFreed
         << libvlc_MediaStateChanged;

    foreach(const libvlc_event_e &event, list) {
        libvlc_event_detach(_vlcEvents, event, libvlc_callback, this);
    }
}

QString VlcMedia::currentLocation() const
{
    return _currentLocation;
}

VlcStats *VlcMedia::getStats()
{
    libvlc_media_stats_t *coreStats = new libvlc_media_stats_t;

    VlcStats *stats = new VlcStats;
    stats->valid = libvlc_media_get_stats(_vlcMedia, coreStats);

    stats->read_bytes = coreStats->i_read_bytes;
    stats->input_bitrate = coreStats->f_input_bitrate;
    stats->demux_read_bytes = coreStats->i_demux_read_bytes;
    stats->demux_bitrate = coreStats->f_demux_bitrate;
    stats->demux_corrupted = coreStats->i_demux_corrupted;
    stats->demux_discontinuity = coreStats->i_demux_discontinuity;
    stats->decoded_video = coreStats->i_decoded_video;
    stats->decoded_audio = coreStats->i_decoded_audio;
    stats->displayed_pictures = coreStats->i_displayed_pictures;
    stats->lost_pictures = coreStats->i_lost_pictures;
    stats->played_abuffers = coreStats->i_played_abuffers;
    stats->lost_abuffers = coreStats->i_lost_abuffers;
    stats->sent_packets = coreStats->i_sent_packets;
    stats->sent_bytes = coreStats->i_sent_bytes;
    stats->send_bitrate = coreStats->f_send_bitrate;

    return stats;
}

QString VlcMedia::duplicate(const QString &name,
                            const QString &path,
                            const Vlc::Mux &mux)
{
    return record(name, path, mux, true);
}

QString VlcMedia::duplicate(const QString &name,
                            const QString &path,
                            const Vlc::Mux &mux,
                            const Vlc::AudioCodec &audioCodec,
                            const Vlc::VideoCodec &videoCodec)
{
    return record(name, path, mux, audioCodec, videoCodec, true);
}

QString VlcMedia::duplicate(const QString &name,
                            const QString &path,
                            const Vlc::Mux &mux,
                            const Vlc::AudioCodec &audioCodec,
                            const Vlc::VideoCodec &videoCodec,
                            int bitrate,
                            int fps,
                            int scale)
{
    return record(name, path, mux, audioCodec, videoCodec, bitrate, fps, scale, true);
}

QString VlcMedia::merge(const QString &name,
                        const QString &path,
                        const Vlc::Mux &mux)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "gather:std{access=file,mux=%1,dst='%2'}";
    parameters = parameters.arg(Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    option1 = ":sout-keep";
    option2 = ":sout=#%1";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::showErrmsg();

    return l + "." + Vlc::mux()[mux];
}

QString VlcMedia::record(const QString &name,
                         const QString &path,
                         const Vlc::Mux &mux,
                         bool duplicate)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "std{access=file,mux=%1,dst='%2'}";
    parameters = parameters.arg(Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    if (duplicate) {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    } else {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::showErrmsg();

    return l + "." + Vlc::mux()[mux];
}

QString VlcMedia::record(const QString &name,
                         const QString &path,
                         const Vlc::Mux &mux,
                         const Vlc::AudioCodec &audioCodec,
                         const Vlc::VideoCodec &videoCodec,
                         bool duplicate)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "transcode{vcodec=%1,acodec=%2}:std{access=file,mux=%3,dst='%4'}";
    parameters = parameters.arg(Vlc::videoCodec()[videoCodec], Vlc::audioCodec()[audioCodec], Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    if (duplicate) {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    } else {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::showErrmsg();

    return l + "." + Vlc::mux()[mux];
}

QString VlcMedia::record(const QString &name,
                         const QString &path,
                         const Vlc::Mux &mux,
                         const Vlc::AudioCodec &audioCodec,
                         const Vlc::VideoCodec &videoCodec,
                         int bitrate,
                         int fps,
                         int scale,
                         bool duplicate)
{
    QString option1, option2, parameters;
    QString l = QDir::toNativeSeparators(path + "/" + name);

    parameters = "transcode{vcodec=%1,vb=%2,fps=%3,scale=%4,acodec=%5}:std{access=file,mux=%6,dst='%7'}";
    parameters = parameters.arg(Vlc::videoCodec()[videoCodec], QString::number(bitrate), QString::number(fps), QString::number(scale), Vlc::audioCodec()[audioCodec], Vlc::mux()[mux], l + "." + Vlc::mux()[mux]);

    if (duplicate) {
        option2 = ":sout=#duplicate{dst=display,dst=\"%1\"}";
    } else {
        option2 = ":sout=#%1";
    }

    option1 = ":sout-all";
    option2 = option2.arg(parameters);

    setOption(option1);
    setOption(option2);

    VlcError::showErrmsg();

    return l + "." + Vlc::mux()[mux];
}

void VlcMedia::setProgram(int program)
{
    QString option = "program=%1";
    setOption(option.arg(program));
}

void VlcMedia::setOption(const QString &option)
{
    libvlc_media_add_option(_vlcMedia, option.toUtf8().data());

    VlcError::showErrmsg();
}

void VlcMedia::setOptions(const QStringList &options)
{
    foreach(const QString &option, options) {
        libvlc_media_add_option(_vlcMedia, option.toUtf8().data());
    }

    VlcError::showErrmsg();
}

void VlcMedia::libvlc_callback(const libvlc_event_t *event,
                               void *data)
{
    VlcMedia *core = (VlcMedia *)data;

    switch(event->type)
    {
    case libvlc_MediaMetaChanged:
        emit core->metaChanged(Vlc::Meta(event->u.media_meta_changed.meta_type));
        break;
    case libvlc_MediaSubItemAdded:
        emit core->subitemAdded(event->u.media_subitem_added.new_child);
        break;
    case libvlc_MediaDurationChanged:
        emit core->durationChanged(event->u.media_duration_changed.new_duration);
        break;
    case libvlc_MediaParsedChanged:
        emit core->parsedChanged(event->u.media_parsed_changed.new_status);
        break;
    case libvlc_MediaFreed:
        emit core->freed(event->u.media_freed.md);
        break;
    case libvlc_MediaStateChanged:
        emit core->stateChanged(Vlc::State(event->u.media_state_changed.new_state));
        break;
    default:
        break;
    }
}
