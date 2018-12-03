#include <iostream>
#include "selector.h"
#include "bus.h"

using namespace std;

int main() {
    base::BusBase _in_0_;
    base::BusBase _in_1_;
    base::BusBase _in_2_;
    base::BusBase _in_3_;
    base::BusBase _in_4_;
    base::BusBase _in_5_;
    base::BusBase _in_6_;
    base::BusBase _in_7_;

    base::BusBase _out_;

    base::BusBase _control_;

    unsigned long _ins_offset = 7;

    base::SelectorBase s(&_in_0_, &_in_1_, &_in_2_, &_in_3_, 
            &_in_4_, &_in_5_, &_in_6_, &_in_7_, &_out_, &_control_, _ins_offset);

    _in_1_._write(0b1100111100110000);
    _in_3_._write(0b1001100000110101);
    _control_._write(SELECTOR_ROUTE_1 << _ins_offset);
    s();
    cout << bitset<DATA_BITS_SIZE>(_out_._read()) << endl;

    _control_._write(SELECTOR_ROUTE_3 << _ins_offset);
    s();
    cout << bitset<DATA_BITS_SIZE>(_out_._read()) << endl;

    return 0;
}
