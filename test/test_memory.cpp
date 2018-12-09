#include <iostream>
#include <string>
#include "memory.h"
#include "options.h"

using namespace std;

int main() {
    unsigned long _addr_width = 4;
    unsigned long _active_bits = 0b11;
    base::BusBase _in_(DATA_BITS_WIDTH);
    base::BusBase _out_(DATA_BITS_WIDTH);
    base::BusBase _control_(2);
    base::BusBase _addr_(_addr_width);
    _in_.named("Data_in_bus");
    _out_.named("Data_out_bus");
    _control_.named("Control_bus");
    _addr_.named("Address_bus");

    compute::MemoryBase mem(&_in_, &_out_, &_control_, &_addr_, DATA_BITS_WIDTH, _addr_width, _active_bits);
    mem.named("MemoryTest");

    //_control_.write(MEMORY_WRITE);
    //_in_.write(0b10101010);
    //_out_.write(0);
    //_addr_.write(0b0001);
    //mem();
    //mem.debug("write----");

    //_control_.write(MEMORY_READ);
    //_in_.write(0);
    //_out_.write(0);
    //_addr_.write(0b0001);
    //mem();
    //mem.debug("read----");
    //_out_.debug("output----");

    mem.write_in(1, 1);
    mem.write_in(2, 2);
    mem.write_in(3, 3);
    mem.write_in(4, 4);
    mem.debug(1);
    mem.debug(2);
    mem.debug(3);
    mem.debug(4);
    
    return 0;
}
