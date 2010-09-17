/****************************************************************************
* VLC-Qt - Qt and libVLC connector library
* VideoWidget.h: Video widget
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

#ifndef VLCQT_VIDEOWIDGET_H_
#define VLCQT_VIDEOWIDGET_H_

#include <QtCore/QTimer>
#include <QtGui/QWidget>

/*! \class VideoWidget VideoWidget.h vlc-qt/VideoWidget.h
	\brief Video widget

	This is one of VLC-Qt GUI classes.
	It provides video display and mouse control.
*/
class VlcVideoWidget : public QWidget
{
Q_OBJECT
public:
	/*!
		VideoWidget constructor
		\param parent video widget's parent GUI widget
	*/
	VlcVideoWidget(QWidget *parent = 0);

	/*!
		VideoWidget destructor
	*/
	~VlcVideoWidget();


	/*!
		Get unique video widget ID to set it in the instance
		\return widget ID
		\sa Instance::Instance()
	*/
	WId widgetId() {return _widget->winId();};

	/*!
		Set OSD size and location
		\param width OSD width
		\param height OSD height
		\param x OSD x coordinate
		\param y OSD y coordinate
	*/
	void setOsdParameters(const int &width, const int &height, const int &x = 0, const int y = 0);


protected:
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);

signals:
	/*!
		Signal sending fullscreen request
	*/
	void fullscreen();

	/*!
		Signal sending right click and it's location
		\param QPoint right click location
	*/
	void rightClick(const QPoint);

	/*!
		Signal sending mouse wheel direction
		\param bool true if up
	*/
	void wheel(const bool);

	/*!
		Signal sending if mouse moved
	*/
	void mouseMove();

	/*!
		Signal sending wanted OSD visibility
		\param bool true if visible
	*/
	void osdVisibility(const bool);


public slots:
	/*!
		Enable mouse hide
	*/
	void enableMouseHide() { _hide = true; };
	/*!
		Disable mouse hide
	*/
	void disableMouseHide() { _hide = false; };

	/*!
		Toggle fullscreen
	*/
	void toggleFullscreen();

	/*!
		Show teletext
	*/
	void teletext();
	/*!
		Get current teletext page
		\return current page
	*/
	int teletextPage();
	/*!
		Set teletext page
		\param page teletext page
	*/
	void setTeletextPage(const int &page);

	/*!
		Set previous video settings (crop, ratio, deinterlacing filter)
	*/
	void setPreviousSettings();

	/*!
		Set ratio: Original
	*/
	void setRatioOriginal();
	/*!
		Set ratio: 1:1
	*/
	void setRatio1_1();
	/*!
		Set ratio: 4:3
	*/
	void setRatio4_3();
	/*!
		Set ratio: 16:9
	*/
	void setRatio16_9();
	/*!
		Set ratio: 16:10
	*/
	void setRatio16_10();
	/*!
		Set ratio: 2.21:1
	*/
	void setRatio2_21_1();
	/*!
		Set ratio: 5:4
	*/
	void setRatio5_4();

	/*!
		Set crop: Original
	*/
	void setCropOriginal();
	/*!
		Set crop: 16:9
	*/
	void setCrop16_9();
	/*!
		Set crop: 16:10
	*/
	void setCrop16_10();
	/*!
		Set crop: 1.85:1
	*/
	void setCrop1_85_1();
	/*!
		Set crop: 2.21:1
	*/
	void setCrop2_21_1();
	/*!
		Set crop: 2.35:1
	*/
	void setCrop2_35_1();
	/*!
		Set crop: 2.39:1
	*/
	void setCrop2_39_1();
	/*!
		Set crop: 5:4
	*/
	void setCrop5_4();
	/*!
		Set crop: 5:3
	*/
	void setCrop5_3();
	/*!
		Set crop: 4:3
	*/
	void setCrop4_3();
	/*!
		Set crop: 1:1
	*/
	void setCrop1_1();

	/*!
		Set deinterlace filter: Disabled
	*/
	void setFilterDisabled();
	/*!
		Set deinterlace filter: Discard
	*/
	void setFilterDiscard();
	/*!
		Set deinterlace filter: Blend
	*/
	void setFilterBlend();
	/*!
		Set deinterlace filter: Mean
	*/
	void setFilterMean();
	/*!
		Set deinterlace filter: Bob
	*/
	void setFilterBob();
	/*!
		Set deinterlace filter: Linear
	*/
	void setFilterLinear();
	/*!
		Set deinterlace filter: X
	*/
	void setFilterX();


private slots:
	void hideMouse();
	void applyPreviousSettings();

private:
	QWidget *_widget;
	QTimer *_timerMouse;
	QTimer *_timerSettings;

	bool _hide;

	int _desktopWidth;
	int _desktopHeight;

	int _osdWidth;
	int _osdHeight;

	QString _currentRatio;
	QString _currentCrop;
	QString _currentFilter;
};

#endif // VLCQ_VIDEOWIDGET_H_
