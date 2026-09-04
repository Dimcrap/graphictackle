cmake_minimum_required(VERSION 3.24)

project(graphic1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#find_package(opengl REQUIRED)
#find_package(GLFW REQUIRED)

find_library( glfw_lib 
	NAMES glfw glfw3
	PATHS /usr/lib /usr/lib64 
)

find_path(glfw_include_dir
	NAMES GLFW/glfw3.h
	PATHS /usr/include /usr/local/include
)

find_path(glm_include_dir 
	NAME glm 
	PATHS /usr/include /usr/lib)

add_executable(${PROJECT_NAME} main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c shaders.cpp)
add_executable(exer exer2.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c shaders.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(exer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE ${glfw_lib})
target_include_directories(${PROJECT_NAME} PRIVATE ${glfw_include_dir})

target_link_libraries(exer PRIVATE ${glfw_lib})
target_include_directories(exer PRIVATE ${glfw_include_dir})
