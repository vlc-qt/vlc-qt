/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.0

Item {
    id:slider
    height: 10
    property real min:0
    property real max:1
    property real value: min
    property real init:min+(max-min)/2

    Component.onCompleted: {
        setValue(init);
    }
    function setValue(v) {
        if( v > max )
            v = max
        else if( v < min )
            v = min
        setBarX(v);
        updateValue();
    }
    function setBarX(v) {
       if (min < max)
          bar.x = v/(max - min) * (foo.width - bar.width);
    }
    function updateValue() {
       value = min + (max - min) * (bar.x / (foo.width - bar.width));
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            setBarX( (max - min) / (foo.width - bar.width) * mouseX );
            updateValue();
        }
        Item {
            id: foo
            height: 2
            width: parent.width
            anchors.verticalCenter:parent.verticalCenter
            anchors.left:parent.left


            Rectangle {
                height: parent.height
                anchors.left: parent.left
                anchors.right: bar.horizontalCenter
				color: "#c7c7c7"
                radius: 3
            }
            Rectangle {
                height: parent.height
                anchors.left: bar.horizontalCenter
                anchors.right: parent.right
                color: "#747474"
                radius: 3
            }
            Rectangle {
                anchors.fill: parent
                color: "transparent"
                radius: 3
            }

            Rectangle {
                id: bar
                width: 10
                height: 10
                y: -4
                radius: 15
                color: "#c7c7c7"
                opacity: 0.9
                MouseArea {
                    anchors.fill: parent
					property variant previousPosition
					onPressed: {
						previousPosition = Qt.point(mouseX, mouseY)
					}
					onPositionChanged: {
						if (pressedButtons == Qt.LeftButton) {
							var newX = bar.x + ( mouseX - previousPosition.x );
							if( newX > 0 && newX < ( foo.width - bar.width ) )
                            {
								bar.x = newX;
                                updateValue();
                            }
						}
					}
                }
            }
        }


    }
}
