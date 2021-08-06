cmake_minimum_required(VERSION 3.0.0)
project(interpreter VERSION 0.1.0)

include(CTest)
enable_testing()

add_subdirectory(lisp/)

add_executable(interpreter interpreter.cc)

target_link_libraries(interpreter lisp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
