/********************************************************************************
** Form generated from reading UI file 'DemoPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMOPLAYER_H
#define UI_DEMOPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "vlc-qt/WidgetSeek.h"
#include "vlc-qt/WidgetVideo.h"
#include "vlc-qt/WidgetVolumeSlider.h"

QT_BEGIN_NAMESPACE

class Ui_DemoPlayer
{
public:
    QAction *actionClose;
    QAction *actionPause;
    QAction *actionStop;
    QAction *actionOpenLocal;
    QAction *actionOpenUrl;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QPushButton *openLocal;
    QPushButton *openUrl;
    VlcWidgetVideo *video;
    QPushButton *stop;
    QPushButton *pause;
    VlcWidgetVolumeSlider *volume;
    VlcWidgetSeek *seek;
    QPushButton *equalizer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuMedia;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DemoPlayer)
    {
        if (DemoPlayer->objectName().isEmpty())
            DemoPlayer->setObjectName(QStringLiteral("DemoPlayer"));
        DemoPlayer->resize(640, 480);
        actionClose = new QAction(DemoPlayer);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionPause = new QAction(DemoPlayer);
        actionPause->setObjectName(QStringLiteral("actionPause"));
        actionStop = new QAction(DemoPlayer);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionOpenLocal = new QAction(DemoPlayer);
        actionOpenLocal->setObjectName(QStringLiteral("actionOpenLocal"));
        actionOpenUrl = new QAction(DemoPlayer);
        actionOpenUrl->setObjectName(QStringLiteral("actionOpenUrl"));
        centralwidget = new QWidget(DemoPlayer);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        openLocal = new QPushButton(centralwidget);
        openLocal->setObjectName(QStringLiteral("openLocal"));

        gridLayout_2->addWidget(openLocal, 0, 0, 1, 1);

        openUrl = new QPushButton(centralwidget);
        openUrl->setObjectName(QStringLiteral("openUrl"));

        gridLayout_2->addWidget(openUrl, 0, 1, 1, 1);

        video = new VlcWidgetVideo(centralwidget);
        video->setObjectName(QStringLiteral("video"));

        gridLayout_2->addWidget(video, 1, 0, 1, 2);

        stop = new QPushButton(centralwidget);
        stop->setObjectName(QStringLiteral("stop"));

        gridLayout_2->addWidget(stop, 3, 1, 1, 1);

        pause = new QPushButton(centralwidget);
        pause->setObjectName(QStringLiteral("pause"));
        pause->setCheckable(true);

        gridLayout_2->addWidget(pause, 3, 0, 1, 1);

        volume = new VlcWidgetVolumeSlider(centralwidget);
        volume->setObjectName(QStringLiteral("volume"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(volume->sizePolicy().hasHeightForWidth());
        volume->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(volume, 5, 0, 1, 2);

        seek = new VlcWidgetSeek(centralwidget);
        seek->setObjectName(QStringLiteral("seek"));
        sizePolicy.setHeightForWidth(seek->sizePolicy().hasHeightForWidth());
        seek->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(seek, 6, 0, 1, 2);

        equalizer = new QPushButton(centralwidget);
        equalizer->setObjectName(QStringLiteral("equalizer"));

        gridLayout_2->addWidget(equalizer, 4, 0, 1, 1);

        DemoPlayer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DemoPlayer);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuMedia = new QMenu(menubar);
        menuMedia->setObjectName(QStringLiteral("menuMedia"));
        DemoPlayer->setMenuBar(menubar);
        statusbar = new QStatusBar(DemoPlayer);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        DemoPlayer->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuMedia->menuAction());
        menuFile->addAction(actionOpenLocal);
        menuFile->addAction(actionOpenUrl);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);
        menuMedia->addAction(actionPause);
        menuMedia->addAction(actionStop);

        retranslateUi(DemoPlayer);
        QObject::connect(actionClose, SIGNAL(triggered()), DemoPlayer, SLOT(close()));

        QMetaObject::connectSlotsByName(DemoPlayer);
    } // setupUi

    void retranslateUi(QMainWindow *DemoPlayer)
    {
        DemoPlayer->setWindowTitle(QApplication::translate("DemoPlayer", "Demo Player", 0));
        actionClose->setText(QApplication::translate("DemoPlayer", "Close", 0));
        actionPause->setText(QApplication::translate("DemoPlayer", "Pause", 0));
        actionStop->setText(QApplication::translate("DemoPlayer", "Stop", 0));
        actionOpenLocal->setText(QApplication::translate("DemoPlayer", "Open local file", 0));
        actionOpenUrl->setText(QApplication::translate("DemoPlayer", "Open URL", 0));
        openLocal->setText(QApplication::translate("DemoPlayer", "Open local file", 0));
        openUrl->setText(QApplication::translate("DemoPlayer", "Open URL", 0));
        stop->setText(QApplication::translate("DemoPlayer", "Stop", 0));
        pause->setText(QApplication::translate("DemoPlayer", "Pause", 0));
        equalizer->setText(QApplication::translate("DemoPlayer", "Equalizer", 0));
        menuFile->setTitle(QApplication::translate("DemoPlayer", "File", 0));
        menuMedia->setTitle(QApplication::translate("DemoPlayer", "Media", 0));
    } // retranslateUi

};

namespace Ui {
    class DemoPlayer: public Ui_DemoPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMOPLAYER_H
