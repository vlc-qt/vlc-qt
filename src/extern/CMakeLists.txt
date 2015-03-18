#################
# Configuration #
#################

# Add definition for exporting symbols
ADD_DEFINITIONS(-DVLCQT_EXTERN_LIBRARY)

# Add definition for using seek points
IF(EXTERN_WITH_CHAPTERS)
    ADD_DEFINITIONS(-DVLCQT_EXTERN_ENABLE_SEEKPOINTS=1)
ELSE()
    ADD_DEFINITIONS(-DVLCQT_EXTERN_ENABLE_SEEKPOINTS=0)
ENDIF()

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATIC -D_REENTRANT)
ELSE()
    ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)
ENDIF()

IF(MINGW OR MSVC)
    CONFIGURE_FILE(
        ${CMAKE_SOURCE_DIR}/src/platform/windows/extern.rc.in
        ${CMAKE_BINARY_DIR}/src/platform/windows/extern.rc
    )
ENDIF()

###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_EXTERN_SRCS
    qt4.hpp
    adapters/seekpoints.cpp
    styles/seekstyle.cpp
    util/input_slider.cpp
    util/timetooltip.cpp

    SharedExportExtern.h
    WidgetSeekSlider.cpp
)

# Define the Include files
SET(VLCQT_EXTERN_EXPORT_HEADERS
    SharedExportExtern.h
    WidgetSeekSlider.h
)
SET(VLCQT_EXTERN_HEADERS
    qt4.hpp
    adapters/seekpoints.hpp
    styles/seekstyle.hpp
    util/input_slider.hpp
    util/timetooltip.hpp

    ${VLCQT_EXTERN_EXPORT_HEADERS}
    ${CMAKE_BINARY_DIR}/src/Config.h
)


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${LIBVLC_INCLUDE_DIR}
    ${LIBVLC_INCLUDE_DIR}/vlc/plugins
)

IF(EXTERN_WITH_CHAPTERS)
    INCLUDE_DIRECTORIES(
        ${VLC_SRC_DIR}/modules/gui/qt4
        ${VLC_SRC_DIR}/include
    )
ENDIF()

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/extern
    ${CMAKE_BINARY_DIR}/src
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/msvc)
ELSEIF(MINGW)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/mingw)
ENDIF()

# Compile resources with windres
IF(MINGW)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${CMAKE_BINARY_DIR}/src/platform/windows/extern.obj
        COMMAND ${CMAKE_RC_COMPILER}
        -i ${CMAKE_BINARY_DIR}/src/platform/windows/extern.rc
        -o ${CMAKE_BINARY_DIR}/src/platform/windows/extern.obj
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/src/platform/windows"
    )
    SET(VLCQT_EXTERN_SRCS ${VLCQT_EXTERN_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/extern.obj)
ENDIF()

IF(MSVC)
    SET(VLCQT_EXTERN_SRCS ${VLCQT_EXTERN_SRCS} ${CMAKE_BINARY_DIR}/src/platform/windows/extern.rc)
ENDIF()

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_EXTERN} STATIC ${VLCQT_EXTERN_SRCS})
ELSE()
    ADD_LIBRARY(${VLCQT_EXTERN} SHARED ${VLCQT_EXTERN_SRCS})
ENDIF()

ADD_DEPENDENCIES(${VLCQT_EXTERN} ${VLCQT})

# Debug suffix
IF(DEBUG_SUFFIX)
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES DEBUG_POSTFIX ${LS})
ENDIF()

# MSVC: Avoid Debug/Release/... subfolders
IF(MSVC)
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ".")
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_DEBUG ".")
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELEASE ".")
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_RELWITHDUBUGINFO ".")
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ".")
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY_PROFILE ".")
ENDIF()

# Linux/Mac: So version extensions
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET_TARGET_PROPERTIES(${VLCQT_EXTERN} PROPERTIES VERSION ${VLCQT_VERSION}
                                                     SOVERSION "${VLCQT_VERSION_MAJOR}.${VLCQT_VERSION_MINOR}"
    )
ENDIF()

# Link the required libraries
IF(QT_VERSION MATCHES 4)
    TARGET_LINK_LIBRARIES(${VLCQT_EXTERN} ${VLCQT_BINARY} Qt4::Gui ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ELSE()
    TARGET_LINK_LIBRARIES(${VLCQT_EXTERN} ${VLCQT_BINARY} Qt5::Widgets ${LIBVLC_LIBRARY} ${LIBVLCCORE_LIBRARY})
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND WITH_X11)
    TARGET_LINK_LIBRARIES(${VLCQT_EXTERN} -lX11)
ENDIF()


################
# Installation #
################
INSTALL(TARGETS ${VLCQT_EXTERN} RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib${LIB_SUFFIX}
        ARCHIVE DESTINATION lib${LIB_SUFFIX}
)
INSTALL(FILES ${VLCQT_EXTERN_EXPORT_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt)
INSTALL(FILES util/input_slider.hpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include/vlc-qt/util)	#hm.
