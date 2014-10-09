
# - macro_copy_dir_recursive(_src _dst)
# Copies recursively a directory to ${_dst} only if ${_src} is different (newer) than ${_dst}
#
# See macro_copy_file()
#
# Example:
# macro_copy_dir_recursive(${CMAKE_CURRENT_SOURCE_DIR}/* ${BUILD_DIR}/.)
# Copies recursively ${CMAKE_CURRENT_SOURCE_DIR} directory to ${BUILD_DIR} directory
#
# Copyright (c) 2006-2007  Wengo
# Copyright (c) 2006-2008  Andreas Schneider
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING file.

include(InstallFile)

macro (install_dir_recursive _src _dst)
  get_filename_component(relativePath ${_src} PATH)

  file(GLOB_RECURSE fileList ${_src})
  if (fileList)
    foreach (file ${fileList})
      file(RELATIVE_PATH path ${relativePath} ${file})
      get_filename_component(path ${path} PATH)

      macro_install_file(${file} ${_dst}/${path}/.)
    endforeach (file ${fileList})
  endif (fileList)
endmacro (install_dir_recursive)

macro (install_file_list _relativePath _srcList _dst)
	foreach(srcFile ${_srcList})
		file(GLOB fileList ${srcFile})
		if (fileList)
			foreach (file ${fileList})
				file(RELATIVE_PATH path ${_relativePath} ${file})
				get_filename_component(path ${path} PATH)
				macro_install_file(${file} ${_dst}/${path}/.)
			endforeach (file ${fileList})
		endif (fileList)
	endforeach()
endmacro (install_file_list)