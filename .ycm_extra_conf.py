def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c++', '-Wall', '-Wextra', '-Werror', '-I./include', '-I./extern/cxxopts/include', '-I./extern/fmt/include', '-I./extern/spdlog/include'],
  }
