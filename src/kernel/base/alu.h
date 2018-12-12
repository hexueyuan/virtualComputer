#ifndef __ALU_H__
#define __ALU_H__

#include "base.h"
#include "bus.h"
#include "bits.h"

/*alu.h*/
#define ALU_NOT_ENABLE          0b000   //ALU不执行指令
#define ALU_ARITHMETIC_ADD      0b001   //算术加法
#define ALU_LOGIC_AND           0b010   //逻辑与
#define ALU_LOGIC_OR            0b011   //逻辑或
#define ALU_LOGIC_NOT           0b100   //逻辑非
#define ALU_DIRECT_TRANSMISSION 0b101   //数据直传
#define ALU_LOGIC_XOR           0b110   //保留
#define ALU_CONTAIN_2           0b111   //保留

//ALU机器计算部件
//执行逻辑运算和加法运算
//指令长3位
namespace base {
    class AluBase {
        public:
            //构造函数
            //输入：_in_A_ 输入总线A
            //      _in_B_ 输入总线B
            //      _out_A_ 输出总线A
            //      _out_B_ 输出总线B
            //      _control_ 控制总线
            //      _ins_active_bits_ 指令有效位
            //ALU与selector串联，数据经选择器连接到ALU，再连接到selector，因为selector由双输入，所以这里ALU双输出
            AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                    BusBase* _control_, unsigned long _ins_active_bits_);
            ~AluBase();

            //执行当前控制总线上的一条指令
            void operator()();
            //调试
            void debug(string prefix = "");
            //命名
            void named(string _name_);

        private:
            BusBase* _input_bus_A_;
            BusBase* _input_bus_B_;
            BusBase* _output_bus_A_;
            BusBase* _output_bus_B_;
            BusBase* _control_bus_;

            unsigned long _instruction_;
            unsigned long _instruction_active_bits_;
            string _alu_name_;

            //算术加法
            void _ARITHMETIC_ADD();
            //逻辑与
            void _LOGIC_AND();
            //逻辑或
            void _LOGIC_OR();
            //逻辑非
            void _LOGIC_NOT();
            //直传
            void _DIRECT_TRANSMISSION();
            //逻辑异或
            void _LOGIC_XOR();
    };
}

#endif
