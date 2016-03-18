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

#ifndef VLCQT_QMLSOURCE_H_
#define VLCQT_QMLSOURCE_H_

#include <QtCore/QObject>
#include <QtQml/QQmlParserStatus>

#include "SharedExportQml.h"

class VlcMediaPlayer;

class VlcQmlVideoOutput;
class VlcQmlVideoStream;

/*!
    \class VlcQmlSource QmlSource.h VLCQtQml/QmlSource.h
    \ingroup VLCQtQml
    \brief QML video source

    A special class which represents video source.
    VlcQmlVideoOutput can connect to any class that subclasses this one.

    \see VlcQmlPlayer
    \see VlcQmlVideoOutput
 */
class VLCQT_QML_EXPORT VlcQmlSource : public QObject,
                                      public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)
public:
    /*!
        \brief VlcQmlSource constructor
        \param parent parent object
     */
    VlcQmlSource(QObject *parent);
    ~VlcQmlSource();

    /*!
        \brief Set media player to use
        \param player media player
     */
    void setPlayer(VlcMediaPlayer *player);

    /*!
        \brief Remove player from source
    */
    void removePlayer();

    /*!
        \brief Register video output
        \param output QML video output
     */
    virtual void registerVideoOutput(VlcQmlVideoOutput *output);

    /*!
        \brief Deregister video output
        \param output QML video output
     */
    virtual void deregisterVideoOutput(VlcQmlVideoOutput *output);


private:
    void classBegin() override {}
    void componentComplete() override {}

    VlcQmlVideoStream *_videoStream;
};

#endif // VLCQT_QMLSOURCE_H_
