cmake_minimum_required (VERSION 3.2.0)

include(cmake/print_target_properties.cmake)

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

# --------------
# CXXOPTS
# --------------
add_subdirectory(extern/cxxopts)

# --------------
# FMT
# --------------
add_subdirectory(extern/fmt)

# --------------
# SPDLOG 
# --------------
set(SPDLOG_FMT_EXTERNAL ON) # Don't use internal fmt. Its provided directly!
add_subdirectory(extern/spdlog)

# --------------
# PCRE
# --------------
set(PCRE2_BUILD_PCRE2GREP OFF CACHE BOOL "") # Don't use internal fmt. Its provided directly!
set(PCRE2_BUILD_TESTS OFF CACHE BOOL "") # Don't use internal fmt. Its provided directly!
set(PCRE2_SUPPORT_UNICODE OFF CACHE BOOL "")
set(PCRE2_SHOW_REPORT OFF CACHE BOOL "")

add_subdirectory(extern/pcre2)
# Add missing include directories that the library can be used by this project
target_include_directories(pcre2-8-static INTERFACE ${PROJECT_BINARY_DIR}/extern/pcre2/ )

# --------------
add_subdirectory(src)
#print_target_properties(regscan)

add_subdirectory(app)


# Testing only available if this is the main app
if ((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME) AND BUILD_TESTING)
  include(GoogleTest)
  add_subdirectory(tests)
endif()
