cmake_minimum_required(VERSION 3.2)

project(LabSE18 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_GENERATOR_PLATFORM x86)

add_executable(main
    src/main.cpp
    src/In/In.cpp
    src/Out/Out.cpp
    src/Error/Error.cpp
    src/Log/Log.cpp
    src/fst/Fst.cpp
    src/Lexer/newLexer.cpp
    src/Parm/Parm.cpp
    src/WCHAR/WCHAR.cpp
    src/Syntacsis/GRB.cpp
    src/Syntacsis/MFST.cpp
    src/Semantics/Sem.cpp
    src/Generation/Gen.cpp
)
