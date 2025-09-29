cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Wireframe)
set(CMAKE_CXX_STANDARD 17)

set(WINDOW_NAME "Wireframe")
set(WINDOW_WIDTH 1440)
set(WINDOW_HEIGHT 900)

project(${PROJECT_NAME})

set(SOURCES
	src/main.cpp
	src/Window.cpp
	src/Map.cpp
	src/Mesh.cpp
	src/Shader.cpp
	src/Camera.cpp
	src/App.cpp
)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/libraries/SDL2-2.32.10/cmake")

find_package(SDL2 REQUIRED)

add_library(glad STATIC
	third_party/glad/src/glad.c
)

target_include_directories(glad PUBLIC
	third_party/glad/include
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBRARIES
SDL2::SDL2main
SDL2::SDL2
glad
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${SDL2_INCLUDE_DIRS}
	${CMAKE_SOURCE_DIR}/third_party/glm
	include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
	WINDOW_NAME="${WINDOW_NAME}"
	WINDOW_WIDTH=${WINDOW_WIDTH}
	WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

if(WIN32)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_SOURCE_DIR}/libraries/SDL2-2.32.10/lib/x64/SDL2.dll"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()
