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

#ifndef VLCQT_TEST_MEDIALIST_H_
#define VLCQT_TEST_MEDIALIST_H_

// QtGui/QtWidgets
#include <QMainWindow>

#include "Config.h"

namespace Ui {
    class MediaList;
}

class VlcInstance;
class VlcMediaList;
class VlcMediaListPlayer;
class VlcMediaPlayer;

class MediaList : public QMainWindow
{
    Q_OBJECT
public:
    explicit MediaList(QWidget *parent = 0);
    ~MediaList();

private:
    Ui::MediaList *ui;

    VlcInstance *_instance;
    VlcMediaList *_mediaList;
    VlcMediaListPlayer *_listPlayer;
    VlcMediaPlayer *_player;
};

#endif // VLCQT_TEST_MEDIALIST_H_
