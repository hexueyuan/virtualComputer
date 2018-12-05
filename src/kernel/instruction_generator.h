#include "base/options.h"
#include "base/register.h"
#include "base/mutil_register.h"
#include "base/bus.h"
#include "base/bits.h"
#include "memory.h"
#include "cpu.h"

#ifndef _MIRCO_INSTRUCTION_H__
#define _MIRCO_INSTRUCTION_H__

#define DATA_BITS_WIDTH 32   //数据宽度
#define INSIDE_CONTROL_BITS_WIDTH 39 //内控制总线宽度
#define OUTSIDE_ADDRESS_BITS_WIDTH 12 //外地址总线宽度
#define OUTSIDE_DATA_BITS_WIDTH 32 //外数据总线宽度
#define OUTSIZE_CONTROL_BITS_WIDTH 2 //外控制总线宽度
#define MEMORY_UNIT_BITS_SIZE 32    //存储单元大小

//内控制总线指令有效位定义
#define SHIFTOR_ACTIVE_BITS             0b110000000000000000000000000000000000000
#define ALU_ACTIVE_BITS                 0b001110000000000000000000000000000000000
#define SELECTOR_A_ACTIVE_BITS          0b000001111000000000000000000000000000000
#define SELECTOR_B_ACTIVE_BITS          0b000000000111100000000000000000000000000
#define REGISTER_0_ACTIVE_BITS          0b000000000000011000000000000000000000000
#define REGISTER_1_ACTIVE_BITS          0b000000000000000110000000000000000000000
#define REGISTER_2_ACTIVE_BITS          0b000000000000000001100000000000000000000
#define REGISTER_3_ACTIVE_BITS          0b000000000000000000011000000000000000000
#define REGISTER_IP_ACTIVE_BITS         0b000000000000000000000110000000000000000
#define REGISTER_PC_ACTIVE_BITS         0b000000000000000000000001100000000000000
#define REGISTER_SP_ACTIVE_BITS         0b000000000000000000000000011000000000000
#define REGISTER_PSW_ACTIVE_BITS        0b000000000000000000000000000110000000000
#define REGISTER_C_ACTIVE_BITS          0b000000000000000000000000000001100000000
#define REGISTER_D_ACTIVE_BITS          0b000000000000000000000000000000011000000
#define REGISTER_MAR_ACTIVE_BITS        0b000000000000000000000000000000000111000
#define REGISTER_MDR_ACTIVE_BITS        0b000000000000000000000000000000000000111

//指令集
#define INSTRUCTION_NOP     0b0000
#define INSTRUCTION_MOV     0b0001
#define INSTRUCTION_ADD     0b0010
#define INSTRUCTION_ZERO    0b0011
#define INSTRUCTION_LSFT    0b0100
#define INSTRUCTION_RSFT    0b0101
#define INSTRUCTION_AND     0b0110
#define INSTRUCTION_OR      0b0111
#define INSTRUCTION_NOT     0b1000
#define INSTRUCTION_XOR     0b1001
#define INSTRUCTION_CMP     0b1010
#define INSTRUCTION_JMP     0b1011
#define INSTRUCTION_JMPP    0b1100
#define INSTRUCTION_JMPN    0b1101
#define INSTRUCTION_JMPZ    0b1110
#define INSTRUCTION_CONTAIN 0b1111

//寻址方式
#define ADDRESS_REGISTER    0b00
#define ADDRESS_NUMBER      0b01
#define ADDRESS_MEMORY      0b10
#define ADDRESS_CONTAIN     0b11

//指令有效位
#define INSTRUCTION_TYPE                    0b11110000000000000000000000000000
#define OPERATE_NUMBER_1_ADDRESS_METHOD     0b00001100000000000000000000000000
#define OPERATE_NUMBER_1                    0b00000011111111111100000000000000
#define OPERATE_NUMBER_2_ADDRESS_METHOD     0b00000000000000000011000000000000
#define OPERATE_NUMBER_2                    0b00000000000000000000111111111111

