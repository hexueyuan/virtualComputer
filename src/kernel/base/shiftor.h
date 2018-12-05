#include "options.h"
#include "bus.h"

#ifndef __SHIFTOR_H__
#define __SHIFTOR_H__

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

    ShiftorBase::ShiftorBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_, 
                        BusBase* _control_, unsigned long _ins_active_bits_) {
        _input_bus_A_ = _in_A_;
        _input_bus_B_ = _in_B_;
        _output_bus_ = _out_;
        _control_bus_ = _control_;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    ShiftorBase::~ShiftorBase() {}

    void ShiftorBase::operator()() {
        _instruction_ = _extract_instruction(_control_bus_ -> read(), _instruction_active_bits_);

        switch (_instruction_) {
            case SHIFTOR_NOT_ENABLE:
                break;
            case SHIFTOR_LEFT_SHIFT:
                _left_shift();
                break;
            case SHIFTOR_RIGHT_SHIFT:
                _right_shift();
                break;
            case SHIFTOR_DIRECT_TRANSMISSION:
                _direct_transmission();
                break;
            default:
                break;
        }
    }

    void ShiftorBase::named(string _name) {
        _name_ = _name;
    }

    void ShiftorBase::_left_shift() {
        _output_bus_ -> write((_input_bus_A_ -> read()) << (_input_bus_B_ -> read()));
    }

    void ShiftorBase::_right_shift() {
        _output_bus_ -> write((_input_bus_A_ -> read()) >> (_input_bus_B_ -> read()));
    }

    void ShiftorBase::_direct_transmission() {
        _output_bus_ -> write(_input_bus_A_ -> read());
    }

    void ShiftorBase::debug(string prefix) {
        string space(prefix.length(), ' ');
        cout << prefix << "Shiftor(" + _name_ + ") instruction: " << _bin_str(_instruction_, 
                    _active_bits_size(_instruction_active_bits_)) << endl;
        cout << space << "Shiftor(" + _name_ + ") input_bus_A: " << _input_bus_A_ -> name() << endl;
        cout << space << "Shiftor(" + _name_ + ") input_bus_B: " << _input_bus_B_ -> name() << endl;
        cout << space << "Shiftor(" + _name_ + ") output_bus: " << _output_bus_ -> name() << endl;
        cout << prefix << "Shiftor(" + _name_ + ") control_bus: " << _control_bus_ -> name() << endl;
    }
}

#endif