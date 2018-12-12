#include <iostream>
#include "bus.h"
using std::cout;
using std::endl;

namespace base {
    BusBase::BusBase(unsigned long _width_): _bus_width_(_width_){}
    BusBase::~BusBase() {}

    void BusBase::in(unsigned long _data_) {
        _bus_data_ = _data_ & (((unsigned long)1 << _bus_width_) - 1);
    }

    unsigned long BusBase::out() {
        return _bus_data_ & (((unsigned long)1 << _bus_width_) - 1);
    }

    void BusBase::debug(string prefix) {
        cout << prefix << "Bus(" + _bus_name_ + ") data: " << base::_bin_str(_bus_data_, _bus_width_) << endl;
    }

    void BusBase::named(string _name_) {
        _bus_name_ = _name_;
    }

    unsigned long BusBase::width() {
        return _bus_width_;
    }

    string BusBase::name() {
        return _bus_name_;
    }
}