#include "alu.h"

namespace base {
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
        _output_bus_A_ -> in(_input_bus_A_ -> out() + _input_bus_B_ -> out());
    }

    void AluBase::_LOGIC_AND() {
        _output_bus_A_ -> in(_input_bus_A_ -> out() & _input_bus_B_ -> out());
    }

    void AluBase::_LOGIC_OR() {
        _output_bus_A_ -> in(_input_bus_A_ -> out() | _input_bus_B_ -> out());
    }

    void AluBase::_LOGIC_NOT() {
        _output_bus_A_ -> in(~(_input_bus_A_ -> out()));
    }

    void AluBase::_DIRECT_TRANSMISSION() {
        _output_bus_A_ -> in(_input_bus_A_ -> out());
        _output_bus_B_ -> in(_input_bus_B_ -> out());
    }

    void AluBase::_LOGIC_XOR() {
        _output_bus_A_ -> in(_input_bus_A_ -> out() ^ _input_bus_B_ -> out());
    }
}