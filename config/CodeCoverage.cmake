#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2016 Tadej Novak <tadej@tano.si>
# Copyright (C) 2012-2015 Lars Bilke
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
# Check prereqs
FIND_PROGRAM( GCOV_PATH gcov )
FIND_PROGRAM( LCOV_PATH lcov )
FIND_PROGRAM( GENHTML_PATH genhtml )

# Param _targetname     The name of new the custom make target
# Param _testrunner     The name of the target which runs the tests.
#                        MUST return ZERO always, even on errors.
#                        If not, no coverage report will be created!
# Param _outputname     lcov output is generated as _outputname.info
#                       HTML report is generated in _outputname/index.html
# Optional fourth parameter is passed as arguments to _testrunner
#   Pass them in list form, e.g.: "-j;2" for -j 2
FUNCTION(SETUP_TARGET_FOR_COVERAGE _targetname _testrunner _outputname)
    IF(NOT GCOV_PATH)
        MESSAGE(FATAL_ERROR "gcov not found! Aborting...")
    ENDIF() # NOT GCOV_PATH

    IF(NOT LCOV_PATH)
        MESSAGE(FATAL_ERROR "lcov not found! Aborting...")
    ENDIF() # NOT LCOV_PATH

    IF(NOT GENHTML_PATH)
        MESSAGE(FATAL_ERROR "genhtml not found! Aborting...")
    ENDIF() # NOT GENHTML_PATH

    # Setup target
    ADD_CUSTOM_TARGET(${_targetname}

        # Cleanup lcov
        ${LCOV_PATH} --directory src --zerocounters
        COMMAND ${LCOV_PATH} --directory src --capture --initial --output-file ${_outputname}.info.initial

        # Run tests
        COMMAND ${_testrunner} ${ARGV3}

        # Capturing lcov counters and generating report
        COMMAND ${LCOV_PATH} --directory src --capture --output-file ${_outputname}.info.full
        COMMAND ${LCOV_PATH} --remove ${_outputname}.info.full 'moc_*' 'tests/*' '/usr/*' '/Applications/*' 'compat/*' '*.framework/Headers/*' '${QT_LIB_DIR}/*' --output-file ${_outputname}.info
        COMMAND ${GENHTML_PATH} -t "VLC-Qt" -o ${_outputname} ${_outputname}.info
        COMMAND ${CMAKE_COMMAND} -E remove ${_outputname}.info.initial ${_outputname}.info.full

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
    )

    # Show info where to find the report
    ADD_CUSTOM_COMMAND(TARGET ${_targetname} POST_BUILD
        COMMAND ;
        COMMENT "Open ./${_outputname}/index.html in your browser to view the coverage report."
    )

ENDFUNCTION() # SETUP_TARGET_FOR_COVERAGE
