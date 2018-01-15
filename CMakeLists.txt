cmake_minimum_required(VERSION 2.8.9)
project (semordnilap)
include_directories(/usr/include/enchant)
add_executable(semordnilap semordnilap.c)
target_link_libraries(semordnilap enchant)

enable_testing()
add_test(test roundup)

# Target should be called 'tags' but doesn't work
add_custom_target(dev ALL DEPENDS tags)
add_custom_command(OUTPUT tags
                   COMMAND ctags *.c
                   DEPENDS *.c
                  )
