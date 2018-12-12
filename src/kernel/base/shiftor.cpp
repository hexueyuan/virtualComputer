#include "shiftor.h"
#include "bus.h"

namespace base {
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
        _instruction_ = _extract_instruction(_control_bus_ -> out(), _instruction_active_bits_);

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
        _output_bus_ -> in((_input_bus_A_ -> out()) << (_input_bus_B_ -> out()));
    }

    void ShiftorBase::_right_shift() {
        _output_bus_ -> in((_input_bus_A_ -> out()) >> (_input_bus_B_ -> out()));
    }

    void ShiftorBase::_direct_transmission() {
        _output_bus_ -> in(_input_bus_A_ -> out());
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