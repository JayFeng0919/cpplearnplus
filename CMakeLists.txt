cmake_minimum_required(VERSION 3.10)
project(cpplearnplus_project)

# C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows终端中文GBK（仅GCC有效，MSVC会自动忽略这行，不影响）
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options("-fexec-charset=GBK")
endif()

# 关键：添加头文件搜索路径 inc
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 收集源文件
file(GLOB SOURCES
    main.cpp
    src/*.cpp
)

# 生成可执行程序
add_executable(main ${SOURCES})