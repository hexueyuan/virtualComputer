#ifndef __MUTIL_REGISTER_H__
#define __MUTIL_REGISTER_H__

#include "base.h"
#include "bus.h"

#define MUTIL_REGISTER_NOT_ENABLE   0b000   //空指令，寄存器无动作
#define MUTIL_REGISTER_READ_A       0b100   //从输入总线A读取数据
#define MUTIL_REGISTER_READ_B       0b101   //从输入总线B读取数据
#define MUTIL_REGISTER_WRITE_A      0b110   //向输出总线A输出数据
#define MUTIL_REGISTER_WRITE_B      0b111   //向输出总线B输出数据

//双口I/O寄存器
//位长可变
//指令长3位
//MAR与MDR需要向内总线和外总线输出数据，因此需要匹配双输出总线
namespace base {
    class MutilRegisterBase {
        public:
            //构造函数
            //_in_A_ 输入总线A，用于数据读入
            //_in_B_ 输入总线B，用于数据读入
            //_out_B_ 输出总线A，用于数据输出
            //_out_B_ 输出总线B，用于数据输出
            //_control_ 控制总线，控制当前周期的执行命令
            //_d_width 数据宽度，支持不同宽度的寄存器
            //_ins_active_bits_ 有效指令位，多个寄存器使用同一个控制总线，每个寄存器指令只用不同的位
            MutilRegisterBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                        BusBase* _control_, unsigned long _d_width, unsigned long _ins_active_bits_);
            ~MutilRegisterBase();

            //执行控制总线上的命令
            void operator()();

            //寄存器命名
            void named(string _name);
            //调试
            void debug(string prefix="");
            //返回命名
            string name();

        private:
            //输入总线
            BusBase* _input_bus_A_;
            BusBase* _input_bus_B_;
            //输出总线
            BusBase* _output_bus_A_;
            BusBase* _output_bus_B_;
            //控制总线
            BusBase* _control_bus_;
            
            //寄存器数据
            unsigned long _register_;
            //bitset<REGISTER_BITS_SIZE> _register_;
            //寄存器数据宽度
            unsigned long _data_width_;
            //指令偏移
            unsigned long _instruction_active_bits_;
            //命名
            string _name_;
    };
}

#endif