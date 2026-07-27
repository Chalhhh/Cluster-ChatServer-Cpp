#!/bin/bash

set -e

# 如果 build 目录不存在，则创建该目录；如果存在就忽略
if [ ! -d "build" ]; then
    mkdir build
fi

# 清理并重新构建
rm -rf build/*
cd build
cmake ..
make