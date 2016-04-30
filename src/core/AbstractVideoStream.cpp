/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
* Copyright (C) 2012 Harald Sitter <sitter@kde.org>
*
* This file is based on Phonon multimedia library
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

#include <vlc/vlc.h>

#include "core/AbstractVideoStream.h"
#include "core/MediaPlayer.h"

static inline VlcAbstractVideoStream *p_this(void *opaque) { return static_cast<VlcAbstractVideoStream *>(opaque); }
static inline VlcAbstractVideoStream *p_this(void **opaque) { return static_cast<VlcAbstractVideoStream *>(*opaque); }
#define P_THIS p_this(opaque)

VlcAbstractVideoStream::VlcAbstractVideoStream() { }

VlcAbstractVideoStream::~VlcAbstractVideoStream() { }

void VlcAbstractVideoStream::setCallbacks(VlcMediaPlayer *player)
{
    libvlc_video_set_callbacks(player->core(),
                               lockCallbackInternal,
                               unlockCallbackInternal,
                               displayCallbackInternal,
                               this);
    libvlc_video_set_format_callbacks(player->core(),
                                      formatCallbackInternal,
                                      formatCleanUpCallbackInternal);
}

void VlcAbstractVideoStream::unsetCallbacks(VlcMediaPlayer *player)
{
    if (player) {
        libvlc_video_set_callbacks(player->core(), 0, 0, 0, 0);
        libvlc_video_set_format_callbacks(player->core(), 0, 0);
    }
}


void *VlcAbstractVideoStream::lockCallbackInternal(void *opaque,
                                                   void **planes)
{
    return P_THIS->lockCallback(planes);
}

void VlcAbstractVideoStream::unlockCallbackInternal(void *opaque,
                                                    void *picture,
                                                    void * const *planes)
            {
    P_THIS->unlockCallback(picture, planes);
}

void VlcAbstractVideoStream::displayCallbackInternal(void *opaque,
                                                     void *picture)
{
    P_THIS->displayCallback(picture);
}

unsigned VlcAbstractVideoStream::formatCallbackInternal(void **opaque,
                                                        char *chroma,
                                                        unsigned *width,
                                                        unsigned *height,
                                                        unsigned *pitches,
                                                        unsigned *lines)
{
    return P_THIS->formatCallback(chroma, width, height, pitches, lines);
}

void VlcAbstractVideoStream::formatCleanUpCallbackInternal(void *opaque)
{
    P_THIS->formatCleanUpCallback();
}
