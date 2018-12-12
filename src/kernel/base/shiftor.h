#ifndef __SHIFTOR_H__
#define __SHIFTOR_H__

#include "base.h"
#include "bus.h"

/*shiftor.h*/
#define SHIFTOR_NOT_ENABLE          0b00    //移位器不执行指令
#define SHIFTOR_LEFT_SHIFT          0b01    //逻辑左移
#define SHIFTOR_RIGHT_SHIFT         0b10    //逻辑右移
#define SHIFTOR_DIRECT_TRANSMISSION 0b11    //数据直传

//移位器
//指令长2位
namespace base {
    class ShiftorBase {
        public:
            //构造函数
            //输入 _in_A_ 数据输入总线A
            //      _in_B_ 数据输入总线B
            //      _out_ 输出总线
            //      _control_ 控制总线
            //      _ins_active_bits_ 有效指令位
            ShiftorBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_, 
                            BusBase* _control_, unsigned long _ins_active_bits_);
            ~ShiftorBase();

            //执行一次当前控制总线上的指令
            void operator()();

            //命名
            void named(string _name);
            //调试
            void debug(string prefix = "");

        private:
            BusBase* _input_bus_A_;
            BusBase* _input_bus_B_;
            BusBase* _output_bus_;
            BusBase* _control_bus_;

            //bitset<SHIFTOR_INSTRUCTION_BITS_SIZE> _instruction_;
            unsigned long _instruction_;
            unsigned long _instruction_active_bits_;
            string _name_;

            void _left_shift();
            void _right_shift();
            void _direct_transmission();
    };
}

#endif