cmake_minimum_required(VERSION 2.8.9)
project (semordnilap C)

# Compilation
add_executable(semordnilap semordnilap.c)
add_library(libsemordnilap libsemordnilap.c)
add_library(libsemordnilas SHARED libsemordnilap.c)
set_target_properties(libsemordnilap PROPERTIES OUTPUT_NAME semordnilap)
set_target_properties(libsemordnilas PROPERTIES OUTPUT_NAME semordnilap)
include_directories(/usr/include/enchant /usr/local/include/enchant-2)
find_library(libenchant NAMES enchant enchant-2)
target_link_libraries(semordnilap ${libenchant})
target_link_libraries(libsemordnilas ${libenchant})

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")

if(NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "Clang")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi")
endif()

# Installation
install(TARGETS semordnilap   DESTINATION bin)
install(FILES   semordnilap.1 DESTINATION share/man/man1)

# Testing
enable_testing()
add_test(apple    ${PROJECT_SOURCE_DIR}/tests/apple   )
add_test(rewot    ${PROJECT_SOURCE_DIR}/tests/rewot   )
add_test(stressed ${PROJECT_SOURCE_DIR}/tests/stressed)
add_test(xyz      ${PROJECT_SOURCE_DIR}/tests/xyz     )
add_test(man  man ${PROJECT_SOURCE_DIR}/semordnilap.1 )

add_test(NAME installed_man
         COMMAND man ${CMAKE_INSTALL_PREFIX}/share/man/man1/semordnilap.1
         CONFIGURATIONS installcheck
        )

add_test(NAME path_man
         COMMAND man semordnilap
         CONFIGURATIONS pathcheck
        )
add_test(NAME path_man_1
         COMMAND man 1 semordnilap
         CONFIGURATIONS pathcheck
        )

add_custom_target(check ALL
                  semordnilap=${PROJECT_BINARY_DIR}/semordnilap ${CMAKE_CTEST_COMMAND}
                  DEPENDS ${PROJECT_BINARY_DIR}/semordnilap
                 )

add_custom_target(installcheck
                  semordnilap=${CMAKE_INSTALL_PREFIX}/bin/semordnilap ${CMAKE_CTEST_COMMAND} -C installcheck
                 )
add_custom_target(pathcheck
                  semordnilap=semordnilap ${CMAKE_CTEST_COMMAND} -C pathcheck
                 )

add_custom_target(crosscheck docker-compose up --build)

# Development
add_custom_command(OUTPUT        ${PROJECT_SOURCE_DIR}/tags
                   COMMAND ctags ${PROJECT_SOURCE_DIR}/*.c
                   DEPENDS       ${PROJECT_SOURCE_DIR}/*.c
                  )

add_custom_target(format clang-format -i ${PROJECT_SOURCE_DIR}/*.c)
