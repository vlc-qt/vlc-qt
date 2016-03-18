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

#include <QtQml/QQmlExtensionPlugin>

#include "qml/Qml.h"

class Q_DECL_EXPORT VlcPluginQml : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "si.tano.VLC-Qt")

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("VLCQt"));

        VlcQml::registerTypes();
    }
};

#include "Plugin.moc"
