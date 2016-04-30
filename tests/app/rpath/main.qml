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

import QtQuick 2.3
import QtQuick.Window 2.2
import VLCQt 1.1

Window {
    visible: true
    color: "black"

    width: 300
    height: 300

    VlcPlayer {
        id: vlcPlayer
    }
    VlcVideoOutput {
        source: vlcPlayer
        anchors.fill: parent
    }

    Timer {
        interval: 1000; running: true; repeat: false
        onTriggered: Qt.quit()
    }
}
