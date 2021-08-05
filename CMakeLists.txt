CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

project (JustOnce)

file (GLOB SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c"
	"${PROJECT_SOURCE_DIR}/src/main.c")

include_directories (
	"${PROJECT_SOURCE_DIR}/src")

add_executable (JustOnce ${SRC})
