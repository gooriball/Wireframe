cmake_minimum_required(VERSION 3.14)

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

include(FetchContent)

set(SDL_TEST OFF CACHE BOOL "" FORCE)
set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
	SDL2
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG release-2.32.10
	GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(
	imgui
	GIT_REPOSITORY https://github.com/ocornut/imgui.git
	GIT_TAG v1.90.6
	GIT_SHALLOW TRUE
)
FetchContent_GetProperties(imgui)
if (NOT imgui_POPULATED)
	FetchContent_Populate(imgui)
endif()

add_library(glad STATIC
	third_party/glad/src/glad.c
)

add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp	
)
target_include_directories(imgui PUBLIC
	${imgui_SOURCE_DIR}
	${imgui_SOURCE_DIR}/backends
)
target_link_libraries(imgui PRIVATE
	SDL2::SDL2
	glad
)
	
target_compile_definitions(imgui PUBLIC
	IMGUI_IMPL_OPENGL_LOADER_GLAD
)

if(WIN32)
	set(OPENGL_LIB opengl32)
else()
	find_package(OpenGL REQUIRED)
	set(OPENGL_LIB OpenGL::GL)
endif()

target_include_directories(glad PUBLIC
	third_party/glad/include
)

add_executable(${PROJECT_NAME} ${SOURCES})

set(LIBRARIES
	SDL2::SDL2
	${OPENGL_LIB}
	imgui
	glad
)
if (WIN32)
	list(APPEND LIBRARIES SDL2::SDL2main)
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_SOURCE_DIR}/third_party/glm
	include
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBRARIES})

target_compile_definitions(${PROJECT_NAME} PRIVATE
	WINDOW_NAME="${WINDOW_NAME}"
	WINDOW_WIDTH=${WINDOW_WIDTH}
	WINDOW_HEIGHT=${WINDOW_HEIGHT}
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:SDL2::SDL2>
          $<TARGET_FILE_DIR:${PROJECT_NAME}>
)