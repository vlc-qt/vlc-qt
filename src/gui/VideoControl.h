/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* VideoControl.h: Video and subtitles controller
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

#ifndef VLCQT_VIDEOCONTROL_H_
#define VLCQT_VIDEOCONTROL_H_

#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QTimer>
#include <QtGui/QAction>
#include <QtGui/QActionGroup>

/*!
	\classVlc VideoControl VideoControl.h vlc-qt/VideoControl.h
	\brief Video control class

	This is one of VLC-Qt control classes.
	It provides video and subtitle tracks management.
*/
class VlcVideoControl : public QObject
{
Q_OBJECT
public:
	/*!
		VideoControl constructor
		\param lang default subtitle language
		\param parent video controller's parent object
	*/
	VlcVideoControl(const QString &lang = 0,
					QObject *parent = 0);

	/*!
		VideoControl destructor
	*/
	~VlcVideoControl();


	/*!
		Open and load subtitles from file
		\param sub full path to subtitles file
	*/
	void loadSubtitle(const QString &sub);

	/*!
		Reset all settings and selected video and subtitle tracks
		Usually called on media change.
	*/
	void reset();

	/*!
		Set default subtitle language
		\param lang comma separated languages
	*/
	void setDefaultSubtitleLanguage(const QString &lang);


signals:
	/*!
		Signal sending actions for changing video and subititle tracks
		\param QString type of actions
		\param QList<QAction*> list of actions
	*/
	void actions(const QString,
				 QList<QAction*>);


private slots:
	void updateSubtitleActions();
	void updateSubtitles();
	void updateVideoActions();
	void updateVideo();

private:
	QTimer *_timer;

	QList<QAction*> _actionSubList;
	QMap<QString,int> _mapSub;
	QActionGroup *_actionSubGroup;

	QList<QAction*> _actionVideoList;
	QMap<QString,int> _mapVideo;
	QActionGroup *_actionVideoGroup;

	bool _manualLanguage;
	QStringList _preferedLanguage;
};

#endif // VLCQT_VIDEOCONTROL_H_
