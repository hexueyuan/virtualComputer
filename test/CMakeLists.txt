#cmake_minimum_required(VERSION 2.8)

#项目全局变量
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-Wall -g3")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build//output/test)

link_directories(${PROJECT_SOURCE_DIR}/build/output/lib)

add_executable(test_bits test_bits.cpp)
target_link_libraries(test_bits libbase.a libgtest.a)

add_executable(test_bus test_bus.cpp)
target_link_libraries(test_bus libbase.a libgtest.a)

add_executable(test_register test_register.cpp)
target_link_libraries(test_register libbase.a libgtest.a)

add_executable(test_mutilregister test_mutilregister.cpp)
target_link_libraries(test_mutilregister libbase.a libgtest.a)

add_executable(test_alu test_alu.cpp)
target_link_libraries(test_alu libbase.a libgtest.a)

add_executable(test_selector test_selector.cpp)
target_link_libraries(test_selector libbase.a libgtest.a)

add_executable(test_shiftor test_shiftor.cpp)
target_link_libraries(test_shiftor libbase.a libgtest.a)

add_executable(test_cpu test_cpu.cpp)
target_link_libraries(test_cpu libbase.a libgtest.a libcomputer.a)

add_executable(test_memory test_memory.cpp)
target_link_libraries(test_memory libbase.a libgtest.a)