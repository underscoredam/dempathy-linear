#specify the version being used as well as the language
cmake_minimum_required(VERSION 2.8)

if(UNIX AND NOT APPLE)
	set(LINUX TRUE)
ENDIF()

if(UNIX AND APPLE)
	set(MACOS TRUE)
ENDIF()

project(dempathy-linear)

#set empathy source code
set(EMPATHY_SOURCES_BASE "empathy/include/Empathy")

include(empathy/load_sources.cmake)

#set dempathy source code
set (DEMPATHY_SOURCES
        dempathy-linear/__main__.cpp)


include(empathy/load_libraries.cmake)


pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLrW_INCLUDE_DIRS})

IF(LINUX)

	pkg_search_module(x11 REQUIRED x11)
	include_directories(${x11_INCLUDE_DIRS})

	pkg_search_module(xrandr REQUIRED xrandr)
	include_directories(${xrandr_INCLUDE_DIRS})

	pkg_search_module(xi REQUIRED xi)
	include_directories(${xi_INCLUDE_DIRS})

	pkg_search_module(xxf86vm REQUIRED xxf86vm)
	include_directories(${xxf86vm_INCLUDE_DIRS})
endif()

include_directories(dempathy-linear/libs/irrKlang-64bit-1.5.0/include/)
include_directories(empathy/include)

#add source files for compilation
add_executable(dempathy ${DEMPATHY_SOURCES} ${EMPATHY_SOURCES} )


#link the libraries
target_link_libraries(dempathy
#        "${CMAKE_CURRENT_SOURCE_DIR}/empathy/dist/libempathy.so"
        ${GLFW_STATIC_LIBRARIES}
        ${EMPATHY_DEPENDENCY_LIBRARIES}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${MUPARSER_LIBRARIES}

#			Links Library's if linux requires
			${x11_LIBRARIES}
			${xi_LIBRARIES}
			${xxf86vm_LIBRARIES}
			${xrandr_LIBRARIES}
			
		"${CMAKE_CURRENT_SOURCE_DIR}/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/macosx-gcc/libirrklang.dylib"

        )

