# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/avdan-os-dock_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/avdan-os-dock_autogen.dir/ParseCache.txt"
  "avdan-os-dock_autogen"
  )
endif()
