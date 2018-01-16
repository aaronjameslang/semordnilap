cmake_minimum_required(VERSION 2.8.9)
project (semordnilap)
include_directories(/usr/include/enchant)
add_executable(semordnilap semordnilap.c)
target_link_libraries(semordnilap enchant)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pedantic-errors")

enable_testing()
add_test(test roundup)

# Target should be called 'tags' but doesn't work
add_custom_target(dev ALL DEPENDS tags)
add_custom_command(OUTPUT tags
                   COMMAND ctags *.c
                   DEPENDS *.c
                  )

add_custom_target(test_target ALL roundup)
add_custom_target(format ALL clang-format -i *.c)
