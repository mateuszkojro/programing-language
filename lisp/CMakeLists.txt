cmake_minimum_required(VERSION 3.0.0)
project(lisp VERSION 0.1.0)

include(CTest)
enable_testing()

set(
    TOKENS 
    tokens/Error.h tokens/Error.cc
    tokens/Function.h
    tokens/Token.h
    tokens/Main.h tokens/Main.cc
    tokens/Scope.h tokens/Scope.cc
    tokens/Variable.h tokens/Variable.cc
)

add_library(lisp lisp.cc ${TOKENS} )



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
