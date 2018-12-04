#include "base/bus.h"
#include "base/options.h"
#include "memory.h"

using namespace std;

int main() {
    unsigned long _addr_width = 4;
    base::BusBase _in_(DATA_BITS_SIZE);
    base::BusBase _out_(DATA_BITS_SIZE);
    base::BusBase _control_(2);
    base::BusBase _addr_(_addr_width);
    _in_.named("Data_in_bus");
    _out_.named("Data_out_bus");
    _control_.named("Control_bus");
    _addr_.named("Address_bus");

    compute::MemoryBase mem(&_in_, &_out_, &_control_, &_addr_, DATA_BITS_SIZE, _addr_width);
    mem.named("MemoryTest");

    _control_.write(MEMORY_WRITE);
    _in_.write(0b10101010);
    _out_.write(0);
    _addr_.write(0b0001);
    mem();
    mem.debug("write----");

    _control_.write(MEMORY_READ);
    _in_.write(0);
    _out_.write(0);
    _addr_.write(0b0001);
    mem();
    mem.debug("read----");
    _out_.debug("output----");
    
    return 0;
}
