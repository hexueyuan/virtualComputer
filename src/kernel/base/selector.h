#include "options.h"
#include "bus.h"

#ifndef __SELECTOR_H__
#define __SELECTOR_H__

//八路选择器
namespace base {
    class SelectorBase {
        public:
            SelectorBase(BusBase* _in_0_, BusBase* _in_1_, BusBase* _in_2_, BusBase* _in_3_,
                        BusBase* _in_4_, BusBase* _in_5_, BusBase* _in_6_, BusBase* _in_7_,
                        BusBase* _out_, BusBase* _control_, unsigned long _ins_offset_);
            ~SelectorBase();

            void operator()();

            void _named(string _name);
            void debug();

        private:
            BusBase* _input_0_;
            BusBase* _input_1_;
            BusBase* _input_2_;
            BusBase* _input_3_;
            BusBase* _input_4_;
            BusBase* _input_5_;
            BusBase* _input_6_;
            BusBase* _input_7_;
            BusBase* _output_;
            BusBase* _control_bus_;

            bitset<SELECTOR_INSTRUCTION_BITS_SIZE> _instruction_;
            unsigned long _instruction_offset_;
            string _name_;
    };

    SelectorBase::SelectorBase(BusBase* _in_0_, BusBase* _in_1_, BusBase* _in_2_, BusBase* _in_3_,
                            BusBase* _in_4_, BusBase* _in_5_, BusBase* _in_6_, BusBase* _in_7_,
                            BusBase* _out_, BusBase* _control_, unsigned long _ins_offset_) {
        _input_0_ = _in_0_;
        _input_1_ = _in_1_;
        _input_2_ = _in_2_;
        _input_3_ = _in_3_;
        _input_4_ = _in_4_;
        _input_5_ = _in_5_;
        _input_6_ = _in_6_;
        _input_7_ = _in_7_;
        _output_ = _out_;
        _control_bus_ = _control_;
        _instruction_offset_ = _ins_offset_;
    }

    SelectorBase::~SelectorBase() {}

    void SelectorBase::operator()() {
        _instruction_ = (_control_bus_ -> read()) >> _instruction_offset_;

        switch(_instruction_.to_ulong()) {
            case SELECTOR_ROUTE_0:
                _output_ -> write(_input_0_ -> read());
                break;
            case SELECTOR_ROUTE_1:
                _output_ -> write(_input_1_ -> read());
                break;
            case SELECTOR_ROUTE_2:
                _output_ -> write(_input_2_ -> read());
                break;
            case SELECTOR_ROUTE_3:
                _output_ -> write(_input_3_ -> read());
                break;
            case SELECTOR_ROUTE_4:
                _output_ -> write(_input_3_ -> read());
                break;
            case SELECTOR_ROUTE_5:
                _output_ -> write(_input_3_ -> read());
                break;
            case SELECTOR_ROUTE_6:
                _output_ -> write(_input_3_ -> read());
                break;
            case SELECTOR_ROUTE_7:
                _output_ -> write(_input_3_ -> read());
                break;
            case SELECTOR_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void SelectorBase::_named(string _name) {
        _name_ = _name;
    }

    void SelectorBase::debug() {
        cout << "Selector " + _name_ + " instruction: " << _instruction_ << endl;
        cout << "Selector " + _name_ + " input 0: " << bitset<64>(_input_0_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 1: " << bitset<64>(_input_1_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 2: " << bitset<64>(_input_2_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 3: " << bitset<64>(_input_3_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 4: " << bitset<64>(_input_4_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 5: " << bitset<64>(_input_5_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 6: " << bitset<64>(_input_6_ -> read()) << endl;
        cout << "Selector " + _name_ + " input 7: " << bitset<64>(_input_7_ -> read()) << endl;
        cout << "Selector " + _name_ + " output: " << bitset<64>(_output_ -> read()) << endl;
    }
}

#endif
