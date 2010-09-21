/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* SeekWidget.h: Seek widget
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#ifndef VLCQT_SEEKWIDGET_H_
#define VLCQT_SEEKWIDGET_H_

#include <QtCore/QTimer>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QWidget>

/*!
	\class VlcSeekWidget SeekWidget.h vlc-qt/SeekWidget.h
	\brief Seek widget

	This is one of VLC-Qt GUI classes.
	It provides only a display of elapsed time and full time of the media.
*/
class VlcSeekWidget : public QWidget
{
Q_OBJECT
public:
	/*!
		\brief VlcSeekWidget constructor
		\param parent seek widget's parent GUI widget (QWidget)
	*/
	VlcSeekWidget(QWidget *parent = 0);

	/*!
		VlcSeekWidget destructor
	*/
	~VlcSeekWidget();


private slots:
	void changeTime();
	void updateTime();

private:
	QSlider *_seek;
	QLabel *_labelElapsed;
	QLabel *_labelFull;
	QTimer *_timer;
};

#endif // VLCQT_SEEKWIDGET_H_
