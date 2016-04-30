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

#ifndef VLCQT_QMLVIDEOOUTPUT_H_
#define VLCQT_QMLVIDEOOUTPUT_H_

#include <memory>

#include <QQuickItem>
#include <QPointer>

#include <VLCQtCore/Enums.h>

#include "SharedExportQml.h"

struct VlcYUVVideoFrame;
class VlcQmlSource;

/*!
    \class VlcQmlVideoOutput QmlVideoOutput.h VLCQtQml/QmlVideoOutput.h
    \ingroup VLCQtQml
    \brief QML video output

    A QML video output that can be used to display video inside QML.

    \since VLC-Qt 1.1
 */
class VLCQT_QML_EXPORT VlcQmlVideoOutput : public QQuickItem
{
    Q_OBJECT

    /*!
        \brief Current video source
        \see source
        \see setSource
        \see sourceChanged
     */
    Q_PROPERTY(VlcQmlSource *source READ source WRITE setSource NOTIFY sourceChanged)

    /*!
        \brief Current fill mode
        \see fillMode
        \see setFillMode
        \see fillModeChanged
     */
    Q_PROPERTY(int fillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged)

    /*!
        \brief Current aspect ratio
        \see aspectRatio
        \see setAspectRatio
        \see aspectRatioChanged
     */
    Q_PROPERTY(int aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged)

    /*!
        \brief Current crop ratio
        \see cropRatio
        \see setCropRatio
        \see cropRatioChanged
     */
    Q_PROPERTY(int cropRatio READ cropRatio WRITE setCropRatio NOTIFY cropRatioChanged)


public:
    VlcQmlVideoOutput();
    ~VlcQmlVideoOutput();

    /*!
        \brief Current video source
        \return source

        Used as property in QML.
     */
    VlcQmlSource *source() const;

    /*!
        \brief Set video source
        \param source video source

        Used as property in QML.
     */
    void setSource(VlcQmlSource *source);

    /*!
        \brief Current fill mode
        \return fill mode

        Used as property in QML.
     */
    int fillMode() const;

    /*!
        \brief Set fill mode
        \param mode fill mode

        Used as property in QML.
     */
    void setFillMode(int mode);

    /*!
        \brief Current aspect ratio
        \return aspect ratio

        Used as property in QML.
     */
    int aspectRatio() const;

    /*!
        \brief Set aspect ratio
        \param aspectRatio new aspect ratio

        No effect when fillMode equals Vlc::Stretch.
        Used as property in QML.
     */
    void setAspectRatio(int aspectRatio);

    /*!
        \brief Current crop ratio
        \return crop ratio

        Used as property in QML.
     */
    int cropRatio() const;

    /*!
        \brief Set crop ratio
        \param cropRatio new crop ratio

        No effect when fillMode equals Vlc::Stretch.
        Used as property in QML.
     */
    void setCropRatio(int cropRatio);


public slots:
    /*!
        \brief Set frame which will be rendered in the output.
        \param frame
     */
    void presentFrame(const std::shared_ptr<const VlcYUVVideoFrame> &frame);


signals:
    /*!
        \brief Source changed signal
     */
    void sourceChanged();

    /*!
        \brief Fill mode changed signal
     */
    void fillModeChanged();

    /*!
        \brief Fill mode changed signal
     */
    void aspectRatioChanged();

    /*!
        \brief Fill mode changed signal
     */
    void cropRatioChanged();


private:
    virtual QSGNode *updatePaintNode(QSGNode *oldNode,
                                     UpdatePaintNodeData *data);

    Vlc::FillMode _fillMode;
    Vlc::Ratio _aspectRatio;
    Vlc::Ratio _cropRatio;

    QPointer<VlcQmlSource> _source;

    bool _frameUpdated;
    std::shared_ptr<const VlcYUVVideoFrame> _frame;
};

#endif // VLCQT_QMLVIDEOOUTPUT_H_
