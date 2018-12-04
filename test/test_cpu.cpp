#include <iostream>

#include "base/options.h"

#include "cpu.h"

int main() {
    unsigned long _data_width = 8;
    base::BusBase _R0_(_data_width);
    base::BusBase _R1_(_data_width);
    base::BusBase _R2_(_data_width);
    base::BusBase _R3_(_data_width);
    base::BusBase _IP_(_data_width);
    base::BusBase _PC_(_data_width);
    base::BusBase _SP_(_data_width);
    base::BusBase _MAR_(_data_width);
    base::BusBase _MDR_(_data_width);
    base::BusBase _PSW_(_data_width);
    base::BusBase _C_(_data_width);
    base::BusBase _D_(_data_width);

    _R0_.named("R0");
    _R1_.named("R1");
    _R2_.named("R2");
    _R3_.named("R3");
    _IP_.named("IP");
    _PC_.named("PC");
    _SP_.named("SP");
    _MAR_.named("MAR");
    _MDR_.named("MDR");
    _PSW_.named("PSW");
    _C_.named("C");
    _D_.named("D");

    base::BusBase _out_(_data_width);
    _out_.named("Answer");

    base::BusBase _control_(CONTROL_BUS_BITS_WIDTH);
    _control_.named("Control");
    
    compute::CPU c(&_R0_, &_R1_, &_R2_, &_R3_, &_IP_, &_PC_, &_C_, &_D_, &_MAR_, &_MDR_, &_PSW_, &_SP_, &_out_, &_control_);
    c.named("CPUTest");
    
    //R1 + R2
    //  selector:R1 -> SA
    //  selector:R2 -> SB
    //  alu:R1 + R2
    //  shiftor:direct transmission
    _R0_.write(0);
    _R1_.write(11);
    _R2_.write(15);
    _R3_.write(0);
    _IP_.write(0);
    _PC_.write(0);
    _C_.write(0);
    _D_.write(0);
    _MAR_.write(0);
    _MDR_.write(0);
    _PSW_.write(0);
    _SP_.write(0);
    _out_.write(0);
    _control_.write(0);
    unsigned long _ins_add_1 = (base::_generate_instruction(SELECTOR_ROUTE_1, SELECTOR_A_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_B_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(ALU_NOT_ENABLE, ALU_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SHIFTOR_NOT_ENABLE, SHIFTOR_INSTRUCTION_ACTIVE_BITS));
    unsigned long _ins_add_2 = (base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_A_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SELECTOR_ROUTE_2, SELECTOR_B_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(ALU_NOT_ENABLE, ALU_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SHIFTOR_NOT_ENABLE, SHIFTOR_INSTRUCTION_ACTIVE_BITS));
    unsigned long _ins_add_3 = (base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_A_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_B_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(ALU_ARITHMETIC_ADD, ALU_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SHIFTOR_NOT_ENABLE, SHIFTOR_INSTRUCTION_ACTIVE_BITS));
    unsigned long _ins_add_4 = (base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_A_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_B_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(ALU_NOT_ENABLE, ALU_INSTRUCTION_ACTIVE_BITS) |
                base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_INSTRUCTION_ACTIVE_BITS));
    c.debug("o---");
    _control_.debug("o---");
    _control_.write(_ins_add_1);
    c();
    cout << "-----------------------------" << endl;
    c.debug("o---");
    _control_.debug("o---");
    _control_.write(_ins_add_2);
    c();
    c.debug("o---");
    _control_.debug("o---");
    _control_.write(_ins_add_3);
    c();
    c.debug("o---");
    _control_.debug("o---");
    _control_.write(_ins_add_4);
    c();
    c.debug("o---");
    _control_.debug("o---");
    _out_.debug("*---");
    cout << "*---Except: " << base::_bin_str(11 + 15, _data_width) << endl;

    return 0;
}
