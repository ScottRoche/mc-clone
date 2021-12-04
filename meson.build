project('mc-clone', 'cpp')

glm_inc = include_directories('subprojects/glm')

glfw = dependency('glfw3')
glad = subproject('glad').get_variable('glad_dep')
spdlog = subproject('spdlog').get_variable('spdlog_dep')

executable('mc-clone',
           'src/main.cpp',
           include_directories : glm_inc,
           dependencies : [glfw, glad, spdlog])
