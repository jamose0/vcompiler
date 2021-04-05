add_library(vparser STATIC parser.cpp scanner.cpp token.cpp parseerror.cpp)
set_property(TARGET vparser PROPERTY CXX_STANDARD 17)
