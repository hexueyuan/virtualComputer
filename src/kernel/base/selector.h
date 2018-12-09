#ifndef __SELECTOR_H__
#define __SELECTOR_H__

#include "base.h"

/*selector.h*/
#define SELECTOR_NOT_ENABLE     0b0000  //选择器不执行指令
#define SELECTOR_CONTAIN_0      0b0001  //保留
#define SELECTOR_CONTAIN_1      0b0010  //保留
#define SELECTOR_CONTAIN_2      0b0011  //保留
#define SELECTOR_CONTAIN_3      0b0100  //保留
#define SELECTOR_CONTAIN_4      0b0101  //保留
#define SELECTOR_CONTAIN_5      0b0110  //保留
#define SELECTOR_CONTAIN_6      0b0111  //保留
#define SELECTOR_ROUTE_0        0b1000  //选择路由0
#define SELECTOR_ROUTE_1        0b1001  //选择路由1
#define SELECTOR_ROUTE_2        0b1010  //选择路由2
#define SELECTOR_ROUTE_3        0b1011  //选择路由3
#define SELECTOR_ROUTE_4        0b1100  //选择路由4
#define SELECTOR_ROUTE_5        0b1101  //选择路由5
#define SELECTOR_ROUTE_6        0b1110  //选择路由6
#define SELECTOR_ROUTE_7        0b1111  //选择路由7

//八路选择器
//ALU使用选择器从多个寄存器中获取数据
//指令长度4位，其中3位用于选路，1位用于控制使能
namespace base {
    class SelectorBase {
        public:
            //构造函数
            //输入参数 _in_0_ ~ _in_7_ 输入总线
            //          _out_ 输出总线
            //          _control_ 控制总线
            //          _ins_active_bits_ 指令偏移
            SelectorBase(BusBase* _in_0_, BusBase* _in_1_, BusBase* _in_2_, BusBase* _in_3_,
                        BusBase* _in_4_, BusBase* _in_5_, BusBase* _in_6_, BusBase* _in_7_,
                        BusBase* _out_, BusBase* _control_, unsigned long _ins_active_bits_);
            ~SelectorBase();

            //选择执行当前控制总线中的指令
            void operator()();

            //选择器命名
            void named(string _name);
            //调试信息
            void debug(string tab);
            //返回命名
            string name();

        private:
            BusBase* _input_bus_0_;
            BusBase* _input_bus_1_;
            BusBase* _input_bus_2_;
            BusBase* _input_bus_3_;
            BusBase* _input_bus_4_;
            BusBase* _input_bus_5_;
            BusBase* _input_bus_6_;
            BusBase* _input_bus_7_;
            BusBase* _output_bus_;
            BusBase* _control_bus_;

            //bitset<SELECTOR_INSTRUCTION_BITS_SIZE> _instruction_;
            unsigned long _instruction_;
            unsigned long _instruction_active_bits_;
            string _name_;
    };

    SelectorBase::SelectorBase(BusBase* _in_0_, BusBase* _in_1_, BusBase* _in_2_, BusBase* _in_3_,
                            BusBase* _in_4_, BusBase* _in_5_, BusBase* _in_6_, BusBase* _in_7_,
                            BusBase* _out_, BusBase* _control_, unsigned long _ins_active_bits_) {
        _input_bus_0_ = _in_0_;
        _input_bus_1_ = _in_1_;
        _input_bus_2_ = _in_2_;
        _input_bus_3_ = _in_3_;
        _input_bus_4_ = _in_4_;
        _input_bus_5_ = _in_5_;
        _input_bus_6_ = _in_6_;
        _input_bus_7_ = _in_7_;
        _output_bus_ = _out_;
        _control_bus_ = _control_;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    SelectorBase::~SelectorBase() {}

    void SelectorBase::operator()() {
        _instruction_ = base::_extract_instruction(_control_bus_ -> out(), _instruction_active_bits_);
        //_instruction_ = (_control_bus_ -> read()) >> _instruction_offset_;

        switch(_instruction_) {
            case SELECTOR_ROUTE_0:
                _output_bus_ -> in(_input_bus_0_ -> out());
                break;
            case SELECTOR_ROUTE_1:
                _output_bus_ -> in(_input_bus_1_ -> out());
                break;
            case SELECTOR_ROUTE_2:
                _output_bus_ -> in(_input_bus_2_ -> out());
                break;
            case SELECTOR_ROUTE_3:
                _output_bus_ -> in(_input_bus_3_ -> out());
                break;
            case SELECTOR_ROUTE_4:
                _output_bus_ -> in(_input_bus_4_ -> out());
                break;
            case SELECTOR_ROUTE_5:
                _output_bus_ -> in(_input_bus_5_ -> out());
                break;
            case SELECTOR_ROUTE_6:
                _output_bus_ -> in(_input_bus_6_ -> out());
                break;
            case SELECTOR_ROUTE_7:
                _output_bus_ -> in(_input_bus_7_ -> out());
                break;
            case SELECTOR_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void SelectorBase::named(string _name) {
        _name_ = _name;
    }

    void SelectorBase::debug(string tab) {
        string space(tab.length(), ' ');
        unsigned long _instruction = base::_extract_instruction(_control_bus_ -> out(), _instruction_active_bits_);
        cout << tab << "Selector(" + _name_ + ") instruction: " << \
            base::_bin_str(_instruction, base::_active_bits_size(_instruction_active_bits_)) << endl;
        cout << space << "Selector(" + _name_ + ") control bus: " << _control_bus_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 0: " << _input_bus_0_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 1: " << _input_bus_1_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 2: " << _input_bus_2_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 3: " << _input_bus_3_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 4: " << _input_bus_4_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 5: " << _input_bus_5_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 6: " << _input_bus_6_ -> name() << endl;
        cout << space << "Selector(" + _name_ + ") route 7: " << _input_bus_7_ -> name() << endl;
        cout << tab << "Selector(" + _name_ + ") output: " << _output_bus_ -> name() << endl;
    }

    string SelectorBase::name() {
        return _name_;
    }
}

#endif