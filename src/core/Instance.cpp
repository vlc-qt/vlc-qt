/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Instance.cpp: Main libvlc instance
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

#include <QtCore/QDebug>
#include <QtGui/QMessageBox>

#include "Config.h"
#include "core/Error.h"
#include "core/Instance.h"

libvlc_instance_t *_vlcInstance = NULL;

VlcInstance::VlcInstance(const QList<const char *> &args,
						 QObject *parent)
	: QObject(parent)
{
	// Convert arguments to required format
	const char *vlcArgs[args.size()];
	for(int i=0; i<args.size(); i++)
		vlcArgs[i] = args[i];

	// Create new libvlc instance
	_vlcInstance = libvlc_new(sizeof(vlcArgs) / sizeof(*vlcArgs), vlcArgs);

	VlcError::errmsg();

	// Check if instance is running
	if(_vlcInstance) {
		qDebug() << "libvlc-qt" << libVersion() << "initialised";
		qDebug() << "Using libvlc version:" << version();
		qDebug() << "libvlc loaded";
	} else {
		qDebug() << "libvlc-qt Error: libvlc failed to load!";
		exit(-100);
	}
}

VlcInstance::~VlcInstance()
{
	libvlc_release(_vlcInstance);
}

QString VlcInstance::libVersion()
{
	QString version;
#ifdef LIBVLCQT_VERSION
	version.append(QString(LIBVLCQT_VERSION));
#else
	version.append(QString("Unknown"));
#endif //LIBVLCQT_VERSION

#ifdef LIBVLCQT_VERSION_PATCH
	if(QString(LIBVLCQT_VERSION_PATCH) != "0" && QString(LIBVLCQT_VERSION_PATCH) != "") {
		version.append("-" + QString(LIBVLCQT_VERSION_PATCH));
	}
#endif //LIBVLCQT_VERSION

	return version;
}

QString VlcInstance::changeset()
{
	// Returns libvlc changeset
	return QString(libvlc_get_changeset());
}

QString VlcInstance::compiler()
{
	// Returns libvlc compiler version
	return QString(libvlc_get_compiler());
}

QString VlcInstance::version()
{
	// Returns libvlc version
	return QString(libvlc_get_version());
}

void VlcInstance::setUserAgent(const QString &application,
							   const QString &version)
{
	QString applicationOutput = application + " " + version;
	QString httpOutput = application + "/" + version + " " + "libvlc-qt" + "/" + libVersion(); // "AppName/1.2.3 libvlc-qt/1.2.3"
	libvlc_set_user_agent(_vlcInstance, applicationOutput.toAscii().data(), httpOutput.toAscii().data());
}
