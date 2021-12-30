project('stb_image', 'cpp')

include = include_directories('include')

stb_lib = library('stbi',
                  'stb_image.cpp',
                  include_directories : include)

stbi_dep = declare_dependency(link_with : stb_lib,
                              include_directories : include)