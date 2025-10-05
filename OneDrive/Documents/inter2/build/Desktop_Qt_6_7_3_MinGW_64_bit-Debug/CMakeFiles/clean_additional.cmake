# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\inter2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\inter2_autogen.dir\\ParseCache.txt"
  "inter2_autogen"
  )
endif()
