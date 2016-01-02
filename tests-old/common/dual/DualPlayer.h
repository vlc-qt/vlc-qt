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

#ifndef VLCQT_TEST_DUALPLAYER_H_
#define VLCQT_TEST_DUALPLAYER_H_

// QtGui/QtWidgets
#include <QMainWindow>

namespace Ui {
    class Dual;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class DualPlayer : public QMainWindow
{
    Q_OBJECT
public:
    explicit DualPlayer(QWidget *parent = 0);
    ~DualPlayer();

private slots:
    void open1();
    void open2();

private:
    Ui::Dual *ui;

    VlcInstance *_instance;

    VlcMedia *_media1;
    VlcMediaPlayer *_player1;

    VlcMedia *_media2;
    VlcMediaPlayer *_player2;
};

#endif // VLCQT_TEST_DUALPLAYER_H_
