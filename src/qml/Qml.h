/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_QML_H_
#define VLCQT_QML_H_

#include "SharedExportQml.h"

/*!
    \defgroup VLCQtQml VLC-Qt Qml (VLCQtQml)
    \brief QML classes for controlling video and media playback
 */

namespace VlcQml {
    /*!
        \brief Register QML types as VLCQt

        Intended for use without plugin.

        Include into QML file as
        import VLCQt VERSION_MAJOR.VERSION_MINOR

        Object names: VlcPlayer, VlcVideoObject

        \since VLC-Qt 1.1
     */
    VLCQT_QML_EXPORT void registerTypes();
}

#endif // VLCQT_QML_H_
