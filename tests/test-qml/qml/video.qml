/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
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
import QtGraphicalEffects 1.0
import VLCQt 0.9

Rectangle {
    id: root
    width: 640
    height: 480
    color: "black"

    function toggleControls()
    {
        if( ( viewer.isFullscreen == false && globalMouseArea.containsMouse == false) || ( viewer.isFullscreen == true && controlsTimer.running == false && controlsMouseArea.containsMouse == false ) )
        {
            controls.state = "hidden";
        }
        else
        {
            controls.state = "normal"
        }
    }

    MouseArea {
        id: globalMouseArea
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.ArrowCursor
        onDoubleClicked: {
            viewer.toggleFullscreen();
            toggleControls();
        }
        onPositionChanged: {
            cursorShape = Qt.ArrowCursor
            toggleControls();
            controlsTimer.start();
        }
        onContainsMouseChanged: {
            toggleControls();
        }
        onWheel: {
            volumeSlider.setValue( volumeSlider.value + wheel.angleDelta.y / 8 )
        }
        onClicked: {
            //controls.updateControlsProgress();
        }

        VlcVideoPlayer {
            id: vidwidget
            anchors.fill: parent
            aspectRatio: Vlc.Original
            cropRatio: Vlc.Original
            autoplay: true
            url: "http://download.blender.org/peach/bigbuckbunny_movies/BigBuckBunny_640x360.m4v"
            volume: volumeSlider.value
            position: ( positionSlider.value / 100 )
            deinterlacing: Vlc.Disabled;

            onTimeChanged: {
                var d = new Date( vidwidget.time );
                var hours = d.getUTCHours();
                var minutes = d.getUTCMinutes();
                var seconds = d.getUTCSeconds();
                var text = "";
                if( hours > 0 )
                    text = ( hours < 10 ? "0" + hours : hours ) + ":";
                text += ( minutes < 10 ? "0" + minutes : minutes ) + ":" + ( seconds < 10 ? "0" + seconds : seconds );
                timeText.text = text;
            }

            onLengthChanged: {
                if( vidwidget.length > 0 )
                {
                    var d = new Date( vidwidget.length );
                    var hours = d.getUTCHours();
                    var minutes = d.getUTCMinutes();
                    var seconds = d.getUTCSeconds();
                    var text = " / ";
                    if( hours > 0 )
                        text += ( hours < 10 ? "0" + hours : hours ) + ":";
                    text += ( minutes < 10 ? "0" + minutes : minutes ) + ":" + ( seconds < 10 ? "0" + seconds : seconds );
                    timeText.text = text;
                    timeElapsedText.text = text;
                }
                else
                {
                    timeElapsedText.text = "";
                }
            }

            onPositionChanged: {
                positionSlider.setBarX( vidwidget.position * 100 );
            }
        }

        Rectangle {
            id: controls

            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }
            height: 45
            color: "#1a1a1a"
            opacity: 0.8

            MouseArea {
                id: controlsMouseArea
                anchors.fill: parent
                hoverEnabled: true

                MouseArea {
                    id: playPauseButton
                    width: 11
                    height: 12
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    hoverEnabled: true;
                    onClicked: {
                        if( playPauseButtonImage.state == "playing" )
                        {
                            vidwidget.pause();
                            bubble.show(playPauseButton,"Play");
                        }
                        else
                        {
                            vidwidget.play();
                            bubble.show(playPauseButton,"Pause");
                        }
                    }
                    onEntered: {
                        if( playPauseButtonImage.state == "playing" )
                            bubble.show(playPauseButton,"Pause");
                        else
                            bubble.show(playPauseButton,"Play");
                    }
                    onExited: {
                        bubble.hide();
                    }
                    Image {
                        id: playPauseButtonImage
                        anchors.fill: parent
                        source: "images/pl_play.png"
                        cache: false
                        states: [
                            State {
                                name: "playing"; when: vidwidget.state == Vlc.Playing;
                                PropertyChanges { target: playPauseButtonImage; source: "images/pl_pause.png" }
                            }
                        ]
                    }
                    BrightnessContrast {
                        id: playPauseButtonEffect
                        anchors.fill: playPauseButton
                        source: playPauseButtonImage
                        brightness: 0
                        contrast: 0
                    }
                    states: [
                        State {
                            name: "hover";
                            when: playPauseButton.containsMouse == true
                            PropertyChanges { target: playPauseButtonEffect; brightness: 0.5 }
                        }
                    ]
                }
                Slider {
                    id: positionSlider
                    anchors.left: playPauseButton.right
                    anchors.leftMargin: 15
                    anchors.right: timeText.left
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter

                    init: 0
                    min: 0
                    max: 100
                }
                Text {
                    id: timeText
                    anchors.right: timeElapsedText.left
                    anchors.verticalCenter: parent.verticalCenter
                    color: "white"
                    font.family: "Tahoma"
                    font.pixelSize: 12
                }
                Text {
                    id: timeElapsedText
                    anchors.right: muteButton.left
                    anchors.rightMargin: 25
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#989898"
                    font.family: "Tahoma"
                    font.pixelSize: 12
                }

                MouseArea {
                    id: muteButton
                    property int lastVolume: 0
                    width: 18
                    height: 13
                    anchors.right: volumeSlider.left
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    hoverEnabled: true;
                    onClicked: {
                        if( muteButtonImage.state == "mute" )
                        {
                            volumeSlider.setValue( lastVolume );
                            lastVolume = 0;
                            bubble.show(muteButton,"Mute");
                        }
                        else
                        {
                            lastVolume = volumeSlider.value;
                            volumeSlider.setValue(0);
                            bubble.show(muteButton,"Unmute");
                        }
                    }
                    onEntered: {
                        if( muteButtonImage.state == "mute" )
                            bubble.show(muteButton,"Unmute");
                        else
                            bubble.show(muteButton,"Mute");
                    }
                    onExited: {
                        bubble.hide();
                    }
                    Image {
                        id: muteButtonImage
                        anchors.fill: parent
                        source: "images/pl_vol_on.png"
                        cache: false
                        states: [
                            State {
                                name: "mute"; when: volumeSlider.value < 5;
                                PropertyChanges { target: muteButtonImage; source: "images/pl_vol_off.png" }
                            }
                        ]
                    }
                    BrightnessContrast {
                        id: muteButtonEffect
                        anchors.fill: muteButton
                        source: muteButtonImage
                        brightness: 0
                        contrast: 0
                    }
                    states: [
                        State {
                            name: "hover";
                            when: muteButton.containsMouse == true
                            PropertyChanges { target: muteButtonEffect; brightness: 0.5 }
                        }
                    ]
                }
                Slider {
                    id: volumeSlider
                    anchors.right: aspectButton.left
                    anchors.rightMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    width: 70
                    init: 50
                    min: 0
                    max: 100
                }
                MouseArea {
                    id: aspectButton
                    width: 18
                    height: 13
                    anchors.right: fullsrceenButton.left
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    hoverEnabled: true;
                    onClicked: {
                        nextState();
                        bubble.show(aspectButton,"Image size (" + state + ")");
                    }
                    onEntered: {
                        bubble.show(aspectButton,"Image size (" + state + ")");
                    }
                    onExited: {
                        bubble.hide();
                    }
                    Image {
                        id: aspectButtonImage
                        anchors.fill: parent
                        source: "images/pl_aspect.png"
                        cache: false
                        states: [
                            State {
                                name: "hover";
                                when: aspectButton.containsMouse == true
                                PropertyChanges { target: aspectButtonEffect; brightness: 0.5 }
                            }
                        ]
                    }
                    BrightnessContrast {
                        id: aspectButtonEffect
                        anchors.fill: aspectButton
                        source: aspectButtonImage
                        brightness: 0
                        contrast: 0
                    }

                    state: "Original"
                    states: [
                        State {
                            name: "Original"
                            PropertyChanges { target: vidwidget; cropRatio: Vlc.Original }
                        },
                        State {
                            name: "16:9"
                            PropertyChanges { target: vidwidget; cropRatio: Vlc.R_16_9 }
                        },
                        State {
                            name: "4:3"
                            PropertyChanges { target: vidwidget; cropRatio: Vlc.R_4_3 }
                        }
                    ]

                    function nextState() {
                        if( state == "Original" )
                            state = "4:3";
                        else if( state == "4:3" )
                            state = "16:9";
                        else if( state == "16:9" )
                            state = "Original";
                    }
                }
                MouseArea {
                    id: fullsrceenButton
                    width: 18
                    height: 13
                    anchors.right: parent.right
                    anchors.rightMargin: 16
                    anchors.verticalCenter: parent.verticalCenter
                    hoverEnabled: true;
                    onClicked: {
                        viewer.toggleFullscreen();
                    }
                    onEntered: {
                        if( fullsrceenButtonImage.state == "fullscreen" )
                            bubble.show(fullsrceenButton,"Window mode");
                        else
                            bubble.show(fullsrceenButton,"Fullscreen mode");
                    }
                    onExited: {
                        bubble.hide();
                    }
                    Image {
                        id: fullsrceenButtonImage
                        anchors.fill: parent
                        source: "images/pl_screen_small.png"
                        cache: false
                        states: [
                            State {
                                name: "fullscreen"; when: viewer.isFullscreen == true;
                                PropertyChanges { target: fullsrceenButtonImage; source: "images/pl_screen_full.png" }
                            }
                        ]
                    }
                    BrightnessContrast {
                        id: fullsrceenButtonEffect
                        anchors.fill: fullsrceenButton
                        source: fullsrceenButtonImage
                        brightness: 0
                        contrast: 0
                    }
                    states: [
                        State {
                            name: "hover";
                            when: fullsrceenButton.containsMouse == true
                            PropertyChanges { target: fullsrceenButtonEffect; brightness: 0.5 }
                        }
                    ]
                }
            }

            states: [
                State {
                    name: "normal";
                    PropertyChanges {
                        target: controls
                        opacity: 0.8
                    }
                },
                State {
                    name: "hidden";
                    PropertyChanges {
                        target: controls
                        opacity: 0
                    }
                }
            ]
            Behavior on opacity {
                NumberAnimation { duration: 100 }
            }
        }
    }
    Timer {
        id: controlsTimer
        interval: 2000
        repeat: false
        onTriggered: {
                toggleControls();
                globalMouseArea.cursorShape = Qt.BlankCursor
        }
    }
    Bubble {
        id: bubble
    }
}
