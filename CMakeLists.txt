cmake_minimum_required(VERSION 3.2)

project(LabSE18 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_GENERATOR_PLATFORM x86)

add_executable(main
    src/main.cpp
    src/In/In.cpp
    src/In/In.h
    src/Out/Out.cpp
    src/Out/Out.h
    src/Error/Error.cpp
    src/Error/Error.h
    src/Log/Log.cpp
    src/Log/Log.h
    src/fst/Fst.cpp
    src/fst/Fst.h
    src/Lexer/newLexer.cpp
    src/Lexer/newLexer.h
    src/Parm/Parm.cpp
    src/Parm/Parm.h
    src/WCHAR/WCHAR.cpp
    src/WCHAR/WCHAR.h
    src/Syntacsis/GRB.cpp
    src/Syntacsis/GRB.h
    src/Syntacsis/MFST.cpp
    src/Syntacsis/MFST.h
    src/Syntacsis/Rules.h
    src/Semantics/Sem.h
    src/Semantics/Sem.cpp
)
