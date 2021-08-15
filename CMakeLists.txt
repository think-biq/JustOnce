CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

# set up versioning.
set(BUILD_MAJOR "1")
set(BUILD_MINOR "2")
set(BUILD_PATCH "10")
set(BUILD_VERSION "${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH}")

project (JustOnce VERSION ${BUILD_VERSION})

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE PATH "" FORCE)
endif()

string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

add_subdirectory(lib/ShaOne)
add_subdirectory(lib/libbaseencode)

file (GLOB JustOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
add_library(JustOnce SHARED ${JustOnce_SRC})
target_include_directories(JustOnce PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/ShaOne/src>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/libbaseencode/src>"
)
target_link_libraries(JustOnce ShaOne baseencode)


if (JustOnce_WithTest)
	if (IS_STANDALON_PROJECT)
		add_subdirectory(lib/testly)
		include_directories(lib/testly/src)
	else()
		find_package(Testly)
	endif()

	file(GLOB JustOnce_Test_SRC	
		"${PROJECT_SOURCE_DIR}/test/*.c"
		"${PROJECT_SOURCE_DIR}/test/**/*.c")
	add_executable (JustOnceTest ${JustOnce_Test_SRC})
	target_include_directories(JustOnce PUBLIC
	  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
	)
	target_link_libraries(JustOnceTest JustOnce Testly)
endif()