cmake_minimum_required(VERSION 3.2)
project(job_server)

set(CMAKE_CXX_STANDARD 20)

add_executable(job_server main.cpp
        asyntabworker.cpp
        jobserver.cpp
        processmanager.cpp
        worker.cpp
        xpipe.cpp)
