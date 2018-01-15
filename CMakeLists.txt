cmake_minimum_required(VERSION 2.8.9)
project (semordnilap)
include_directories(/usr/include/enchant)
add_executable(semordnilap semordnilap.c)
target_link_libraries(semordnilap enchant)

enable_testing()
add_test(test roundup)
