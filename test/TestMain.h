/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2010 Tadej Novak <ntadej@users.sourceforge.net>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef VLCQT_TEST_MAIN_H_
#define VLCQT_TEST_MAIN_H_

#include <QtGui/QMainWindow>

namespace Ui
{
	class TestMain;
}

class TestMain : public QMainWindow
{
Q_OBJECT
public:
	TestMain(QWidget *parent = 0);
	~TestMain();

private slots:
	void metaManagerTest();
	void recorderTest();

private:
	Ui::TestMain *ui;
};

#endif // VLCQT_TEST_MAIN_H_
