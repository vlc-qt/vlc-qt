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

#include "core/Media.h"

class TestMedia : public TestsCommon
{
    Q_OBJECT
private slots:
    void localInit();
    void remoteInit();
    void copyInit();

    void basic();
    void recording();
    void options();
};

void TestMedia::localInit()
{
    VlcMedia *media = new VlcMedia(QString(SAMPLES_DIR) + "sample.mp3", true, _instance);

    delete media;
}

void TestMedia::remoteInit()
{
    VlcMedia *media = new VlcMedia("http://localhost/sample.mp3", _instance);

    delete media;
}

void TestMedia::copyInit()
{
    VlcMedia *media1 = new VlcMedia(QString(SAMPLES_DIR) + "sample.mp3", true, _instance);
    VlcMedia *media2 = new VlcMedia(media1->core());

    Q_UNUSED(media2)
}

void TestMedia::basic()
{
    VlcMedia *media = new VlcMedia(QString(SAMPLES_DIR) + "sample.mp3", true, _instance);

    QCOMPARE(media->parsed(), false);
    QCOMPARE(media->currentLocation(), QString(SAMPLES_DIR) + "sample.mp3");
    QCOMPARE(media->state(), Vlc::Idle);

#ifdef Q_OS_MAC
    QEventLoop *loop = new QEventLoop(this);

    connect(media, static_cast<void (VlcMedia::*)(bool)>(&VlcMedia::parsedChanged), [=]() {
        QCOMPARE(media->duration(), 30097);

        media->getStats();

        loop->exit();

        delete media;
    });

    media->parse();

    loop->exec();
#endif
}

void TestMedia::recording()
{
    VlcMedia *media = new VlcMedia(QString(SAMPLES_DIR) + "sample.mp3", true, _instance);
    QCOMPARE(media->duplicate("test", "path", Vlc::AVI), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->duplicate("test", "path", Vlc::AVI, Vlc::MPEG2Audio, Vlc::MPEG4Video), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->duplicate("test", "path", Vlc::AVI, Vlc::MPEG2Audio, Vlc::MPEG4Video, 1000, 25, 1), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->merge("test", "path", Vlc::AVI), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->record("test", "path", Vlc::AVI, false), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->record("test", "path", Vlc::AVI, Vlc::MPEG2Audio, Vlc::MPEG4Video, false), QDir::toNativeSeparators("path/test.avi"));
    QCOMPARE(media->record("test", "path", Vlc::AVI, Vlc::MPEG2Audio, Vlc::MPEG4Video, 1000, 25, 1, false), QDir::toNativeSeparators("path/test.avi"));

    delete media;
}

void TestMedia::options()
{
    VlcMedia *media = new VlcMedia(QString(SAMPLES_DIR) + "sample.mp3", true, _instance);
    media->setProgram(1);
    media->setOptions(QStringList() << "option1"
                                    << "option2");
    delete media;
}

QTEST_MAIN(TestMedia)
#include "TestMedia.moc"
