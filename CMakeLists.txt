CMAKE_MINIMUM_REQUIRED (VERSION 3.19)

project (JustOnce)

add_subdirectory(third-party/ShaOne)
include_directories(third-party/ShaOne/src)

add_subdirectory(third-party/libbaseencode)
include_directories(third-party/libbaseencode/src)

file (GLOB JustOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
file (GLOB JustOnce_ThirdParty_SRC
	"${PROJECT_SOURCE_DIR}/third-party/**/*.c")
include_directories (
	"${PROJECT_SOURCE_DIR}/src"
	"${PROJECT_SOURCE_DIR}/third-party")
add_library(JustOnce SHARED ${JustOnce_SRC} ${JustOnce_ThirdParty_SRC})
target_link_libraries(JustOnce ShaOne baseencode)

if (JustOnce_WithTest)
	if (NOT Testly)
		add_subdirectory(third-party/testly)
		include_directories(third-party/testly/src)
	endif()

	message(WARNING "Starting to setup test build ...")
	file(GLOB JustOnce_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (JustOnceTest ${JustOnce_Test_SRC})
	target_link_libraries(JustOnceTest JustOnce Testly)
	message(WARNING "Done ...")
endif()