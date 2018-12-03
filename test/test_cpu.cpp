#include <iostream>

#include "base/options.h"

#include "cpu.h"

int main() {
    base::BusBase _R0_;
    base::BusBase _R1_;
    base::BusBase _R2_;
    base::BusBase _R3_;
    base::BusBase _IP_;
    base::BusBase _PC_;
    base::BusBase _SP_;
    base::BusBase _MAR_;
    base::BusBase _MDR_;
    base::BusBase _PSW_;
    base::BusBase _C_;
    base::BusBase _D_;

    base::BusBase _out_;

    base::BusBase _control_;

    compute::CPU c(&_R0_, &_R1_, &_R2_, &_R3_, &_IP_, &_PC_, &_C_, &_D_, &_MAR_, &_MDR_, &_PSW_, &_SP_, &_out_, &_control_);
    
    c._named();
    _R0_._write(8);
    _R1_._write(15);
    _R2_._write(17);
    _R3_._write(45);
    _PC_._write(0b0011);
    _MDR_._write(78);
    
    //R1 + R2
    //  selector:R1 -> SA
    //  selector:R2 -> SB
    //  alu:R1 + R2
    //  shiftor:direct transmission
    unsigned long _ins_1_1 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_ROUTE_1 << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_NOT_ENABLE << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_NOT_ENABLE << SHIFTOR_INSTRUCTION_OFFSET);
    unsigned long _ins_1_2 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_ROUTE_2 << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_NOT_ENABLE << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_NOT_ENABLE << SHIFTOR_INSTRUCTION_OFFSET);
    unsigned long _ins_1_3 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_ADD << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_NOT_ENABLE << SHIFTOR_INSTRUCTION_OFFSET);
    unsigned long _ins_1_4 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_NOT_ENABLE << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_DIRECT_TRANSMISSION << SHIFTOR_INSTRUCTION_OFFSET);

    _control_._write(_ins_1_1);
    c();
    _control_._write(_ins_1_2);
    c();
    _control_._write(_ins_1_3);
    c();
    _control_._write(_ins_1_4);
    c();
    //cout << "answer:" << _out_._read() << endl;

    //R3 << R0
    //  selector:R3 -> SA
    //  selector:R0 -> SB
    //  alu:direct_transmission
    //  shiftor:R3 << R0
    unsigned long _ins_2_1 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_ROUTE_3 << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_NOT_ENABLE << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_NOT_ENABLE << SHIFTOR_INSTRUCTION_OFFSET);
    unsigned long _ins_2_2 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_ROUTE_0 << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_NOT_ENABLE << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_NOT_ENABLE << SHIFTOR_INSTRUCTION_OFFSET);
    unsigned long _ins_2_3 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_DIRECT_TRANSMISSION << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_NOT_ENABLE << SHIFTOR_INSTRUCTION_OFFSET);
    unsigned long _ins_2_4 = (REGISTER_NOT_WORK << COMMON_REGISTER_0_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_1_INSTRUCTION_OFFSET |
            REGISTER_NOT_WORK << COMMON_REGISTER_2_INSTRUCTION_OFFSET | 
            REGISTER_NOT_WORK << COMMON_REGISTER_3_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_A_INSTRUCTION_OFFSET |
            SELECTOR_NOT_ENABLE << SELECTOR_B_INSTRUCTION_OFFSET |
            ALU_NOT_ENABLE << ALU_INSTRUCTION_OFFSET |
            SHIFTOR_LEFT_SHIFT << SHIFTOR_INSTRUCTION_OFFSET);

    _control_._write(_ins_2_1);
    c();
    c.debug();
    _control_._write(_ins_2_2);
    c();
    _control_._write(_ins_2_3);
    c();
    _control_._write(_ins_2_4);
    c();
    cout << " input:" << bitset<DATA_BITS_SIZE>(_R3_._read()) << endl;
    cout << "answer:" << bitset<DATA_BITS_SIZE>(_out_._read()) << endl;

    return 0;
}