//寄存器编号
#define REGISTER_0      0b000000000000
#define REGISTER_1      0b000000000001
#define REGISTER_2      0b000000000010
#define REGISTER_3      0b000000000011
#define REGISTER_IP     0b000000000100
#define REGISTER_PC     0b000000000101
#define REGISTER_SP     0b000000000110
#define REGISTER_C      0b000000000111
#define REGISTER_D      0b000000001000
#define REGISTER_MAR    0b000000001001
#define REGISTER_MDR    0b000000001010
#define REGISTER_PSW    0b000000001011

unsigned long _inside_ins_nop_ = (base::_generate_instruction(SHIFTOR_NOT_ENABLE, SHIFTOR_ACTIVE_BITS) | 
                            base::_generate_instruction(ALU_NOT_ENABLE, ALU_ACTIVE_BITS) |
                            base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_A_ACTIVE_BITS) |
                            base::_generate_instruction(SELECTOR_NOT_ENABLE, SELECTOR_B_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_0_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_1_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_2_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_3_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_IP_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_PC_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_SP_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_PSW_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_C_ACTIVE_BITS) |
                            base::_generate_instruction(REGISTER_NOT_ENABLE, REGISTER_D_ACTIVE_BITS) |
                            base::_generate_instruction(MUTIL_REGISTER_NOT_ENABLE, REGISTER_MAR_ACTIVE_BITS) |
                            base::_generate_instruction(MUTIL_REGISTER_NOT_ENABLE, REGISTER_MDR_ACTIVE_BITS));
unsigned long _outside_ins_nop_ = 0b00;
//一个CPU、一个主存、一个辅存、四个通用寄存器、八个特殊寄存器、单条内数据总线、单条内控制总线
//单条外数据总线、单条外控制总线、单条外地址总线

//微指令生成器&计算机指令执行控制器
//提供常用的几条汇编指令的微指令并控制系统执行
//NOP   空指令，无参数          0b0000
//MOV   转移指令，双参数        0b0001
//ADD   逻辑加法，双参数        2
//ZERO  判零，单参数            3
//LSFT  逻辑左移，双参数        4
//RSFT  逻辑右移，双参数        5
//AND   逻辑与                  6
//OR    逻辑或                  7
//NOT   逻辑非                  8
//XOR   逻辑异或                9
//CMP   比较指令，双参数            10
//JMP   无条件跳转，单参数              11
//JMPP  正值跳转，单参数                12
//JMPN  负值跳转，单参数                13
//JMPZ  零值跳转，单参数                14
namespace compute {
    class InstructionGeneratorBase {
        public:
            //
            InstructionGeneratorBase();
            ~InstructionGeneratorBase();
            
            //执行传入的汇编指令
            void operator()(unsigned long _ins);
        
        private:
            compute::CPU* _CPU_;
            compute::MemoryBase* _memory_;
            
            base::RegisterBase* _R0_;
            base::RegisterBase* _R1_;
            base::RegisterBase* _R2_;
            base::RegisterBase* _R3_;
            base::RegisterBase* _IP_;
            base::RegisterBase* _PC_;
            base::RegisterBase* _SP_;
            base::RegisterBase* _C_;
            base::RegisterBase* _D_;
            base::MutilRegisterBase* _MAR_;
            base::MutilRegisterBase* _MDR_;
            base::RegisterBase* _PSW_;

            base::BusBase* _inside_data_bus_;
            base::BusBase* _inside_control_bus_;

            base::BusBase* _outside_address_bus_;
            base::BusBase* _outside_data_bus_;
            base::BusBase* _outside_control_bus_;

            void _run_once();
            void _register_write_to_inside_bus();
            void _register_read_from_inside_bus();
            void _memory_write_to_outside_bus();
            void _memory_read_from_outside_bus();
            void _mov_inside_bus_to_outside_bus();
            void _mov_outside_bus_to_inside_bus();

            /*---------指令-----------*/
            void _NOP(unsigned long _ins);
            void _MOV(unsigned long _ins);
            void _ADD(unsigned long _ins);
            void _ZERO(unsigned long _ins);
            void _LSFT(unsigned long _ins);
            void _RSFT(unsigned long _ins);
            void _AND(unsigned long _ins);
            void _OR(unsigned long _ins);
            void _NOT(unsigned long _ins);
            void _XOR(unsigned long _ins);
            void _CMP(unsigned long _ins);
            void _JMP(unsigned long _ins);
            void _JMPZ(unsigned long _ins);
            void _JMPP(unsigned long _ins);
            void _JMPN(unsigned long _ins);
   };

