# Create the library 
add_library(regscan 
  file_list/get_file_list_uc.cpp 
  file_list/path_beginswith_blacklist_uc.cpp
  file_list/path_contains_blacklist_uc.cpp
  file_list/file_extension_whitelist_uc.cpp

  # --- 
  memory_loader/load_filelist_uc.cpp 
)

# Build the library with C++17 
target_compile_features(regscan PRIVATE cxx_std_20)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(regscan PUBLIC ../include)


target_link_libraries(regscan PRIVATE fmt spdlog)

