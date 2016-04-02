/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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

#include "ModuleDescription.h"

VlcModuleDescription::VlcModuleDescription(Type type,
                                           const QString &name)
    : _type(type),
      _name(name) { }

VlcModuleDescription::~VlcModuleDescription() { } // LCOV_EXCL_LINE

void VlcModuleDescription::setShortName(const QString &name)
{
    if (_shortName != name) {
        _shortName = name;
    }
}

void VlcModuleDescription::setLongName(const QString &name)
{
    if (_longName != name) {
        _longName = name;
    }
}

void VlcModuleDescription::setHelp(const QString &help)
{
    if (_help != help) {
        _help = help;
    }
}
