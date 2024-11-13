cmake_minimum_required(VERSION 3.29)
project(testMemoire)

set(CMAKE_CXX_STANDARD 20)

add_executable(testMemoire mainFCFS.cpp
        test.cpp
        Process.h
        MemoryBlock.h
        Processor.h
        usualFunction.h
        mainSRTF.cpp
        mainRR.cpp
        mainSJF.cpp
        main.cpp)
