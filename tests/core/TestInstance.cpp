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

#include "Config.h"
#include "core/Common.h"
#include "core/Instance.h"

class TestInstance : public QObject
{
    Q_OBJECT
private slots:
    void init();

    void wrongArguments();
    void withExternalPluginsSet();
    void withPlugins();

    void versions();
    void userAgent();
    void appId();
    void filters();
};

void TestInstance::init()
{
    qunsetenv("VLC_PLUGIN_PATH");
}

void TestInstance::wrongArguments()
{
    QStringList wrong;
    wrong << "--something-wrong";
    VlcInstance *instance = new VlcInstance(wrong, this);

    QCOMPARE(instance->status(), false);

    delete instance;
}

void TestInstance::withExternalPluginsSet()
{
    VlcCommon::setPluginPath("something/wrong");
    VlcCommon::setPluginPath(QString(LIBVLC_PLUGINS_DIR));

    VlcInstance *instance = new VlcInstance(VlcCommon::args(), this);

    QCOMPARE(instance->status(), true);

    delete instance;
}

void TestInstance::withPlugins()
{
    VlcInstance *instance = new VlcInstance(VlcCommon::args(), this);

    QCOMPARE(instance->status(), true);

    delete instance;
}

void TestInstance::versions()
{
    VlcInstance *instance = new VlcInstance(VlcCommon::args(), this);

    qDebug() << instance->libVersion() << instance->libVersionMajor() << instance->libVersionMinor();
    qDebug() << instance->version() << instance->changeset() << instance->compiler();

    delete instance;
}

void TestInstance::userAgent()
{
    VlcInstance *instance = new VlcInstance(VlcCommon::args(), this);

    instance->setUserAgent("TestCase", "1.0");

    delete instance;
}

void TestInstance::appId()
{
    VlcInstance *instance = new VlcInstance(VlcCommon::args(), this);

    instance->setAppId("si.tano.vlc-qt", "1.0", "image");

    delete instance;
}

void TestInstance::filters()
{
    VlcInstance *instance = new VlcInstance(VlcCommon::args(), this);

    instance->audioFilterList();
    instance->videoFilterList();

    delete instance;
}

QTEST_MAIN(TestInstance)
#include "TestInstance.moc"
