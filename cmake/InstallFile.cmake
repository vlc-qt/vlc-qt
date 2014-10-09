# - macro_copy_file(_src _dst)
# Copies a file to ${_dst} only if ${_src} is different (newer) than ${_dst}
#
# Example:
# macro_copy_file(${CMAKE_CURRENT_SOURCE_DIR}/icon.png ${CMAKE_CURRENT_BINARY_DIR}/.)
# Copies file icon.png to ${CMAKE_CURRENT_BINARY_DIR} directory
#
# Copyright (c) 2006-2007  Wengo
# Copyright (c) 2006-2008  Andreas Schneider <mail@cynapses.org>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING file.


macro (macro_install_file _src _dst)
	# Removes all path containing .svn or CVS or CMakeLists.txt during the copy
	if (NOT ${_src} MATCHES ".*\\.svn|CVS|CMakeLists\\.txt.*")
		INSTALL(FILES ${_src} DESTINATION "${_dst}")
	endif (NOT ${_src} MATCHES ".*\\.svn|CVS|CMakeLists\\.txt.*")
endmacro (macro_install_file)