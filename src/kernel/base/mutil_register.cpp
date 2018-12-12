#include "mutil_register.h"
#include "bus.h"

namespace base {
    MutilRegisterBase::MutilRegisterBase(BusBase* _in_A_, BusBase* _in_B_, 
                                            BusBase* _out_A_, BusBase* _out_B_, 
                                            BusBase* _control_, 
                                            unsigned long _d_width, 
                                            unsigned long _ins_active_bits_) {
        _input_bus_A_ = _in_A_;
        _input_bus_B_ = _in_B_;
        _output_bus_A_ = _out_A_;
        _output_bus_B_ = _out_B_;
        _control_bus_ = _control_;
        _data_width_ = _d_width;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    MutilRegisterBase::~MutilRegisterBase() {};

    void MutilRegisterBase::operator()() {
        unsigned long _offset = base::_active_bits_offset(_instruction_active_bits_);
        unsigned long _instruction_ = (((_control_bus_ -> out()) & _instruction_active_bits_) >> _offset);

        switch (_instruction_) {
            case MUTIL_REGISTER_READ_A:
                _register_ = (_input_bus_A_ -> out()) & (((unsigned long)1 << (_data_width_)) - 1);
                break;
            case MUTIL_REGISTER_READ_B:
                _register_ = (_input_bus_B_ -> out()) & (((unsigned long)1 << (_data_width_)) - 1);
                break;
            case MUTIL_REGISTER_WRITE_A:
                _output_bus_A_ -> in(_register_);
                break;
            case MUTIL_REGISTER_WRITE_B:
                _output_bus_B_ -> in(_register_);
                break;
            case MUTIL_REGISTER_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void MutilRegisterBase::named(string _name) {
        _name_ = _name;
    }

    void MutilRegisterBase::debug(string prefix) {
        //unsigned long _offset = base::_active_bits_offset(_instruction_active_bits_);
        //unsigned long _instruction_ = (((_control_bus_ -> out()) & _instruction_active_bits_) >> _offset);
        //unsigned long _size = base::_active_bits_size(_instruction_active_bits_);
        string _space(prefix.length(), ' ');
        //cout << prefix << "Register(" + _name_ + ") instruction: " << base::_bin_str(_instruction_, _size) << endl;
        cout << _space << "Register(" + _name_ + ") value: " << base::_bin_str(_register_, _data_width_) << endl;
        //cout << _space << "Register(" + _name_ + ") instruction_offset: " << _instruction_active_bits_ << endl;
        //cout << _space << "Register(" + _name_ + ") data_width: " << _data_width_ << endl;
        //cout << _space << "Register(" + _name_ + ") control_bus: " << _control_bus_ -> name() << endl;
        //cout << _space << "Register(" + _name_ + ") input_bus_A: " << _input_bus_A_ -> name() << endl;
        //cout << _space << "Register(" + _name_ + ") input_bus_B: " << _input_bus_B_ -> name() << endl;
        //cout << _space << "Register(" + _name_ + ") output_bus_A: " << _output_bus_A_ -> name() << endl;
        //cout << prefix << "Register(" + _name_ + ") output_bus_B: " << _output_bus_B_ -> name() << endl;
    }

    string MutilRegisterBase::name() {
        return _name_;
    }
}