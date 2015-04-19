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

#ifndef VLCQT_TEST_METAMANAGER_H_
#define VLCQT_TEST_METAMANAGER_H_

// QtGui/QtWidgets
#include <QDialog>

class VlcInstance;
class VlcMedia;
class VlcMetaManager;

namespace Ui {
    class MetaManager;
}

class MetaManager : public QDialog
{
    Q_OBJECT
public:
    explicit MetaManager(QWidget *parent = 0);
    ~MetaManager();

private slots:
    void open();
    void read();
    void save();
    void set();

private:
    Ui::MetaManager *ui;

    VlcInstance *_instance;
    VlcMedia *_media;
    VlcMetaManager *_meta;
};

#endif //VLCQT_TEST_METAMANAGER_H_
