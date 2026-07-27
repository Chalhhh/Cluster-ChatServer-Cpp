cmake_minimum_required(VERSION 3.10)


# 配置头文件搜索路径
# include_directories()
# 配置库文件搜素路径
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)
# 把指定路径下的所有源文件名字放入变量名里面
# aux_source_directory(. SRC_LIST)

add_executable(server ${SRC_LIST})
# server程序，需要连接这三个库
target_link_libraries(server muduo_net muduo_base pthread)

