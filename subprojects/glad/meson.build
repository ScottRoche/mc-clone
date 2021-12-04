project('glad', 'c')
inc = include_directories('include')

dl_dep = meson.get_compiler('c').find_library('dl', required : true)

glad_lib = library('glad',
                   'src/glad.c',
                   include_directories : inc,
                   dependencies : dl_dep,
                   install : true)

glad_dep = declare_dependency(include_directories : inc,
                              link_with : glad_lib)