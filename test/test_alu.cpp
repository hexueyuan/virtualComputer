#include <iostream>
#include "alu.h"
#include "bus.h"

using namespace std;

int main() {
    unsigned long _data_width = 4;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_A_(_data_width);
    base::BusBase _out_B_(_data_width);
    base::BusBase _control_bus_(16);
    unsigned long _ins_active_bits = 0b000111000;
    _in_A_.named("input_A");
    _in_B_.named("input_B");
    _out_A_.named("output_A");
    _out_B_.named("output_B");
    _control_bus_.named("control");

    base::AluBase alu(&_in_A_, &_in_B_, &_out_A_, &_out_B_, &_control_bus_, _ins_active_bits);
    alu.named("ALUTest");
    
    //从总线读取数据，计算后输出
    /*总线输入数据*/
    unsigned long _data_A1 = 3;
    unsigned long _data_B1 = 4;
    _in_A_.write(_data_A1);
    _in_B_.write(_data_B1);
    /*计算指令*/
    //+
    cout << "ADD:" << endl;
    _control_bus_.write(ALU_ARITHMETIC_ADD << base::_active_bits_offset(_ins_active_bits));
    alu();
    alu.debug("o---");
    _control_bus_.debug("*---");
    _in_A_.debug("*---");
    _in_B_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");
    cout << "except:" << base::_bin_str(_data_A1 + _data_B1, 4) << endl;
    //&
    cout << "AND:" << endl;
    _control_bus_.write(ALU_LOGIC_AND << base::_active_bits_offset(_ins_active_bits));
    alu();
    alu.debug("o---");
    _control_bus_.debug("*---");
    _in_A_.debug("*---");
    _in_B_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");
    cout << "except:" << base::_bin_str(_data_A1 & _data_B1, 4) << endl;
    //|
    cout << "OR:" << endl;
    _control_bus_.write(ALU_LOGIC_OR << base::_active_bits_offset(_ins_active_bits));
    alu();
    alu.debug("o---");
    _control_bus_.debug("*---");
    _in_A_.debug("*---");
    _in_B_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");
    cout << "except:" << base::_bin_str(_data_A1 | _data_B1, 4) << endl;
    //~
    cout << "NOT:" << endl;
    _control_bus_.write(ALU_LOGIC_NOT << base::_active_bits_offset(_ins_active_bits));
    alu();
    alu.debug("o---");
    _control_bus_.debug("*---");
    _in_A_.debug("*---");
    _in_B_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");
    cout << "except:" << base::_bin_str(~_data_A1, 4) << endl;
    //not work
    cout << "NOT WORK:" << endl;
    _control_bus_.write(ALU_NOT_ENABLE << base::_active_bits_offset(_ins_active_bits));
    alu();
    alu.debug("o---");
    _control_bus_.debug("*---");
    _out_A_.debug("*---");
    _out_B_.debug("*---");

    return 0;
}
