cmake_minimum_required(VERSION 2.8)

project(pokeCraft)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
#set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/nvidia/current/libGL.so.319.82)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include pokecraft-lib/include third-party/include)

set(ALL_LIBRARIES glimac pokecraft-lib ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(glimac)
add_subdirectory(pokecraft-lib)
add_subdirectory(pokecraft)



message ("\nqui te dit que tout c'est bien passé. \n")
