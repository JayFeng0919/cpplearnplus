# 1. 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 2. 给你的项目起个名字
project(cpplearnplus_project)

# 告诉编译器：程序执行时的字符集用 GBK（适配 Windows 终端）
add_compile_options("-fexec-charset=GBK")

# 3. 收集当前目录下所有的 .cpp 文件，并把它们打包命名为 SOURCES 变量
# （这就完美替代了我们之前在 tasks.json 里写的 *.cpp）
file(GLOB SOURCES "*.cpp")

# 4. 告诉 CMake：用 SOURCES 里的所有文件，生成一个名为 main 的可执行文件
add_executable(main ${SOURCES})