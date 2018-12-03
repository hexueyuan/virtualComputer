#include <iostream>
#include <bitset>

#include "register.h"
#include "bus.h"
#include "options.h"

int main() {
    unsigned long _input_data = 0b1011001100001111;
    unsigned long _data_width = 15;
    unsigned long _ins_offset = 0b000000111;
    base::BusBase _input_(_data_width);
    _input_.named("reg_input");
    base::BusBase _output_(_data_width);
    _output_.named("reg_output");
    base::BusBase _control_(_data_width);
    _control_.named("reg_control");
    base::RegisterBase reg(&_input_, &_output_, &_control_, _data_width, _ins_offset);
    reg.named("TestRegister");

    //初始化输入输出数据线
    _input_.write(_input_data);
    _output_.write(0);
    cout << "Init environment and write data to input bus." << endl;
    reg.debug("+---");
    _control_.debug("+---");
    _input_.debug("+---");
    _output_.debug("+---");

    //执行写入命令
    cout << "Run WRITE instruction." << endl;
    _control_.write(REGISTER_WRITE << base::_active_bits_offset(_ins_offset));
    reg();
    reg.debug("+---");
    _control_.debug("+---");
    _input_.debug("+---");
    _output_.debug("+---");

    //执行输出命令
    cout << "Run READ instruction." << endl;
    _control_.write(REGISTER_READ << base::_active_bits_offset(_ins_offset));
    reg();
    reg.debug("+---");
    _control_.debug("+---");
    _input_.debug("+---");
    _output_.debug("+---");

    return 0;
}
