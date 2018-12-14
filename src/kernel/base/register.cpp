#include "register.h"
#include "bus.h"
#include "bits.h"

namespace base {
    RegisterBase::RegisterBase(BusBase* _in_, BusBase* _out_, BusBase* _control_, 
                            unsigned long _d_width, unsigned long _ins_active_bits_) {
        _input_bus_ = _in_;
        _output_bus_ = _out_;
        _control_bus_ = _control_;
        _data_width_ = _d_width;
        _instruction_active_bits_ = _ins_active_bits_;
        _register_ = 0;
    }

    RegisterBase::~RegisterBase() {};

    void RegisterBase::operator()() {
        unsigned long _offset = base::_active_bits_offset(_instruction_active_bits_);
        unsigned long _instruction_ = (((_control_bus_ -> out()) & _instruction_active_bits_) >> _offset);

        switch (_instruction_) {
            case REGISTER_READ:
                _register_ = (_input_bus_ -> out() & base::_effective_bits(_data_width_));
                break;
            case REGISTER_WRITE:
                _output_bus_ -> in(_register_ & base::_effective_bits(_data_width_));
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

    void RegisterBase::debug(string prefix) {
        cout << prefix << "Register(" + _name_ + ") value: " << base::_bin_str(_register_, _data_width_) << endl;
    }

    string RegisterBase::name() {
        return _name_;
    }
}