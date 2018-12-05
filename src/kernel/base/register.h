#include "options.h"
#include "bus.h"
#include "bits.h"

#ifndef __REGISTER_H__
#define __REGISTER_H__

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
            void debug(string tab="");
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
            //bitset<REGISTER_BITS_SIZE> _register_;
            //寄存器数据宽度
            unsigned long _data_width_;
            //指令
            unsigned long _instruction_;
            //bitset<REGISTER_INSTRUCTION_BITS_SIZE> _instruction_;
            //指令偏移
            unsigned long _instruction_active_bits_;
            //命名
            string _name_;
    };

    RegisterBase::RegisterBase(BusBase* _in_, BusBase* _out_, BusBase* _control_, 
                            unsigned long _d_width, unsigned long _ins_active_bits_) {
        _input_bus_ = _in_;
        _output_bus_ = _out_;
        _control_bus_ = _control_;
        _data_width_ = _d_width;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    RegisterBase::~RegisterBase() {};

    void RegisterBase::operator()() {
        unsigned long _offset = base::_active_bits_offset(_instruction_active_bits_);
        _instruction_ = (((_control_bus_ -> read()) & _instruction_active_bits_) >> _offset);

        switch (_instruction_) {
            case REGISTER_READ:
                _register_ = (_input_bus_ -> read()) & (((unsigned long)1 << (_data_width_)) - 1);
                break;
            case REGISTER_WRITE:
                _output_bus_ -> write(_register_);
                break;
            case REGISTER_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void RegisterBase::named(string _name) {
        _name_ = _name;
    }

    void RegisterBase::debug(string tab) {
        unsigned long _size = base::_active_bits_size(_instruction_active_bits_);
        string _space(tab.length(), ' ');
        cout << tab << "Register(" + _name_ + ") instruction: " << base::_bin_str(_instruction_, _size) << endl;
        cout << _space << "Register(" + _name_ + ") value: " << base::_bin_str(_register_, _data_width_) << endl;
        cout << _space << "Register(" + _name_ + ") instruction_offset: " << _instruction_active_bits_ << endl;
        cout << _space << "Register(" + _name_ + ") data_width: " << _data_width_ << endl;
        cout << _space << "Register(" + _name_ + ") control_bus: " << _control_bus_ -> name() << endl;
        cout << _space << "Register(" + _name_ + ") input_bus: " << _input_bus_ -> name() << endl;
        cout << tab << "Register(" + _name_ + ") output_bus: " << _output_bus_ -> name() << endl;
    }

    string RegisterBase::name() {
        return _name_;
    }
}

#endif