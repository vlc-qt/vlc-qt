/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2014 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_STATS_H_
#define VLCQT_STATS_H_

#include "SharedExportCore.h"

/*!
    \struct VlcStats Stats.h VLCQtCore/Stats.h
    \ingroup VLCQtCore
    \brief Statistics container

    A direct copy of libvlc stats object to remove dependency to libvlc.
*/
struct VLCQT_CORE_EXPORT VlcStats
{
    bool valid; /*!< VLC stats success status */
    int read_bytes; /*!< libVLC stats */
    float input_bitrate; /*!< libVLC stats */
    int demux_read_bytes; /*!< libVLC stats */
    float demux_bitrate; /*!< libVLC stats */
    int demux_corrupted; /*!< libVLC stats */
    int demux_discontinuity; /*!< libVLC stats */
    int decoded_video; /*!< libVLC stats */
    int decoded_audio; /*!< libVLC stats */
    int displayed_pictures; /*!< libVLC stats */
    int lost_pictures; /*!< libVLC stats */
    int played_abuffers; /*!< libVLC stats */
    int lost_abuffers; /*!< libVLC stats */
    int sent_packets; /*!< libVLC stats */
    int sent_bytes; /*!< libVLC stats */
    float send_bitrate; /*!< libVLC stats */
};

#endif // VLCQT_STATS_H_
