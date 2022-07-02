# Create the library lib1
add_library(lib1 lib1.cpp ../include/lib1/lib1.hpp)

# Build the library with C++17 
target_compile_features(lib1 PRIVATE cxx_std_17)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(lib1 PUBLIC ../include)


target_link_libraries(lib1 PRIVATE fmt spdlog)

