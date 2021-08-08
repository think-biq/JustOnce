CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

project (JustOnce)

file (GLOB JustOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
include_directories (
	"${PROJECT_SOURCE_DIR}/src")
add_library(JustOnce SHARED ${JustOnce_SRC})


file(GLOB JustOnce_Test_SRC	
	"${PROJECT_SOURCE_DIR}/test/*.c"
	"${PROJECT_SOURCE_DIR}/test/**/*.c")
add_executable (JustOnceTest ${JustOnce_Test_SRC})
target_link_libraries(JustOnceTest JustOnce)