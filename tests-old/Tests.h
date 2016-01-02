/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#ifndef VLCQT_TESTS_H_
#define VLCQT_TESTS_H_

// QtGui/QtWidgets
#include <QMainWindow>

#if QT_VERSION >= 0x050000
    #include <QtQuick/QQuickView>
#endif

namespace Ui
{
    class Tests;
}

class DualInstance;
class DualPlayer;
class MediaList;
class Player;

class Tests : public QMainWindow
{
Q_OBJECT
public:
    explicit Tests(QWidget *parent = 0);
    ~Tests();

public:
    void test();

private slots:
    void dualInstance();
    void dualPlayer();
    void mediaList();
    void metaManager();
    void player();
    void qml();
    void recorder();

private:
    Ui::Tests *ui;

#if QT_VERSION >= 0x050000
    QQuickView *_quickView;
#endif

    DualInstance *_testDualInstance;
    DualPlayer *_testDualPlayer;
    MediaList *_testMediaList;
    Player *_testPlayer;
};

#endif // VLCQT_TESTS_H_
