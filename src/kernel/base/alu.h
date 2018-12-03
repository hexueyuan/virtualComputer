#include "selector.h"

#include "options.h"
#include "bits.h"

#ifndef __ALU_H__
#define __ALU_H__

namespace base {

    class AluBase {
        public:
            AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                    BusBase* _control_, unsigned long _ins_active_bits_);
            ~AluBase();

            void operator()();
            void _debug();
            void _named(string _name_);

        private:
            BusBase* _input_bus_A_;
            BusBase* _input_bus_B_;
            BusBase* _output_bus_A_;
            BusBase* _output_bus_B_;
            BusBase* _control_bus_;

            unsigned long _instruction_;
            unsigned long _instruction_active_bits_;
            string _alu_name_;

            void _ARITHMETIC_ADD();
            void _LOGIC_AND();
            void _LOGIC_OR();
            void _LOGIC_NOT();
            void _DIRECT_TRANSMISSION();
    };

    AluBase::AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                                                BusBase* _control_, unsigned long _ins_active_bits_) {
        _input_bus_A_ = _in_A_;
        _input_bus_B_ = _in_B_;
        _output_bus_A_ = _out_A_;
        _output_bus_B_ = _out_B_;
        _control_bus_ = _control_;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    AluBase::~AluBase() {}

    void AluBase::operator()() {
        _instruction_ = _extract_instruction(_control_bus_ -> read(), _instruction_active_bits_);

        switch(_instruction_) {
            case ALU_ARITHMETIC_ADD:
                _ARITHMETIC_ADD();
                break;
            case ALU_LOGIC_AND:
                _LOGIC_AND();
                break;
            case ALU_LOGIC_OR:
                _LOGIC_OR();
                break;
            case ALU_LOGIC_NOT:
                _LOGIC_NOT();
                break;
            case ALU_DIRECT_TRANSMISSION:
                _DIRECT_TRANSMISSION();
                break;
            case ALU_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void AluBase::_named(string _name_) {
        _alu_name_ = _name_;
    }

    void AluBase::_debug() {
        cout << "ALU " + _alu_name_ + " instruction: " << 
            _bin_str(_instruction_, _active_bits_size(_instruction_active_bits_)) << endl;
    }

    void AluBase::_ARITHMETIC_ADD() {
        _output_bus_A_ -> write(_input_bus_A_ -> read() + _input_bus_B_ -> read());
    }

    void AluBase::_LOGIC_AND() {
        _output_bus_A_ -> write(_input_bus_A_ -> read() & _input_bus_B_ -> read());
    }

    void AluBase::_LOGIC_OR() {
        _output_bus_A_ -> write(_input_bus_A_ -> read() | _input_bus_B_ -> read());
    }

    void AluBase::_LOGIC_NOT() {
        _output_bus_A_ -> write(~(_input_bus_A_ -> read()));
    }

    void AluBase::_DIRECT_TRANSMISSION() {
        _output_bus_A_ -> write(_input_bus_A_ -> read());
        _output_bus_B_ -> write(_input_bus_B_ -> read());
    }
}

#endif
