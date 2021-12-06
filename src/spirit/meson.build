glfw = dependency('glfw3')
glad = subproject('glad').get_variable('glad_dep')
spdlog = subproject('spdlog').get_variable('spdlog_dep')
glm = subproject('glm').get_variable('glm_dep')

spirit_dependencies = [glfw, glad, spdlog, glm]

subdir('core')
subdir('renderer')

spirit_source = ['main.cpp']
spirit_source += core_source
spirit_source += renderer_source

spirit_lib = library('spirit',
                     spirit_source,
                     dependencies : spirit_dependencies)

spirit_dep = declare_dependency(link_with : spirit_lib)