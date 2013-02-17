/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* Based on Phonon multimedia library
* Copyright (C) 2011 Harald Sitter <sitter@kde.org>
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

#ifndef VLCQT_PHONON_ABSTRACTVIDEOGRAPHICSPAINTER_H_
#define VLCQT_PHONON_ABSTRACTVIDEOGRAPHICSPAINTER_H_

#include <QtCore/QList>
#include <QtCore/QRectF>

#include "VideoFrame.h"

class QPainter;

/**
 * This class provides a well defined interface to video graphics painter
 * implementations.
 *
 * A video graphics painter is a class that draws onto an arbitrary target
 * rectangle within a QGraphicsScene by whatever means it has (e.g. OpenGL ARB,
 * GLSL or simply QPainter).
 *
 * \author Harald Sitter <sitter@kde.org>
 */
class AbstractVideoGraphicsPainter
{
public:
    virtual QList<VideoFrame::Format> supportedFormats() const = 0;

    /**
     * Set a new frame on the painter.
     * This function should be called before any other function is used. The
     * frame can either stay valid throughout the life time of the object (in
     * which case you only need to call it once) or you need to set the most
     * current frame each paint cycle.
     * At any rate there must be a valid frame set before calling anything.
     *
     * Mind that you will need to drop the painter and reinitialize a new one
     * once the frame changed in format, size, and the like.
     *
     * \param frame is the video frame that the painter is supposed to paint later on.
     */
    void setFrame(const VideoFrame *frame) { _frame = frame; }

    /**
     * Implementations of init can prepare the painter for painting. For example
     * an OpenGL painter may setup the GLContext and prepare the textures.
     * Mind that init will usually be irreversible, so once a painter was
     * initialized for a specific frame only the data of this frame may change.
     *
     * \see setFrame
     */
    virtual void init() = 0;

    /**
     * The actual paint logic is implemented in this function.
     *
     * \param painter the QPainter obtained from the paint call on a QGraphicsItem.
     * \param target the rectangle to draw in, this will usually be the rectangle calculated for
     * a given aspect ratio.
     */
    virtual void paint(QPainter *painter, QRectF target) = 0;

    /** Destructor. */
    virtual ~AbstractVideoGraphicsPainter() { }

    bool inited() const { return _inited; }

protected:
    AbstractVideoGraphicsPainter() : _frame(0), _inited(false) { }

    /** The frame an implementatin is supposed to work with. */
    const VideoFrame *_frame;

    /** Whether or not the painter was inited */
    bool _inited;
};

#endif // VLCQT_PHONON_ABSTRACTVIDEOGRAPHICSPAINTER_H_
