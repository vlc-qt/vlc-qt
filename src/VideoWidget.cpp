/****************************************************************************
* VLC-Qt - Qt and libVLC connector library
* VideoWidget.cpp: Video widget
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

#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMouseEvent>
#include <QtGui/QToolBar>

#include "core/Error.h"
#include "core/MediaPlayer.h"
#include "VideoWidget.h"

VlcVideoWidget::VlcVideoWidget(QWidget *parent) :
	QWidget(parent),
	_hide(true),
	_desktopWidth(QApplication::desktop()->width()), _desktopHeight(QApplication::desktop()->height()),
	_osdWidth(0), _osdHeight(0),
	_currentRatio(""), _currentCrop(""), _currentFilter("")
{
	setMouseTracking(true);

	_widget = new QWidget(this);
	_widget->setMouseTracking(true);

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(_widget);
	setLayout(layout);

	_timerMouse = new QTimer(this);
	connect(_timerMouse, SIGNAL(timeout()), this, SLOT(hideMouse()));
	_timerSettings = new QTimer(this);
	connect(_timerSettings, SIGNAL(timeout()), this, SLOT(applyPreviousSettings()));
}

VlcVideoWidget::~VlcVideoWidget()
{
	delete _timerMouse;
	delete _timerSettings;
	delete _widget;
}

void VlcVideoWidget::setOsdParameters(const int &width, const int &height, const int &x, const int y)
{
	_osdWidth = width;
	_osdHeight = height;
}

//Events:
void VlcVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	event->ignore();
	emit fullscreen();
}
void VlcVideoWidget::mouseMoveEvent(QMouseEvent *event)
{
	event->ignore();

	if(isFullScreen() && _hide) {
		qApp->setOverrideCursor(Qt::ArrowCursor);
		emit osdVisibility(true);

		if(event->globalPos().y() >= _desktopHeight-_osdHeight) {
			_timerMouse->stop();
		} else {
			_timerMouse->start(1000);
		}
	}
}
void VlcVideoWidget::mousePressEvent(QMouseEvent *event)
{
	event->ignore();

	if(event->button() == Qt::RightButton) {
		qApp->setOverrideCursor(Qt::ArrowCursor);
		emit rightClick(event->globalPos());
	}
}
void VlcVideoWidget::wheelEvent(QWheelEvent *event)
{
	event->ignore();

	if(event->delta()>0)
		emit wheel(true);
	else
		emit wheel(false);
}

void VlcVideoWidget::hideMouse()
{
	if(isFullScreen() && _hide) {
		qApp->setOverrideCursor(Qt::BlankCursor);
		emit osdVisibility(false);
		_timerMouse->stop();
	}
}

void VlcVideoWidget::toggleFullscreen()
{
	Qt::WindowFlags flags = windowFlags();
	if (!isFullScreen()) {
		flags |= Qt::Window;
		flags ^= Qt::SubWindow;
		setWindowFlags(flags);
#ifdef Q_WS_X11
		// This works around a bug with Compiz
		// as the window must be visible before we can set the state
		show();
		raise();
		setWindowState( windowState() | Qt::WindowFullScreen );
#else
		setWindowState( windowState() | Qt::WindowFullScreen );
		show();
#endif
	} else if (isFullScreen()) {
		flags ^= (Qt::Window | Qt::SubWindow);
		setWindowFlags(flags);
		setWindowState( windowState() ^ Qt::WindowFullScreen );
		qApp->setOverrideCursor(Qt::ArrowCursor);
		show();
	}
}

void VlcVideoWidget::teletext()
{
	libvlc_toggle_teletext(_vlcCurrentMediaPlayer);

	VlcError::errmsg();
}
int VlcVideoWidget::teletextPage()
{
	return libvlc_video_get_teletext(_vlcCurrentMediaPlayer);

	VlcError::errmsg();
}
void VlcVideoWidget::setTeletextPage(const int &page)
{
	libvlc_video_set_teletext(_vlcCurrentMediaPlayer, page);

	VlcError::errmsg();
}

void VlcVideoWidget::setPreviousSettings()
{
	_timerSettings->start(500);
}
void VlcVideoWidget::applyPreviousSettings()
{
	if(_currentRatio == "" && _currentCrop == "" && _currentFilter == "") {
		_timerSettings->stop();
		return;
	}

	QString success = "";
	if (_vlcCurrentMediaPlayer) {
		if(QString(libvlc_video_get_aspect_ratio(_vlcCurrentMediaPlayer)) != _currentRatio)
			libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, _currentRatio.toAscii().data());
		else
			success.append("+");
		if(QString(libvlc_video_get_crop_geometry(_vlcCurrentMediaPlayer)) != _currentCrop)
			libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, _currentCrop.toAscii().data());
		else
			success.append("+");

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, _currentFilter.toAscii().data());
	}

	if(success == "++")
		_timerSettings->stop();

	VlcError::errmsg();
}

void VlcVideoWidget::setRatioOriginal()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setRatio1_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "1:1";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("1:1").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setRatio4_3()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "4:3";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("4:3").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setRatio16_9()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "16:9";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("16:9").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setRatio16_10()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "16:10";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("16:10").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setRatio2_21_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "221:100";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("221:100").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setRatio5_4()
{
	if (_vlcCurrentMediaPlayer) {
		_currentRatio = "5:4";

		libvlc_video_set_aspect_ratio(_vlcCurrentMediaPlayer, QString("5:4").toAscii().data());

		VlcError::errmsg();
	}
}

void VlcVideoWidget::setCropOriginal()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop16_9()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "16:9";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("16:9").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop16_10()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "16:10";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("16:10").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop1_85_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "185:100";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("185:100").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop2_21_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "221:100";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("221:100").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop2_35_1()
{		_currentCrop = "235:100";
	if (_vlcCurrentMediaPlayer) {

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("235:100").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop2_39_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "239:100";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("239:100").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop5_4()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "5:4";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("5:4").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop5_3()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "5:3";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("5:3").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop4_3()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "4:3";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("4:3").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setCrop1_1()
{
	if (_vlcCurrentMediaPlayer) {
		_currentCrop = "1:1";

		libvlc_video_set_crop_geometry(_vlcCurrentMediaPlayer, QString("1:1").toAscii().data());

		VlcError::errmsg();
	}
}

void VlcVideoWidget::setFilterDisabled()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setFilterDiscard()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "discard";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("discard").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setFilterBlend()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "blend";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("blend").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setFilterMean()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "mean";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("mean").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setFilterBob()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "bob";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("bob").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setFilterLinear()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "linear";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("linear").toAscii().data());

		VlcError::errmsg();
	}
}
void VlcVideoWidget::setFilterX()
{
	if (_vlcCurrentMediaPlayer) {
		_currentFilter = "x";

		libvlc_video_set_deinterlace(_vlcCurrentMediaPlayer, QString("x").toAscii().data());

		VlcError::errmsg();
	}
}
