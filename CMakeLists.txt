cmake_minimum_required(VERSION 3.19)
project(ui4_programowanie_obiektowe)

set(CMAKE_CXX_STANDARD 17)

set(STATES
        state-machine/State.h
        state-machine/Parser.h
        state-machine/states/Base.h
        state-machine/states/CreateVariable.h
        state-machine/states/Error.h
        state-machine/states/VariableAssigment.h
        )

set(TOKENS
        tokens/Token.h
        tokens/Variable.h
        )

include_directories(tokens)
include_directories(state-machine)
include_directories(states)

add_executable(ui4_programowanie_obiektowe main.cpp Matrix.cpp tokens/Function.h tokens/Scope.h)