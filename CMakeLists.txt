CMAKE_MINIMUM_REQUIRED (VERSION 3.2)

project (JustOnce)

string(
    COMPARE EQUAL
    "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"
    IS_STANDALON_PROJECT
)

#[[if (IS_STANDALON_PROJECT)]]
	add_subdirectory(third-party/ShaOne)
	include_directories(third-party/ShaOne/src)
#[[else()
	find_package(ShaOne)
endif()]]

add_subdirectory(third-party/libbaseencode)
include_directories(third-party/libbaseencode/src)

file (GLOB JustOnce_SRC
	"${PROJECT_SOURCE_DIR}/src/**/*.c")
file (GLOB JustOnce_ThirdParty_SRC
	"${PROJECT_SOURCE_DIR}/third-party/**/*.c")
add_library(JustOnce SHARED ${JustOnce_SRC} ${JustOnce_ThirdParty_SRC})
target_include_directories(JustOnce PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>"
)
target_link_libraries(JustOnce ShaOne baseencode)

if (JustOnce_WithTest)
	if (IS_STANDALON_PROJECT)
		add_subdirectory(third-party/testly)
		include_directories(third-party/testly/src)
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