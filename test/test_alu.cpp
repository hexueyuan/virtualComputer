#include <iostream>
#include "alu.h"
#include "bus.h"

using namespace std;

int main() {
    base::BusBase _in_A_(4);
    base::BusBase _in_B_(4);
    base::BusBase _out_A_(4);
    base::BusBase _out_B_(4);
    base::BusBase _control_bus_(ALU_INSTRUCTION_BITS_SIZE);
    unsigned long _ins_active_bits = 0b000111000;
    unsigned long _ins_offset = 3;
    _out_A_._named("A");
    _out_B_._named("B");
    _control_bus_._named("control");

    base::AluBase alu(&_in_A_, &_in_B_, &_out_A_, &_out_B_, &_control_bus_, _ins_active_bits);
    
    //从总线读取数据，计算后输出
    /*总线输入数据*/
    _in_A_.write(0b0011);
    _in_B_.write(0b0110);
    cout << "input A:" << " 0b" << base::_bin_str(0b0011, 4) << endl;
    cout << "input B:" << " 0b" << base::_bin_str(0b0110, 4) << endl;
    /*计算指令*/
    //+
    cout
    _control_bus_.write(ALU_ARITHMETIC_ADD << _ins_offset);
    alu();
    alu._debug();
    cout << "_ADD()" << endl;
    _control_bus_._debug();
    _out_A_._debug();
    _out_B_._debug();
    cout << "except:" << " 0b" << base::_bin_str(0b0011 + 0b0110, 4) << endl;
    //&
    _control_bus_.write(ALU_LOGIC_AND << _ins_offset);
    alu();
    alu._debug();
    cout << "_AND()" << endl;
    _control_bus_._debug();
    _out_A_._debug();
    _out_B_._debug();
    cout << "except:" << " 0b" << base::_bin_str(0b0011 & 0b0110, 4) << endl;
    //|
    _control_bus_.write(ALU_LOGIC_OR << _ins_offset);
    alu();
    alu._debug();
    cout << "_OR()" << endl;
    _control_bus_._debug();
    _out_A_._debug();
    _out_B_._debug();
    cout << "except:" << " 0b" << base::_bin_str(0b0011 | 0b0110, 4) << endl;
    //~
    _control_bus_.write(ALU_LOGIC_NOT << _ins_offset);
    alu();
    alu._debug();
    cout << "_NOT()" << endl;
    _control_bus_._debug();
    _out_A_._debug();
    _out_B_._debug();
    cout << "except:" << " 0b" << base::_bin_str(~0b0011, 4) << endl;
    //not work
    _control_bus_.write(ALU_DIRECT_TRANSMISSION << _ins_offset);
    alu();
    alu._debug();
    cout << "_NOT_WORK()" << endl;
    _control_bus_._debug();
    _out_A_._debug();
    _out_B_._debug();
    cout << "except:" << " 0b" << base::_bin_str(0b0011 + 0b0110, 4) << endl;

    return 0;
}
