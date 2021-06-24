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

add_executable(ui4_programowanie_obiektowe main.cpp Matrix.cpp tokens/Function.h tokens/Scope.h state-machine/states/Conditional.h tokens/Function.cc tokens/Scope.cc tokens/Token.cc tokens/Variable.cc state-machine/states/Base.cc state-machine/states/Conditional.cc state-machine/states/CreateVariable.cc state-machine/states/Error.cc state-machine/states/FunctionCall.cc state-machine/states/VariableAssigment.cc state-machine/Parser.cc Stack.cpp Stack.h state-machine/states/ParseMatrix.cc state-machine/states/ParseMatrix.h)