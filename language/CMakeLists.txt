cmake_minimum_required(VERSION 3.0.0)
project(language VERSION 0.1.0)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  message("Using Clang additional compiler options enabled")
  #  SET(CMAKE_CXX_FLAGS  ${CMAKE_CXX_FLAGS} "-g -fsanitize=null,undefined,address -Wall -Wpedantic -std=c++17 -Wno-unused -Wno-c99-extensions")
  # set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
  # set(CMAKE_CXX_CLANG_TIDY "clang-tidy; --use-color -checks=*")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

add_library(parser 
        parser.cc
        env.cc
        BindDef.cc
        BindingUsage.cc
        Expr.cc
        Block.cc
        IStatment.cc
        FuncDef.cc FuncDef.h
        FuncCall.cc FuncCall.h
        Conditional.cc Conditional.h
        Loop.cc Loop.h
        Matrix.cc Matrix.h
        ErrorStatment.cc ErrorStatment.h)
# target_compile_features(parser PRIVATE cxx_std_17)

add_subdirectory(lib/Catch2)
include_directories(lib/Catch2/single_include)

add_executable(tests 
        test/TestMain.cc 
        test/TestParser.cc
        test/TestExpr.cc
        test/TestBind.cc
        test/TestBlock.cc
        )

target_link_libraries(tests PRIVATE 
        parser
        Catch2::Catch2
        )
# target_compile_features(tests PRIVATE cxx_std_17)

# target_include_directories(tests )
add_test(NAME Catch2 COMMAND ./tests -s)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
