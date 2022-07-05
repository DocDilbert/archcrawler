def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c++', '-std=c++20', '-Wall', '-Wextra', '-Werror', '-I./include', '-I./extern/cxxopts/include', '-I./extern/fmt/include', '-I./extern/spdlog/include'],
  }
