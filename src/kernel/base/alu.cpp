#include "alu.h"

namespace base {
    AluBase::AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                    BusBase* _control_, unsigned long _d_width, unsigned long _ins_active_bits_) {
        _input_bus_A_ = _in_A_;
        _input_bus_B_ = _in_B_;
        _output_bus_A_ = _out_A_;
        _output_bus_B_ = _out_B_;
        _control_bus_ = _control_;
        _data_wdith = _d_width;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    AluBase::~AluBase() {}

    void AluBase::operator()() {
        _instruction_ = _extract_instruction(_control_bus_ -> out(), _instruction_active_bits_);

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
            case ALU_LOGIC_XOR:
                _LOGIC_XOR();
                break;
            default:
                break;
        }
    }

    void AluBase::named(string _name_) {
        _alu_name_ = _name_;
    }

    void AluBase::debug(string prefix) {
        string space(prefix.length(), ' '); 
        cout << prefix << "ALU(" << _alu_name_ << ") instruction: " << 
            _bin_str(_instruction_, _active_bits_size(_instruction_active_bits_)) << endl;
        cout << space << "ALU(" << _alu_name_ << ") input_bus_A: " << _input_bus_A_ -> name() << endl;
        cout << space << "ALU(" << _alu_name_ << ") input_bus_B: " << _input_bus_B_ -> name() << endl;
        cout << space << "ALU(" << _alu_name_ << ") output_bus_A: " << _output_bus_A_ -> name() << endl;
        cout << space << "ALU(" << _alu_name_ << ") output_bus_B: " << _output_bus_B_ -> name() << endl;
        cout << prefix << "ALU(" << _alu_name_ << ") control_bus: " << _control_bus_ -> name() << endl;
    }

    void AluBase::_ARITHMETIC_ADD() {
        unsigned long _eff_bits = base::_effective_bits(_data_wdith);
        unsigned long _data_A = (_input_bus_A_ -> out() & _eff_bits);
        unsigned long _data_B = (_input_bus_B_ -> out() & _eff_bits);
        _output_bus_A_ -> in((_data_A + _data_B) & _eff_bits);
    }

    void AluBase::_LOGIC_AND() {
        unsigned long _eff_bits = base::_effective_bits(_data_wdith);
        unsigned long _data_A = (_input_bus_A_ -> out() & _eff_bits);
        unsigned long _data_B = (_input_bus_B_ -> out() & _eff_bits);
        _output_bus_A_ -> in((_data_A & _data_B) & _eff_bits);
    }

    void AluBase::_LOGIC_OR() {
        unsigned long _eff_bits = base::_effective_bits(_data_wdith);
        unsigned long _data_A = (_input_bus_A_ -> out() & _eff_bits);
        unsigned long _data_B = (_input_bus_B_ -> out() & _eff_bits);
        _output_bus_A_ -> in((_data_A | _data_B) & _eff_bits);
    }

    void AluBase::_LOGIC_NOT() {
        unsigned long _eff_bits = base::_effective_bits(_data_wdith);
        unsigned long _data_A = (_input_bus_A_ -> out() & _eff_bits);
        _output_bus_A_ -> in((~_data_A) & _eff_bits);
    }

    void AluBase::_DIRECT_TRANSMISSION() {
        unsigned long _eff_bits = base::_effective_bits(_data_wdith);
        _output_bus_A_ -> in(_input_bus_A_ -> out() & _eff_bits);
        _output_bus_B_ -> in(_input_bus_B_ -> out() & _eff_bits);
    }

    void AluBase::_LOGIC_XOR() {
        unsigned long _eff_bits = base::_effective_bits(_data_wdith);
        unsigned long _data_A = (_input_bus_A_ -> out() & _eff_bits);
        unsigned long _data_B = (_input_bus_B_ -> out() & _eff_bits);
        _output_bus_A_ -> in((_data_A ^ _data_B) & _eff_bits);
    }
}