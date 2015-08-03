IF(CMAKE_VERSION VERSION_LESS 2.8.9)
    MESSAGE(FATAL_ERROR "VLC-Qt requires at least CMake version 2.8.9")
ENDIF()

IF(NOT VLCQt_FIND_COMPONENTS)
    SET(VLCQt_NOT_FOUND_MESSAGE "The VLC-Qt package requires at least one component")
    SET(VLCQt_FOUND False)
    RETURN()
ENDIF()

SET(_VLCQt_FIND_PARTS_REQUIRED)
IF(VLCQt_FIND_REQUIRED)
    SET(_VLCQt_FIND_PARTS_REQUIRED REQUIRED)
ENDIF()
SET(_VLCQt_FIND_PARTS_QUIET)
IF (VLCQt_FIND_QUIETLY)
    SET(_VLCQt_FIND_PARTS_QUIET QUIET)
ENDIF()

GET_FILENAME_COMPONENT(_VLCQt_install_prefix "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)

SET(_VLCQt_NOTFOUND_MESSAGE)

FOREACH(module ${VLCQt_FIND_COMPONENTS})
    FIND_PACKAGE(VLCQt${module}
        ${_VLCQt_FIND_PARTS_QUIET}
        ${_VLCQt_FIND_PARTS_REQUIRED}
        PATHS "${_VLCQt_install_prefix}" NO_DEFAULT_PATH
    )
    IF (NOT VLCQt${module}_FOUND)
        IF (VLCQt_FIND_REQUIRED_${module})
            SET(_VLCQt_NOTFOUND_MESSAGE "${_VLCQt_NOTFOUND_MESSAGE}Failed to find VLC-Qt component \"${module}\" config file at \"${_VLCQt_install_prefix}/VLCQt${module}/VLCQt${module}Config.cmake\"\n")
        ELSEIF(NOT VLCQt_FIND_QUIETLY)
            message(WARNING "Failed to find VLC-Qt component \"${module}\" config file at \"${_VLCQt_install_prefix}/VLCQt${module}/VLCQt${module}Config.cmake\"")
        ENDIF()
    ENDIF()
ENDFOREACH()

IF (_VLCQt_NOTFOUND_MESSAGE)
    SET(VLCQt_NOT_FOUND_MESSAGE "${_VLCQt_NOTFOUND_MESSAGE}")
    SET(VLCQt_FOUND False)
ENDIF()
