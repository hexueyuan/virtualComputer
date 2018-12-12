#include "selector.h"
#include "bus.h"

namespace base {
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