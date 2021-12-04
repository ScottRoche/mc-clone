spirit_includes = []
spirit_includes += include_directories('../../subprojects/glm')

spirit_source = ['main.cpp',
                 'log.cpp']

glfw = dependency('glfw3')
glad = subproject('glad').get_variable('glad_dep')
spdlog = subproject('spdlog').get_variable('spdlog_dep')

spirit_dependencies = [glfw, glad, spdlog]

spirit_lib = library('spirit',
                     spirit_source,
                     include_directories : spirit_includes,
                     dependencies : spirit_dependencies)

spirit_dep = declare_dependency(include_directories : spirit_includes,
                                link_with : spirit_lib)