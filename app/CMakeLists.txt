
add_executable(app main.cpp)

SET_PROPERTY(TARGET app
  PROPERTY COMPILE_DEFINITIONS PCRE2_CODE_UNIT_WIDTH=8)

target_compile_features(app PRIVATE cxx_std_20)
target_link_libraries(app PRIVATE regscan cxxopts fmt spdlog pcre2-posix)
set(PCRE2_HEADERS  ${PROJECT_BINARY_DIR}/extern/pcre2/)
target_include_directories(app ${PCRE2_HEADERS})
