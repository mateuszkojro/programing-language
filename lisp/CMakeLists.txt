cmake_minimum_required(VERSION 3.18.0)
project(lisp VERSION 0.1.0)


include(CTest)
enable_testing()

add_library(parser 
        parser.cc
        env.cc
        BindDef.cc
        Expr.cc
        )
target_compile_features(parser PRIVATE cxx_std_17)

add_subdirectory(lib/Catch2)
include_directories(lib/Catch2/single_include)

add_executable(tests 
        test/TestMain.cc 
        test/TestParser.cc
        test/TestExpr.cc
        test/TestBind.cc
        )

target_link_libraries(tests PRIVATE 
        parser
        Catch2::Catch2
        )
target_compile_features(tests PRIVATE cxx_std_17)

# target_include_directories(tests )
add_test(NAME Catch2 COMMAND ./tests -s)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
