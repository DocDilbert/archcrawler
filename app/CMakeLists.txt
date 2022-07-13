
add_executable(app main.cpp regex.cpp)

SET_PROPERTY(TARGET app
  PROPERTY COMPILE_DEFINITIONS PCRE2_CODE_UNIT_WIDTH=8)

target_compile_features(app PRIVATE cxx_std_20)
target_link_libraries(app PRIVATE archcrawler cxxopts fmt spdlog pcre2-8)

#target_include_directories(app PUBLIC ${PCRE2_HEADERS})
