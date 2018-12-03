#include "options.h"
#include "bus.h"

#ifndef __SHIFTOR_H__
#define __SHIFTOR_H__

namespace base {
    class ShiftorBase {
        public:
            ShiftorBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_, BusBase* _control_, unsigned long _ins_offset_);
            ~ShiftorBase();

            void operator()();

            void _named(string _name);
            void debug();

        private:
            BusBase* _input_bus_A_;
            BusBase* _input_bus_B_;
            BusBase* _output_bus_;
            BusBase* _control_bus_;

            bitset<SHIFTOR_INSTRUCTION_BITS_SIZE> _instruction_;
            unsigned long _instruction_offset_;
            string _name_;

            void _left_shift();
            void _right_shift();
            void _direct_transmission();
    };

    ShiftorBase::ShiftorBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_, BusBase* _control_, unsigned long _ins_offset_) {
        _input_bus_A_ = _in_A_;
        _input_bus_B_ = _in_B_;
        _output_bus_ = _out_;
        _control_bus_ = _control_;
        _instruction_offset_ = _ins_offset_;
    }

    ShiftorBase::~ShiftorBase() {}

    void ShiftorBase::operator()() {
        _instruction_ = (_control_bus_ -> _read()) >> _instruction_offset_;

        switch (_instruction_.to_ulong()) {
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

    void ShiftorBase::_named(string _name) {
        _name_ = _name;
    }

    void ShiftorBase::_left_shift() {
        _output_bus_ -> _write((_input_bus_A_ -> _read()) << (_input_bus_B_ -> _read()));
    }

    void ShiftorBase::_right_shift() {
        _output_bus_ -> _write((_input_bus_A_ -> _read()) >> (_input_bus_B_ -> _read()));
    }

    void ShiftorBase::_direct_transmission() {
        _output_bus_ -> _write(_input_bus_A_ -> _read());
    }

    void ShiftorBase::debug() {
        cout << "Shiftor " + _name_ + " instruction: " << "0b" << _instruction_ << endl;
    }
}

#endif
