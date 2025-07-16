cmake_minimum_required(VERSION 3.10)

project(fls VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.c")

add_library(fls STATIC ${SOURCES})
#target_include_directories(fls PUBLIC include)

add_library(flsDynamic SHARED ${SOURCES})
#target_include_directories(flsDynamic PUBLIC include)

set(SCRIPT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/scripts/generate_header_only_libs.sh")
add_custom_target(generatelibs
    COMMAND bash ${SCRIPT_PATH}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDS ${SCRIPT_PATH}
    COMMENT "Generating stb style libs..."
)

include(CTest)
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.c")

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE fls)
add_test(NAME tests COMMAND tests)

#install(TARGETS fls ARCHIVE DESTINATION lib)
#install(DIRECTORY include/ DESTINATION include)
