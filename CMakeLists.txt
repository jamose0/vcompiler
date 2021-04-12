cmake_minimum_required(VERSION 3.1)

project(vcompiler)

enable_testing()

add_subdirectory(ast)
add_subdirectory(parser)
add_subdirectory(vcompiler)

# put tests in a test directory and link that with libparser.a
