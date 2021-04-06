include_directories(${CMAKE_SOURCE_DIR}/ast)
add_library(vparser STATIC parser.cpp scanner.cpp token.cpp parseerror.cpp)
target_link_libraries(vparser ast)
set_property(TARGET vparser PROPERTY CXX_STANDARD 17)
