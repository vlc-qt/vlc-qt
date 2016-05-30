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

#ifndef VLCQT_TEST_PLAYER_H_
#define VLCQT_TEST_PLAYER_H_

#include <QMainWindow>

namespace Ui
{
    class Player;
}

class VlcInstance;
class VlcMedia;
class VlcMediaPlayer;

class Player : public QMainWindow
{
    Q_OBJECT
public:
    explicit Player(VlcInstance *instance,
                    QWidget *parent = 0);
    ~Player();

private:
    Ui::Player *ui;

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMediaPlayer *_player;
};

#endif // VLCQT_TEST_PLAYER_H_