   InstructionGeneratorBase::InstructionGeneratorBase() {
        //创建内总线
        _inside_data_bus_ = new base::BusBase(DATA_BITS_WIDTH);
        _inside_data_bus_ -> named("inside_data_bus");

        _inside_control_bus_ = new base::BusBase(INSIDE_CONTROL_BITS_WIDTH);
        _inside_control_bus_ -> named("inside_control_bus");

        //创建外总线
        _outside_address_bus_ = new base::BusBase(OUTSIDE_ADDRESS_BITS_WIDTH);
        _outside_address_bus_ -> named("outside_address_bus");

        _outside_data_bus_ = new base::BusBase(OUTSIDE_DATA_BITS_WIDTH);
        _outside_data_bus_ -> named("outside_data_bus");

        _outside_control_bus_ = new base::BusBase(OUTSIZE_CONTROL_BITS_WIDTH);
        _outside_control_bus_ -> named("outside_control_bus");

        //创建寄存器组
        _R0_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_0_ACTIVE_BITS);
        _R1_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_1_ACTIVE_BITS);
        _R2_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_2_ACTIVE_BITS);
        _R3_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_3_ACTIVE_BITS);
        _IP_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_IP_ACTIVE_BITS);
        _PC_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_PC_ACTIVE_BITS);
        _SP_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_SP_ACTIVE_BITS);
        _PSW_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_PSW_ACTIVE_BITS);
        _C_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_C_ACTIVE_BITS);
        _D_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_D_ACTIVE_BITS);
        _MAR_ = new base::MutilRegisterBase(_inside_data_bus_, _outside_address_bus_, _inside_data_bus_, _outside_address_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_MAR_ACTIVE_BITS);
        _MDR_ = new base::MutilRegisterBase(_inside_data_bus_, _outside_data_bus_, _inside_data_bus_, _outside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_MDR_ACTIVE_BITS);

        _R0_ -> named("Register0");
        _R1_ -> named("Register1");
        _R2_ -> named("Register2");
        _R3_ -> named("Register3");
        _IP_ -> named("RegisterIP");
        _PC_ -> named("RegisterPC");
        _SP_ -> named("RegisterSP");
        _PSW_ -> named("RegisterPSW");
        _C_ -> named("RegisterC");
        _D_ -> named("RegisterD");
        _MAR_ -> named("RegisterMAR");
        _MDR_ -> named("RegisterMDR");

        //创建CPU
        _CPU_ = new compute::CPU(_inside_data_bus_, _inside_data_bus_, _inside_data_bus_, 
                                    _inside_data_bus_, _inside_data_bus_, _inside_data_bus_, 
                                    _inside_data_bus_, _inside_data_bus_, _inside_data_bus_,
                                    _inside_data_bus_, _inside_data_bus_, _inside_data_bus_,
                                    _inside_data_bus_, _inside_control_bus_,
                                    SELECTOR_A_ACTIVE_BITS,
                                    SELECTOR_B_ACTIVE_BITS,
                                    ALU_ACTIVE_BITS,
                                    SHIFTOR_ACTIVE_BITS);
        _CPU_ -> named("CPU");

        //创建内存
        _memory_ = new compute::MemoryBase(_outside_data_bus_, _outside_data_bus_, 
                                            _outside_control_bus_, _outside_address_bus_, 
                                            MEMORY_UNIT_BITS_SIZE, 1 << OUTSIDE_ADDRESS_BITS_WIDTH);
        _memory_ -> named("Memory");
   }

   InstructionGeneratorBase::~InstructionGeneratorBase() {
       delete _R0_;
       delete _R1_;
       delete _R2_;
       delete _R3_;
       delete _IP_;
       delete _PC_;
       delete _SP_;
       delete _PSW_;
       delete _MAR_;
       delete _MDR_;
       delete _CPU_;
       delete _inside_control_bus_;
       delete _inside_data_bus_;
       delete _outside_address_bus_;
       delete _outside_control_bus_;
       delete _outside_data_bus_;
       delete _memory_;
   }

   void InstructionGeneratorBase::_run_once() {
       (*_R0_)();
       (*_R1_)();
       (*_R2_)();
       (*_R3_)();
       (*_IP_)();
       (*_PC_)();
       (*_SP_)();
       (*_PSW_)();
       (*_C_)();
       (*_D_)();
       (*_MAR_)();
       (*_MDR_)();
       (*_CPU_)();
       (*_memory_)();
   }

    void InstructionGeneratorBase::operator()(unsigned long _ins) {
        unsigned long _instruction_type = base::_extract_instruction(_ins, INSTRUCTION_TYPE);
        switch (_instruction_type) {
            case INSTRUCTION_MOV:
                _MOV(_ins);
                break;
            case INSTRUCTION_ADD:
                _ADD(_ins);
                break;
            case INSTRUCTION_ZERO:
                _ZERO(_ins);
                break;
            case INSTRUCTION_LSFT:
                _LSFT(_ins);
                break;
            case INSTRUCTION_RSFT:
                _RSFT(_ins);
                break;
            case INSTRUCTION_AND:
                _AND(_ins);
                break;
            case INSTRUCTION_OR:
                _OR(_ins);
                break;
            case INSTRUCTION_NOT:
                _NOT(_ins);
                break;
            case INSTRUCTION_XOR:
                _XOR(_ins);
                break;
            case INSTRUCTION_CMP:
                _CMP(_ins);
                break;
            case INSTRUCTION_JMP:
                _JMP(_ins);
                break;
            case INSTRUCTION_JMPZ:
                _JMPZ(_ins);
                break;
            case INSTRUCTION_JMPP:
                _JMPP(_ins);
                break;
            case INSTRUCTION_JMPN:
                _JMPN(_ins);
                break;
            default:
                _NOP(_ins);
                break;
        }
    }

    void InstructionGeneratorBase::_NOP(unsigned long _ins) {
        return;
    }

    void InstructionGeneratorBase::_MOV(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            unsigned long _ins_1_;
            switch (_op_1_) {
                case REGISTER_0:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_0_ACTIVE_BITS);
                    break;
                case REGISTER_1:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_1_ACTIVE_BITS);
                    break;
                case REGISTER_2:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_2_ACTIVE_BITS);
                    break;
                case REGISTER_3:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_3_ACTIVE_BITS);
                    break;
                case REGISTER_IP:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_IP_ACTIVE_BITS);
                    break;
                case REGISTER_PC:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_PC_ACTIVE_BITS);
                    break;
                case REGISTER_SP:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_SP_ACTIVE_BITS);
                    break;
                case REGISTER_C:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_C_ACTIVE_BITS);
                    break;
                case REGISTER_D:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_D_ACTIVE_BITS);
                    break;
                case REGISTER_PSW:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_PSW_ACTIVE_BITS);
                    break;
                case REGISTER_MAR:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_MAR_ACTIVE_BITS);
                    break;
                case REGISTER_MDR:
                    _ins_1_ = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_MDR_ACTIVE_BITS);
                    break;
                default:
                    _ins_1_ = _inside_ins_nop_;
            }
            _inside_control_bus_ -> write(_ins_1_);
            _outside_control_bus_ -> write(_outside_ins_nop_);
            _run_once();
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            _inside_data_bus_ -> write(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {

        }
    }

    void InstructionGeneratorBase::_ADD(unsigned long _ins) {}
    void InstructionGeneratorBase::_AND(unsigned long _ins) {}
    void InstructionGeneratorBase::_OR(unsigned long _ins) {}
    void InstructionGeneratorBase::_NOT(unsigned long _ins) {}
    void InstructionGeneratorBase::_XOR(unsigned long _ins) {}
    void InstructionGeneratorBase::_ZERO(unsigned long _ins) {}
    void InstructionGeneratorBase::_LSFT(unsigned long _ins) {}
    void InstructionGeneratorBase::_RSFT(unsigned long _ins) {}
    void InstructionGeneratorBase::_CMP(unsigned long _ins) {}
    void InstructionGeneratorBase::_JMP(unsigned long _ins) {}
    void InstructionGeneratorBase::_JMPZ(unsigned long _ins) {}
    void InstructionGeneratorBase::_JMPN(unsigned long _ins) {}
    void InstructionGeneratorBase::_JMPP(unsigned long _ins) {}
}

#endif
