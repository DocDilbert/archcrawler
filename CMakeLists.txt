cmake_minimum_required (VERSION 3.2.0)

# Project name and a few useful settings. Other commands can pick up the results
project(
  TestProject 
  VERSION 0.1
  DESCRIPTION "An example project with CMake"
  LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 11)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

  # Docs only available if this is the main app
  find_package(Doxygen)
  if(Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(STATUS "Doxygen not found, not building docs")
  endif()
endif()

add_subdirectory(extern/cxxopts EXCLUDE_FROM_ALL)
add_subdirectory(extern/fmt EXCLUDE_FROM_ALL)

set(SPDLOG_FMT_EXTERNAL ON) # Don't use internal fmt. Its provided directly!
add_subdirectory(extern/spdlog EXCLUDE_FROM_ALL)

SET(PCRE2_BUILD_PCRE2GREP OFF CACHE BOOL "") # Don't use internal fmt. Its provided directly!
SET(PCRE2_BUILD_TESTS OFF CACHE BOOL "") # Don't use internal fmt. Its provided directly!
SET(PCRE2_SUPPORT_UNICODE OFF CACHE BOOL "")
add_subdirectory(extern/pcre2 EXCLUDE_FROM_ALL)

add_subdirectory(src)

add_subdirectory(app)


# Testing only available if this is the main app
# Emergency override MODERN_CMAKE_BUILD_TESTING provided as well
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  include(GoogleTest)
  add_subdirectory(tests)
endif()
