/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2016 Tadej Novak <tadej@tano.si>
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

#include <QtTest/QtTest>

#include "TestsConfig.h"
#include "TestsCommon.h"

#include "core/Common.h"
#include "core/Instance.h"

void TestsCommon::init()
{
    qunsetenv("VLC_PLUGIN_PATH");

#ifndef Q_OS_DARWIN
    VlcCommon::setPluginPath(QString(LIBVLC_PLUGINS_DIR));
#endif

    _instance = new VlcInstance(VlcCommon::args(), this);
    _instance->setLogLevel(Vlc::DebugLevel);
}

void TestsCommon::cleanup()
{
    delete _instance;
}
