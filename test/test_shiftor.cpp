#include "shiftor.h"
#include "bus.h"

int main() {
    unsigned long _data_width = 8;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_(_data_width);
    base::BusBase _control_(_data_width);
    unsigned long _ins_active_bits = 0b0011000;
    _in_A_.named("input_bus_A");
    _in_B_.named("input_bus_B");
    _out_.named("output_bus");
    _control_.named("control_bus");
    base::ShiftorBase s(&_in_A_, &_in_B_, &_out_, &_control_, _ins_active_bits);
    s.named("ShiftorTest");
    
    unsigned long _data_A1 = 0b00000001;
    unsigned long _data_B1 = 0b11111111 & 3;
    _in_A_.write(_data_A1);
    _in_B_.write(_data_B1);
    _control_.write(SHIFTOR_LEFT_SHIFT << base::_active_bits_offset(_ins_active_bits));
    s();
    s.debug();
    _out_.debug("o---");
    cout << "o---Except: " << "00001000" << endl;

    unsigned long _data_A2 = 0b01000000;
    unsigned long _data_B2 = 0b11111111 & 3;
    _in_A_.write(_data_A2);
    _in_B_.write(_data_B2);
    _control_.write(SHIFTOR_RIGHT_SHIFT << base::_active_bits_offset(_ins_active_bits));
    s();
    s.debug();
    _out_.debug("o---");
    cout << "o---Except: " << "00001000" << endl;
    
    unsigned long _data_A3 = 0b00000001;
    unsigned long _data_B3 = 0b11111111 & 3;
    _in_A_.write(_data_A1);
    _in_B_.write(_data_B1);
    _control_.write(SHIFTOR_DIRECT_TRANSMISSION << base::_active_bits_offset(_ins_active_bits));
    s();
    s.debug();
    _out_.debug("o---");
    cout << "o---Except: " << "00000001" << endl;
    return 0;
}
