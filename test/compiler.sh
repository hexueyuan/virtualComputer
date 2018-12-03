#/bin/bash

g++ -iquote./../src/kernel/base test_bus.cpp -o test_bus

g++ -iquote./../src/kernel/base test_register.cpp -o test_register

#g++ -iquote./../src/kernel/base test_alu.cpp -o test_alu

#g++ -iquote./../src/kernel/base test_distributor.cpp -o test_distributor

#g++ -iquote./../src/kernel/base test_selector.cpp -o test_selector

#g++ -iquote./../src/kernel/base test_shiftor.cpp -o test_shiftor

#g++ -iquote./../src/kernel test_cpu.cpp -o test_cpu

#g++ -iquote./../src/kernel/base test_bits.cpp -o test_bits
