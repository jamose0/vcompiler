include_directories(${CMAKE_SOURCE_DIR}/parser)
add_executable(vcompiler main.cpp)
target_link_libraries(vcompiler ${CMAKE_SOURCE_DIR}/target/parser/libvparser.a)
set_property(TARGET vcompiler PROPERTY CXX_STANDARD 17)
