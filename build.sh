#!/bin/bash

if ! test -d "build";then
    echo -e "\033[31mCreate build directory...\033[0m"
    mkdir build
fi

echo -e "\033[31mIn build directory...\033[0m"
cd build

echo -e "\033[31mCreate makefile...\033[0m"
cmake .. $@

echo -e "\033[31mCompile executable file in output directory...\033[0m"
make

if test -d "output/test";then
    echo -e "\033[31mRun unittest...\033[0m"
else
    echo -e "\033[32mCompile executable file fail!\033[0m"
fi

cd output/test

for cmd in $(ls .)
do
    ./${cmd}
done
