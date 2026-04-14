cmake_minimum_required(VERSION 3.10)
project(code CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(code main.cpp)

target_compile_options(code PRIVATE -O2 -pipe)

# Place the executable at the repository root as required by the OJ
set_target_properties(code PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}")

