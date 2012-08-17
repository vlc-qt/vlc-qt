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

#ifndef VLCQT_VLCINSTANCE_H_
#define VLCQT_VLCINSTANCE_H_

#include <QtCore/QObject>

#include "SharedExport.h"

struct libvlc_instance_t;

/*!
    \class VlcInstance Instance.h vlc-qt/Instance.h
    \brief Main instance

    A basic Instance manager for VLC-Qt library.
    It provides main instance controls.
*/
class VLCQT_EXPORT VlcInstance : public QObject
{
Q_OBJECT
public:
    /*!
        \brief VlcInstance constructor.

        This is mandatory for using VLC-Qt and all its other classes.

        \param args libvlc arguments (QStringList)
        \param parent Instance's parent object (QObject *)
    */
    explicit VlcInstance(const QStringList &args,
                         QObject *parent = NULL);

    /*!
        VlcInstance destructor
    */
    ~VlcInstance();

    /*!
        \brief Returns libvlc instance object.
        \return libvlc instance (libvlc_instance_t *)
    */
    libvlc_instance_t *core();

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

private:
    libvlc_instance_t *_vlcInstance;
};

#endif // VLCQT_VLCINSTANCE_H_
