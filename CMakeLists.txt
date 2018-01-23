cmake_minimum_required(VERSION 2.8.9)
project (semordnilap)
add_executable(semordnilap semordnilap.c)
install(TARGETS semordnilap DESTINATION bin)
include_directories(/usr/include/enchant /usr/local/include/enchant-2)
find_library(libenchant NAMES enchant enchant-2)
target_link_libraries(semordnilap ${libenchant})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")

if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi")
endif()

enable_testing()
add_test(test ${PROJECT_SOURCE_DIR}/test ${PROJECT_BINARY_DIR}/semordnilap)
add_custom_target(always_be_testing ALL
                  ${PROJECT_SOURCE_DIR}/test ${PROJECT_BINARY_DIR}/semordnilap
                  DEPENDS ${PROJECT_BINARY_DIR}/semordnilap
                 )

add_custom_target(test-install
                ${PROJECT_SOURCE_DIR}/test ${CMAKE_INSTALL_PREFIX}/bin/semordnilap
                )

add_custom_command(OUTPUT        ${PROJECT_SOURCE_DIR}/tags
                   COMMAND ctags ${PROJECT_SOURCE_DIR}/*.c
                   DEPENDS       ${PROJECT_SOURCE_DIR}/*.c
                  )

add_custom_target(format clang-format -i ${PROJECT_SOURCE_DIR}/*.c)
