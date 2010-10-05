/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Instance.h: Main libvlc instance
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

#ifndef VLCQT_VLCINSTANCE_H_
#define VLCQT_VLCINSTANCE_H_

#include <QtCore/QObject>
#include <vlc/vlc.h>

#include "Config.h"

extern libvlc_instance_t *_vlcInstance;

/*!
	\class VlcInstance Instance.h vlc-qt/Instance.h
	\brief Main instance

	A basic Instance manager for VLC-Qt library.
	It provides main instance controls.
*/
class VlcInstance : public QObject
{
Q_OBJECT
public:
	/*!
		\brief VlcInstance constructor.

		This is mandatory for using VLC-Qt and all its other classes.

		\param args libvlc arguments (QList<const char *>)
		\param parent Instance's parent object (QObject)
	*/
	VlcInstance(const QList<const char *> &args,
				QObject *parent = NULL);

	/*!
		VlcInstance destructor
	*/
	~VlcInstance();

	/*!
		\brief VLC-QT version info

		\return a string containing the VLC-Qt version (QString)
	*/
	static QString libVersion();

	/*!
		\brief libvlc version info

		\return a string containing the libvlc version (QString)
	*/
	static QString version();

	/*!
		\brief libvlc compiler info

		\return a string containing the compiler version (QString)
	*/
	static QString compiler();

	/*!
		\brief libvlc changeset info

		\return a string containing the changeset (QString)
	*/
	static QString changeset();

	/*!
		\brief Sets the application name.

		libvlc passes this as the user agent string when a protocol requires it.

		\param application Application name (QString)
		\param version Application version (QString)
	*/
	void setUserAgent(const QString &application,
					  const QString &version);
};

#endif // VLCQT_VLCINSTANCE_H_
