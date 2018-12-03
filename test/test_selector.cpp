#include <iostream>
#include "selector.h"
#include "bus.h"

using namespace std;

int main() {
    base::BusBase _in_0_(8);
    base::BusBase _in_1_(8);
    base::BusBase _in_2_(8);
    base::BusBase _in_3_(8);
    base::BusBase _in_4_(8);
    base::BusBase _in_5_(8);
    base::BusBase _in_6_(8);
    base::BusBase _in_7_(8);
    base::BusBase _out_(8);
    base::BusBase _control_(32);

    _in_0_.named("Input0");
    _in_1_.named("Input1");
    _in_2_.named("Input2");
    _in_3_.named("Input3");
    _in_4_.named("Input4");
    _in_5_.named("Input5");
    _in_6_.named("Input6");
    _in_7_.named("Input7");
    _out_.named("Output");
    _control_.named("Control");

    unsigned long _ins_offset = 0b0011110000000;

    base::SelectorBase s(&_in_0_, &_in_1_, &_in_2_, &_in_3_, 
            &_in_4_, &_in_5_, &_in_6_, &_in_7_, &_out_, &_control_, _ins_offset);
    s.named("Selector");

    //初始化
    _in_0_.write(0b00000000);
    _in_1_.write(0b00110000);
    _in_2_.write(0b00000000);
    _in_3_.write(0b00000000);
    _in_4_.write(0b00000000);
    _in_5_.write(0b00000000);
    _in_6_.write(0b00000000);
    _in_7_.write(0b00000000);
    _out_.write(0b00000000);
    _control_.write(SELECTOR_ROUTE_1 << base::_active_bits_offset(_ins_offset));
    s();
    s.debug("+---");
    _in_0_.debug("o---");
    _in_1_.debug("o---");
    _in_2_.debug("o---");
    _in_3_.debug("o---");
    _in_4_.debug("o---");
    _in_5_.debug("o---");
    _in_6_.debug("o---");
    _in_7_.debug("o---");
    _out_.debug("o---");
    _control_.debug("o---");

    //_in_0_.write(0b00000000);
    //_in_1_.write(0b00000000);
    //_in_2_.write(0b00000000);
    //_in_3_.write(0b00010101);
    //_in_4_.write(0b00000000);
    //_in_5_.write(0b00000000);
    //_in_6_.write(0b00000000);
    //_in_7_.write(0b00000000);
    //_out_.write(0b00000000);
    //_control_.write(SELECTOR_ROUTE_3 << base::_active_bits_offset(_ins_offset));
    //s();
    //s.debug("+---");
    //_in_0_.debug("o---");
    //_in_1_.debug("o---");
    //_in_2_.debug("o---");
    //_in_3_.debug("o---");
    //_in_4_.debug("o---");
    //_in_5_.debug("o---");
    //_in_6_.debug("o---");
    //_in_7_.debug("o---");
    //_out_.debug("o---");
    //_control_.debug("o---");

    return 0;
}