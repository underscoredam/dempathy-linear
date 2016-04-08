#Specify the version being used as well as the language
cmake_minimum_required(VERSION 2.8)

option(LIB "lib" OFF)

project(dempathy-linear)

#set empathy source code
set(EMPATHY_SOURCES_BASE "Empathy/include/Empathy")
include(Empathy/load_sources.cmake)

set (DEMPATHY_SOURCES
        dempathy-linear/__main__.cpp
        )


#include libraries
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

pkg_search_module(x11 REQUIRED x11)
include_directories(${x11_INCLUDE_DIRS})

pkg_search_module(xrandr REQUIRED xrandr)
include_directories(${xrandr_INCLUDE_DIRS})

pkg_search_module(xi REQUIRED xi)
include_directories(${xi_INCLUDE_DIRS})

pkg_search_module(xxf86vm REQUIRED xxf86vm)
include_directories(${xxf86vm_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

include_directories(dempathy-linear/libs/irrKlang-64bit-1.5.0/include/)
include_directories(Empathy/include)

#add source files for compilation
if(LIB)
	message("Building library")
	add_library(dempathy-linear SHARED ${DEMPATHY_SOURCES})
else()
	message("Building executable")
	add_executable(dempathy-linear ${DEMPATHY_SOURCES}  ${EMPATHY_SOURCES})
endif()



#link the libraries
target_link_libraries(dempathy-linear
#        "${CMAKE_CURRENT_SOURCE_DIR}/Empathy/dist/libempathy.so"
        ${GLFW_STATIC_LIBRARIES}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}

        ${x11_LIBRARIES}
        ${xi_LIBRARIES}

        ${xxf86vm_LIBRARIES}
        ${xrandr_LIBRARIES}

        "${CMAKE_CURRENT_SOURCE_DIR}/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/linux-gcc-64/libIrrKlang.so"
        )

