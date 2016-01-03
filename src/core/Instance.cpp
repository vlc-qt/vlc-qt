/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#include <QtCore/QDebug>
#include <QtCore/QStringList>

#include <vlc/vlc.h>

#include "Config.h"
#include "core/Enums.h"
#include "core/Error.h"
#include "core/Instance.h"
#include "core/ModuleDescription.h"

VlcInstance::VlcInstance(const QStringList &args,
                         QObject *parent)
    : QObject(parent),
      _vlcInstance(0),
      _status(false)
{
// Convert arguments to required format
#if defined(Q_OS_WIN32) // Will be removed on Windows if confirmed working
    char **argv = (char **)malloc(sizeof(char **) * args.count());
    for (int i = 0; i < args.count(); ++i)
        argv[i] = (char *)qstrdup(args.at(i).toUtf8().data());
#else
    char *argv[args.count()];
    for (int i = 0; i < args.count(); ++i)
        argv[i] = (char *)qstrdup(args.at(i).toUtf8().data());
#endif

    // Create new libvlc instance
    _vlcInstance = libvlc_new(args.count(), argv);

    qRegisterMetaType<Vlc::Meta>("Vlc::Meta");
    qRegisterMetaType<Vlc::State>("Vlc::State");

    VlcError::showErrmsg();

    // Check if instance is running
    if(_vlcInstance) {
        _status = true;
        qDebug() << "VLC-Qt" << libVersion() << "initialised";
        qDebug() << "Using libvlc version:" << version();
    } else {
        qCritical() << "VLC-Qt Error: libvlc failed to load!";
    }
}

VlcInstance::~VlcInstance()
{
    if (_status && _vlcInstance) {
        libvlc_release(_vlcInstance);
    }
}

libvlc_instance_t *VlcInstance::core()
{
    return _vlcInstance;
}

bool VlcInstance::status() const
{
    return _status;
}

QString VlcInstance::libVersion()
{
    QString version;
#if defined(LIBVLCQT_VERSION)
    version.append(QString(LIBVLCQT_VERSION));
#else
    version.append(QString("Unknown"));
#endif //LIBVLCQT_VERSION

#if defined(LIBVLCQT_VERSION_VCS)
    if(QString(LIBVLCQT_VERSION_VCS) != "0" && QString(LIBVLCQT_VERSION_VCS) != "") {
        version.append("-" + QString(LIBVLCQT_VERSION_VCS));
    }
#endif //LIBVLCQT_VERSION

    return version;
}

int VlcInstance::libVersionMajor()
{
    int version = -1;
#if defined(LIBVLCQT_VERSION_MAJOR)
    version = LIBVLCQT_VERSION_MAJOR;
#endif //LIBVLCQT_VERSION

    return version;
}

int VlcInstance::libVersionMinor()
{
    int version = -1;
#if defined(LIBVLCQT_VERSION_MINOR)
    version = LIBVLCQT_VERSION_MINOR;
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
    QString httpOutput = application + "/" + version + " " + "VLC-Qt" + "/" + libVersion(); // "AppName/1.2.3 VLC-Qt/1.2.3"
    libvlc_set_user_agent(_vlcInstance, applicationOutput.toUtf8().data(), httpOutput.toUtf8().data());
}

QList<VlcModuleDescription *> VlcInstance::audioFilterList() const
{
    libvlc_module_description_t *original = libvlc_video_filter_list_get(_vlcInstance);
    if (original == NULL) {
        return QList<VlcModuleDescription *>();
    }

    libvlc_module_description_t *list = original;
    QList<VlcModuleDescription *> audioFilters;
    do {
        VlcModuleDescription *module = new VlcModuleDescription(VlcModuleDescription::AudioFilter, list->psz_name);
        module->setLongName(list->psz_longname);
        module->setShortName(list->psz_shortname);
        module->setHelp(list->psz_help);
        audioFilters << module;

        list = list->p_next;
    } while (list->p_next);

    libvlc_module_description_list_release(original);

    return audioFilters;
}

QList<VlcModuleDescription *> VlcInstance::videoFilterList() const
{
    libvlc_module_description_t *original = libvlc_video_filter_list_get(_vlcInstance);
    if (original == NULL) {
        return QList<VlcModuleDescription *>();
    }

    libvlc_module_description_t *list = original;
    QList<VlcModuleDescription *> videoFilters;
    do {
        VlcModuleDescription *module = new VlcModuleDescription(VlcModuleDescription::VideoFilter, list->psz_name);
        module->setLongName(list->psz_longname);
        module->setShortName(list->psz_shortname);
        module->setHelp(list->psz_help);
        videoFilters << module;

        list = list->p_next;
    } while (list->p_next);

    libvlc_module_description_list_release(original);

    return videoFilters;
}
