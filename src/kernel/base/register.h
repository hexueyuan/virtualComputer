#ifndef __REGISTER_H__
#define __REGISTER_H__

#include "base.h"
#include "bus.h"

/*register*/
#define REGISTER_NOT_ENABLE     0b00    //寄存器不执行任何指令
#define REGISTER_CONTAIN        0b01    //保留
#define REGISTER_WRITE          0b10    //向输出总线写数据
#define REGISTER_READ           0b11    //从输入总线读数据

//寄存器
//位长可变
//指令长2位
namespace base {
    class RegisterBase {
        public:
            //构造函数
            //_in_ 输入总线，用于数据读入
            //_out_ 输出总线，用于数据输出
            //_control_ 控制总线，控制当前周期的执行命令
            //_d_width 数据宽度，支持不同宽度的寄存器
            //_ins_active_bits_ 有效指令位，多个寄存器使用同一个控制总线，每个寄存器指令只用不同的位
            RegisterBase(BusBase* _in_, BusBase* _out_, BusBase* _control_, 
                        unsigned long _d_width, unsigned long _ins_active_bits_);
            ~RegisterBase();

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
            BusBase* _input_bus_;
            //输出总线
            BusBase* _output_bus_;
            //控制总线
            BusBase* _control_bus_;
            
            //寄存器数据
            unsigned long _register_;
            //寄存器数据宽度
            unsigned long _data_width_;
            //指令偏移
            unsigned long _instruction_active_bits_;
            //命名
            string _name_;
    };

}

#endif