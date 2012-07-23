/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include <QtCore/QTextCodec>

#include "internal/Encoding.h"

QString VlcInternal::Encoding::fromUtf8(const QString &string)
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QString out = codec->toUnicode(string.toLocal8Bit());

    return out;
}

const char *VlcInternal::Encoding::fromUtf8C(const QString &string)
{
    QString out = fromUtf8(string);

    return out.toUtf8().constData();
}
