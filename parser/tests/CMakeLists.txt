set(OBJ_DIR ${CMAKE_SOURCE_DIR}/target/parser/CMakeFiles/vparser.dir)
include_directories(${CMAKE_SOURCE_DIR}/parser)
add_executable(parsetests parsetests.cpp ${OBJ_DIR}/parser.cpp.o
${OBJ_DIR}/scanner.cpp.o ${OBJ_DIR}/token.cpp.o ${OBJ_DIR}/parseerror.cpp.o)
add_test(ParseTests parsetests)
