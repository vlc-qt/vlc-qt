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

#ifndef VLCQT_ENUMS_H_
#define VLCQT_ENUMS_H_

#include <QObject>
#include <QtCore/QStringList>

#include "SharedExportCore.h"

/*!
    \class Vlc Enums.h vlc-qt/Enums.h
    \brief Common enumerations
*/
class VLCQT_CORE_EXPORT Vlc : public QObject
{
Q_OBJECT

Q_ENUMS(ActionsType)
Q_ENUMS(AudioCodec)
Q_ENUMS(AudioOutput)
Q_ENUMS(Deinterlacing)
Q_ENUMS(Meta)
Q_ENUMS(Mux)
Q_ENUMS(PlaybackMode)
Q_ENUMS(Ratio)
Q_ENUMS(Scale)
Q_ENUMS(State)
Q_ENUMS(TrackType)
Q_ENUMS(VideoCodec)
Q_ENUMS(VideoOutput)

public:
    /*!
        \brief Vlc enums constructor.

        This constructor creates a new dummy enums object.

        \param parent object parent (QObject *)
    */
    explicit Vlc(QObject *parent = 0);

    // Enums
    /*!
        \enum ActionsType
        \brief Actions types identifiers
    */
    enum ActionsType {
        AudioTrack,
        Subtitles,
        VideoTrack,
        Other
    };

    /*!
        \enum AudioCodec
        \brief Audio codecs list
    */
    enum AudioCodec {
        NoAudio,
        MPEG2Audio,
        MP3,
        MPEG4Audio,
        Vorbis,
        Flac
    };

    /*!
        \enum AudioOutput
        \brief Audio outputs list
    */
    enum AudioOutput {
        DefaultAout
    };

    /*!
        \enum Deinterlacing
        \brief Supported deinterlacing modes
    */
    enum Deinterlacing {
        Disabled,
        Discard,
        Blend,
        Mean,
        Bob,
        Linear,
        X,
        Yadif,
        Yadif2x,
        Phospor,
        IVTC
    };

    /*!
        \enum Meta
        \brief Supported meta types
    */
    enum Meta {
        Title,
        Artist,
        Genre,
        Copyright,
        Album,
        TrackNumber,
        Description,
        Rating,
        Date,
        Setting,
        URL,
        Language,
        NowPlaying,
        Publisher,
        EncodedBy,
        ArtworkURL,
        TrackID
    };

    /*!
        \enum Mux
        \brief Recording output file mux
    */
    enum Mux {
        TS,
        PS,
        MP4,
        OGG,
        AVI
    };

    /*!
        \enum PlaybackMode
        \brief Playlist playback mode
    */
    enum PlaybackMode {
        DefaultPlayback,
        Loop,
        Repeat
    };

    /*!
        \enum Ratio
        \brief Supported aspect and crop ratios
    */
    enum Ratio {
        Original,
        R_16_9,
        R_16_10,
        R_185_100,
        R_221_100,
        R_235_100,
        R_239_100,
        R_4_3,
        R_5_4,
        R_5_3,
        R_1_1
    };

    /*!
        \enum Scale
        \brief Supported scales
    */
    enum Scale {
        NoScale,
        S_1_05,
        S_1_1,
        S_1_2,
        S_1_3,
        S_1_4,
        S_1_5,
        S_1_6,
        S_1_7,
        S_1_8,
        S_1_9,
        S_2_0
    };

    /*!
        \enum State
        \brief VLC-Qt playback states
    */
    enum State {
        Idle,
        Opening,
        Buffering,
        Playing,
        Paused,
        Stopped,
        Ended,
        Error
    };

    /*!
        \enum TrackType
        \brief Media track type
    */
    enum TrackType {
        UnknownType,
        Audio,
        Video,
        Text
    };

    /*!
        \enum VideoCodec
        \brief Video codecs list
    */
    enum VideoCodec {
        NoVideo,
        MPEG2Video,
        MPEG4Video,
        H264,
        Theora
    };

    /*!
        \enum VideoOutput
        \brief Video outputs list
    */
    enum VideoOutput {
#if defined(Q_OS_LINUX)
        X11,
        XVideo,
        GLX,
#elif defined(Q_OS_WIN32)
        DirectX,
        Direct3D,
        OpenGL,
#endif
        DefaultVout
    };

    // Functions
    /*!
        \brief Audio codecs strings
        \return audio codecs strings (QStringList)
    */
    static QStringList audioCodec();

    /*!
        \brief Audio outputs strings
        \return audio outputs strings (QStringList)
    */
    static QStringList audioOutput();

    /*!
        \brief Audio outputs strings in readable form
        \return audio outputs strings (QStringList)
    */
    static QStringList audioOutputHuman();

    /*!
        \brief Deinterlacing modes strings
        \return deinterlacing strings (QStringList)
    */
    static QStringList deinterlacing();

    /*!
        \brief Mux strings
        \return mux strings (QStringList)
    */
    static QStringList mux();

    /*!
        \brief Aspect and crop ratios strings
        \return ratios strings (QStringList)
    */
    static QStringList ratio();

    /*!
        \brief Aspect and crop ratios strings in readable form
        \return ratios strings (QStringList)
    */
    static QStringList ratioHuman();

    /*!
        \brief Scale floats
        \return scale floats (QList<float>)
    */
    static QList<float> scale();

    /*!
        \brief Video codecs strings
        \return video codecs strings (QStringList)
    */
    static QStringList videoCodec();

    /*!
        \brief Video outputs strings
        \return video outputs strings (QStringList)
    */
    static QStringList videoOutput();

    /*!
        \brief Video outputs strings in readable form
        \return video outputs strings (QStringList)
    */
    static QStringList videoOutputHuman();
};

#endif // VLCQT_ENUMS_H_
