/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2012 Harald Sitter <sitter@kde.org>
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

#ifndef VLCQT_PHONON_VIDEOFRAME_H_
#define VLCQT_PHONON_VIDEOFRAME_H_

#include <QtCore/QByteArray>

/**
 * This struct presents a simple video frame within Phonon.
 * It has all the main characteristics of a frame. It has height, width and a
 * chroma format.
 * The chroma format also decides on how many picture planes one frame may have.
 * For example a YV12 frame will have 3 planes, one for Y one for U and one for V.
 * An RGB32 frame on the other hand only has one plane (as RGB is a packed format).
 *
 * \author Harald Sitter <sitter@kde.org>
 */
struct VideoFrame {
    /**
     * Format names are kept close to the fourcc names. For multiple pixel
     * incarnations the pixel amount is always part of the name.
     * \see http://www.fourcc.org
     * \see http://www.fourcc.org/rgb.php
     * \see http://www.fourcc.org/yuv.php
     */
    enum Format {
        Format_Invalid, /** < Invalid Frame */
        Format_RGB32,   /** < Packed RGB32 */
        Format_YV12,    /** < 3 planes 8 bit Y plane followed by 8 bit 2x2
                              subsampled V and U planes. */
        Format_I420     /** < Like YV12, but U and V are swapped */
    };

    VideoFrame()
        : width(0)
        , height(0)
        , format(Format_Invalid)
    {
        for (int i = 0; i < 4; ++i) {
            pitch[i] = 0;
            visiblePitch[i] = 0;
            lines[i] = 0;
            visibleLines[i] = 0;
        }
    }

    /// The width.
    unsigned int width;

    /// The height.
    unsigned int height;

    /// The format.
    Format format;

    /// The amont of picture planes.
    unsigned int planeCount;

    /// The picture planes.
    QByteArray plane[4];

    /**
     * Pitch/stride of a plane.
     * This pitch is aligned at the backend's desire, so you must not assume any
     * particular alignment.
     * @note The pitch is always bigger than the visible pitch, for painting you
     *       want to clip the plane accordingly (e.g. treat the visible pitch as
     *       a subpicture).
     * @note for conversion into a QImage you will have to pass the appropriate
     *       pitch as bytesPerLine or you'll get unexpected results.
     */
    int pitch[4];

    /**
     * The visible pitch is the actually visible pitch of a plane.
     * It depends only on the format (e.g. for YV12 0 = width, 1 = 2 = width/2).
     */
    int visiblePitch[4];

    /**
     * Lines/scanlines in the plane (aligned).
     * @see pitch
     */
     int lines[4];

    /**
     * Visible lines/scanlines in the plane.
     * @see visiblePitch
     */
    int visibleLines[4];
};

#endif // VLCQT_PHONON_VIDEOFRAME_H_
