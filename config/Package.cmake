#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2015 Tadej Novak <tadej@tano.si>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
INCLUDE(CMakePackageConfigHelpers)

WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${CMAKE_BINARY_DIR}/package/VLCQt/VLCQtConfigVersion.cmake"
    VERSION ${VLCQT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
CONFIGURE_FILE(config/package/VLCQtConfig.cmake
    "${CMAKE_BINARY_DIR}/package/VLCQt/VLCQtConfig.cmake"
)
SET(VlcQtConfigPackageLocation lib${LIB_SUFFIX}/cmake/VLCQt)
INSTALL(
    FILES
        config/package/VLCQtConfig.cmake
        "${CMAKE_BINARY_DIR}/package/VLCQt/VLCQtConfigVersion.cmake"
    DESTINATION ${VlcQtConfigPackageLocation}
    COMPONENT Devel
)

WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${CMAKE_BINARY_DIR}/package/VLCQtCore/VLCQtCoreConfigVersion.cmake"
    VERSION ${VLCQT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
EXPORT(EXPORT VLCQtCoreTargets
       FILE "${CMAKE_BINARY_DIR}/package/VLCQtCore/VLCQtCoreTargets.cmake"
       NAMESPACE VLCQt::
)
CONFIGURE_FILE(config/package/VLCQtCoreConfig.cmake
    "${CMAKE_BINARY_DIR}/package/VLCQtCore/VLCQtCoreConfig.cmake"
)
SET(VlcQtCoreConfigPackageLocation lib${LIB_SUFFIX}/cmake/VLCQtCore)
INSTALL(EXPORT VLCQtCoreTargets
        FILE VLCQtCoreTargets.cmake
        NAMESPACE VLCQt::
        DESTINATION ${VlcQtCoreConfigPackageLocation}
)
INSTALL(
    FILES
        config/package/VLCQtCoreConfig.cmake
        "${CMAKE_BINARY_DIR}/package/VLCQtCore/VLCQtCoreConfigVersion.cmake"
    DESTINATION ${VlcQtCoreConfigPackageLocation}
    COMPONENT Devel
)

WRITE_BASIC_PACKAGE_VERSION_FILE(
    "${CMAKE_BINARY_DIR}/package/VLCQtWidgets/VLCQtWidgetsConfigVersion.cmake"
    VERSION ${VLCQT_VERSION}
    COMPATIBILITY AnyNewerVersion
)
EXPORT(EXPORT VLCQtWidgetsTargets
       FILE "${CMAKE_BINARY_DIR}/package/VLCQtWidgets/VLCQtWidgetsTargets.cmake"
       NAMESPACE VLCQt::
)
CONFIGURE_FILE(config/package/VLCQtWidgetsConfig.cmake
    "${CMAKE_BINARY_DIR}/package/VLCQtWidgets/VLCQtWidgetsConfig.cmake"
)
SET(VlcQtWidgetsConfigPackageLocation lib${LIB_SUFFIX}/cmake/VLCQtWidgets)
INSTALL(EXPORT VLCQtWidgetsTargets
        FILE VLCQtWidgetsTargets.cmake
        NAMESPACE VLCQt::
        DESTINATION ${VlcQtWidgetsConfigPackageLocation}
)
INSTALL(
    FILES
        config/package/VLCQtWidgetsConfig.cmake
        "${CMAKE_BINARY_DIR}/package/VLCQtWidgets/VLCQtWidgetsConfigVersion.cmake"
    DESTINATION ${VlcQtWidgetsConfigPackageLocation}
    COMPONENT Devel
)

IF(QT_VERSION MATCHES 5)
    WRITE_BASIC_PACKAGE_VERSION_FILE(
        "${CMAKE_BINARY_DIR}/package/VLCQtQml/VLCQtQmlConfigVersion.cmake"
        VERSION ${VLCQT_VERSION}
        COMPATIBILITY AnyNewerVersion
    )
    EXPORT(EXPORT VLCQtQmlTargets
           FILE "${CMAKE_BINARY_DIR}/package/VLCQtQml/VLCQtQmlTargets.cmake"
           NAMESPACE VLCQt::
    )
    CONFIGURE_FILE(config/package/VLCQtQmlConfig.cmake
        "${CMAKE_BINARY_DIR}/package/VLCQtQml/VLCQtQmlConfig.cmake"
    )
    SET(VlcQtQmlConfigPackageLocation lib${LIB_SUFFIX}/cmake/VLCQtQml)
    INSTALL(EXPORT VLCQtQmlTargets
            FILE VLCQtQmlTargets.cmake
            NAMESPACE VLCQt::
            DESTINATION ${VlcQtQmlConfigPackageLocation}
    )
    INSTALL(
        FILES
            config/package/VLCQtQmlConfig.cmake
            "${CMAKE_BINARY_DIR}/package/VLCQtQml/VLCQtQmlConfigVersion.cmake"
        DESTINATION ${VlcQtQmlConfigPackageLocation}
        COMPONENT Devel
    )
ENDIF()
