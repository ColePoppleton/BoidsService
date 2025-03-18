# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BoidsService_autogen"
  "CMakeFiles\\BoidsService_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BoidsService_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\boidsystem_tests_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\boidsystem_tests_autogen.dir\\ParseCache.txt"
  "boidsystem_tests_autogen"
  )
endif()
