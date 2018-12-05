#include "options.h"
#include "bus.h"
#include "mutil_register.h"
#include "bits.h"

int main() {
    unsigned long _data_width = 8;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_A_(_data_width);
    base::BusBase _out_B_(_data_width);
    base::BusBase _control_(16);

    _in_A_.named("input_bus_A");
    _in_B_.named("input_bus_B");
    _out_A_.named("output_bus_A");
    _out_B_.named("output_bus_B");
    _control_.named("control_bus");

    unsigned long _active_bits = 0b0000111000000000;
    base::MutilRegisterBase mreg(&_in_A_, &_in_B_, &_out_A_, &_out_B_, &_control_, 
                                _data_width, _active_bits);
    mreg.named("MutilRegisterTest");

    unsigned long _input_data = 0b00000011;
    _in_A_.write(0);
    _in_B_.write(0);
    _out_A_.write(0);
    _out_B_.write(0);
    _control_.write(0);

    //测试从input_bus_A写入数据，再输出到output_bus_A
    _in_A_.write(_input_data);
    _control_.write(base::_generate_instruction(MUTIL_REGISTER_READ_A, _active_bits));
    mreg();
    cout << "o---------------------------------" << endl;
    mreg.debug("o---");
    _in_A_.debug("*---");
    _in_B_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");
    _control_.debug("*---");
    cout << "o---------------------------------" << endl;
    _control_.write(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, _active_bits));
    mreg();
    mreg.debug("o---");
    _in_A_.debug("*---");
    _in_B_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");
    _control_.debug("*---");

    return 0;
}