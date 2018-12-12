#ifndef __CPU_H__
#define __CPU_H__

#include "base/base.h"
#include "base/selector.h"
#include "base/alu.h"
#include "base/shiftor.h"

//base/
//CPU部件由两个选择器、ALU部件和移位器组成
//八个输入端口和一个输出端口，接受一条控制总线
namespace computer {
    class CPU {
        public:
            //构造函数
            //输入：
            //  R0 ~ R3 四个通用寄存器
            //  IP 指令寄存器
            //  PC 程序计数器
            //  C、D 数据暂存器
            //  MAR 地址寄存器
            //  MDR 数据寄存器
            //  PSW 程序状态字寄存器
            //  SP  堆栈指针
            //  _out_ 输出
            //  _control_ 指令控制总线
            CPU(base::BusBase* _in_R0_, base::BusBase* _in_R1_, base::BusBase* _in_R2_, base::BusBase* _in_R3_,
                    base::BusBase* _in_IP_, base::BusBase* _in_PC_, base::BusBase* _in_C_, base::BusBase* _in_D_,
                    base::BusBase* _in_MAR_, base::BusBase* _in_MDR_, base::BusBase* _in_PSW_, base::BusBase* _in_SP_,
                    base::BusBase* _out_, base::BusBase* _control_, 
                    unsigned long _selector_A_active_bits,
                    unsigned long _selector_B_active_bits,
                    unsigned long _alu_active_bits,
                    unsigned long _shiftor_active_bits,
                    unsigned long _data_bits_width);
            ~CPU();

            //执行一次当前控制总线上的指令
            void operator()();
            //CPU命名
            void named(string _name);
            //调试
            void debug(string prefix = "");

        private:
            base::SelectorBase* _selector_A_;
            base::SelectorBase* _selector_B_;
            base::AluBase* _alu_;
            base::ShiftorBase* _shiftor_;
            base::BusBase* _selector_A_out_bus_;
            base::BusBase* _selector_B_out_bus_;
            base::BusBase* _alu_out_bus_A_;
            base::BusBase* _alu_out_bus_B_;
            string _name_;
    };
}

#endif