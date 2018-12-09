#!/bin/bash

g++ -std=c++11 -iquote./../src/kernel -pthread test_bits.cpp /Usr/local/lib/libgtest.a -o test_bits

g++ -std=c++11 -iquote./../src/kernel -pthread test_bus.cpp /Usr/local/lib/libgtest.a -o test_bus
