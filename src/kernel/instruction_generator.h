#ifndef _INSTRUCTION_INSTRUCTION_H__
#define _INSTRUCTION_INSTRUCTION_H__

#include "options.h"
#include "cpu.h"

#include "base/memory.h"
#include "base/base.h"
#include "base/alu.h"
#include "base/register.h"
#include "base/mutil_register.h"
#include "base/selector.h"
#include "base/shiftor.h"

//一个CPU、一个主存、四个通用寄存器、八个特殊寄存器、单条内数据总线、单条内控制总线
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
namespace computer {
    class InstructionGeneratorBase {
        public:
            //
            InstructionGeneratorBase(base::RegisterBase* _r0_, base::RegisterBase* _r1_,
                                    base::RegisterBase* _r2_, base::RegisterBase* _r3_,
                                    base::RegisterBase* _ip_, base::RegisterBase* _pc_,
                                    base::RegisterBase* _sp_, base::RegisterBase* _c_,
                                    base::RegisterBase* _d_, base::MutilRegisterBase* _mar_,
                                    base::MutilRegisterBase* _mdr, base::RegisterBase* _psw_,
                                    computer::CPU* _cpu_, base::MemoryBase* _mem_,
                                    base::BusBase* _in_data_bus_, base::BusBase* _in_control_bus_,
                                    base::BusBase* _out_data_bus_, base::BusBase* _out_control_bus_,
                                    base::BusBase* _out_address_bus);
            ~InstructionGeneratorBase();
            
            //执行PC地址指向的一条指令
            void operator()();

            //
            void debug();
        
        private:
            computer::CPU* _CPU_;
            base::MemoryBase* _memory_;
            
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
            void _register_write_to_inside_bus(unsigned long _reg);
            void _register_read_from_inside_bus(unsigned long _reg);
            void _memory_write_to_outside_bus();
            void _memory_read_from_outside_bus();
            void _mov_inside_bus_to_outside_address_bus();
            void _mov_inside_bus_to_outside_data_bus();
            void _mov_outside_bus_to_inside_bus();

            //从PC寄存器中指出的地址里取出指令到IP寄存器中
            //PC+1
            void _load_instruction();

            /*指令执行阶段*/
            /*1.从PC中取指令 存放到IP*/
            /*2.微指令生成器读取IP解析*/
            /*3.取源操作数*/
            /*4.取目的操作数*/
            /*5.计算PSW值并写入PSW寄存器*/
            /*6.执行指令*/
            /*7.*/
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
}

#endif