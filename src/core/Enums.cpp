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

#include "core/Enums.h"

QStringList Vlc::deinterlacing()
{
    QStringList list;
    list << ""
         << "discard"
         << "blend"
         << "man"
         << "bob"
         << "linear"
         << "x";

    return list;
}

QStringList Vlc::ratio()
{
    QStringList list;
    list << ""
         << "16:9"
         << "16:10"
         << "185:100"
         << "221:100"
         << "235:100"
         << "239:100"
         << "4:3"
         << "5:4"
         << "5:3"
         << "1:1";

    return list;
}

QStringList Vlc::ratioHuman()
{
    QStringList list;
    list << ""
         << "16:9"
         << "16:10"
         << "1.85:1"
         << "2.21:1"
         << "2.35:1"
         << "2.39:1"
         << "4:3"
         << "5:4"
         << "5:3"
         << "1:1";

    return list;
}
