# Create the library 
add_library(regscan 
  file_list/uc_get_file_list.cpp 
  file_list/uc_path_beginswith_blacklist.cpp
  file_list/uc_path_contains_blacklist.cpp
  file_list/uc_file_extension_whitelist.cpp

  # --- 
  memory_loader/uc_load_file_list.cpp 

  # ---
  matchers/uc_search_file_buf.cpp
  matchers/uc_search_in_file_buf_list.cpp
  matchers/uc_search_regex_in_filebuf_list.cpp
)

# Build the library with C++17 
target_compile_features(regscan PRIVATE cxx_std_20)

# Add the include directories and make them known to other targets (PUBLIC)
target_include_directories(regscan PUBLIC ../include)


target_link_libraries(regscan PRIVATE fmt spdlog)

