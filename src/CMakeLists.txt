# Create the library 
add_library(regscan get_file_list_uc.cpp ../include/regscan/get_file_list_uc.h)

# Build the library with C++17 
target_compile_features(regscan PRIVATE cxx_std_20)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(regscan PUBLIC ../include)


target_link_libraries(regscan PRIVATE fmt spdlog)

