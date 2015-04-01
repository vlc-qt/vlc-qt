/*****************************************************************************
 * Copyright © 2011 VideoLAN
 * $Id: 53a1f78975febac1cf2ad7e80f7cf1d6fba60f55 $
 *
 * Authors: Ludovic Fauvet <etix@l0cal.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef TIMETOOLTIP_H
#define TIMETOOLTIP_H

//#include "qt4.hpp"

#include <QWidget>
#include <QBitmap>

class QPaintEvent;
class QString;
class QFont;
class QRect;
class QPainterPath;

class TimeTooltip : public QWidget
{
    Q_OBJECT
public:
    explicit TimeTooltip( QWidget *parent = 0 );
    void setTip( const QPoint& pos, const QString& time, const QString& text );
    virtual void show();

protected:
    virtual void paintEvent( QPaintEvent * );

private:
    void adjustPosition();
    void buildPath();
    QPoint mTarget;
    QString mTime;
    QString mText;
    QString mDisplayedText;
    QFont mFont;
    QRect mBox;
    QPainterPath mPainterPath;
    QBitmap mMask;
    int mTipX;
};

#endif // TIMETOOLTIP_H
