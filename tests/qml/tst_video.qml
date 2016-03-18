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

import QtQuick 2.0
import QtTest 1.0
import VLCQt 1.1

Rectangle {
    width: 640
    height: 480
    color: "black"

    VlcPlayer {
        id: player
        url: "http://download.blender.org/peach/bigbuckbunny_movies/big_buck_bunny_480p_surround-fix.avi"
    }
    VlcVideoOutput {
        id: video
        source: player
        anchors.fill: parent
    }

    TestCase {
        id: tc1
        name: "FillMode"
        when: windowShown

        function test_fillMode() {
            wait(3000)
            video.fillMode = Vlc.PreserveAspectCrop
            wait(500)
            video.fillMode = Vlc.Stretch
            wait(500)
            video.fillMode = Vlc.PreserveAspectFit
            wait(2000)
        }
    }
}
