#Specify the version being used as well as the language
cmake_minimum_required(VERSION 2.8)

project(dempathy-linear)

#set empathy source code
set(EMPATHY_SOURCES_BASE "empathy/include/Empathy")
include(empathy/load_sources.cmake)

set (DEMPATHY_SOURCES
        dempathy-linear/__main__.cpp)


include(empathy/load_libraries.cmake)


pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})

IF(${CMAKE_SYSTEM_NAME} STREQUAL "linux")

	pkg_search_module(x11 REQUIRED x11)
	include_directories(${x11_INCLUDE_DIRS})

	pkg_search_module(xrandr REQUIRED xrandr)
	include_directories(${xrandr_INCLUDE_DIRS})

	pkg_search_module(xi REQUIRED xi)
	include_directories(${xi_INCLUDE_DIRS})

	pkg_search_module(xxf86vm REQUIRED xxf86vm)
	include_directories(${xxf86vm_INCLUDE_DIRS})

ENDIF()

include_directories(dempathy-linear/libs/irrKlang-64bit-1.5.0/include/)
include_directories(empathy/include)

#add source files for compilation
add_executable(dempathy-linear ${DEMPATHY_SOURCES} ${EMPATHY_SOURCES} )


IF(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set (PLATFORM_LIBRARIES
		"${CMAKE_CURRENT_SOURCE_DIR}/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/linux-gcc-64/libIrrKlang.so"
		)
ELSEIF(APPLE)
	set (PLATFORM_LIBRARIES
		"${CMAKE_CURRENT_SOURCE_DIR}/dempathy-linear/libs/irrKlang-64bit-1.5.0/bin/macosx-gcc/libIrrKlang.dylib"
		)
ENDIF()

#link the libraries
target_link_libraries(dempathy-linear
#        "${CMAKE_CURRENT_SOURCE_DIR}/empathy/dist/libempathy.so"
        ${GLFW_STATIC_LIBRARIES}
        ${EMPATHY_DEPENDENCY_LIBRARIES}
		${GLEW_LIBRARIES}
		${OPENGL_LIBRARIES}
		${MUPARSER_LIBRARIES}

        ${x11_LIBRARIES}
        ${xi_LIBRARIES}

        ${xxf86vm_LIBRARIES}
        ${xrandr_LIBRARIES}
	
	${PLATFORM_LIBRARIES}
        )

