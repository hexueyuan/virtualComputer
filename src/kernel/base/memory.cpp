#include "memory.h"
#include "bus.h"

namespace base {
    MemoryBase::MemoryBase() {};
    MemoryBase::MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                            base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits) {
        _input_data_bus_ = _input_;
        _output_data_bus_ = _output_;
        _control_bus_ = _control_;
        _address_bus_ = _addr_;
        _memory_unit_bits_size_ = _unit_bsize;
        _memory_addr_bits_width_ = _addr_bits_width;
        _memory_ = new unsigned long[(unsigned long)1 << _addr_bits_width];
        _memory_active_bits_ = _mem_active_bits;
    }

    MemoryBase::~MemoryBase() {}

    void MemoryBase::operator()() {
        unsigned long _instruction_ = base::_extract_instruction(_control_bus_ -> out(), _memory_active_bits_);

        switch (_instruction_) {
            case MEMORY_READ:
                write_in(_address_bus_ -> out(), _input_data_bus_ -> out());
                break;
            case MEMORY_WRITE:
                _output_data_bus_ -> in(read_from(_address_bus_ -> out()));
                break;
            case MEMORY_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void MemoryBase::named(string _name) {
        _name_ = _name;
    }

    void MemoryBase::debug(unsigned long _addr, string prefix) {
        if (_addr > (((unsigned long)1 << _memory_addr_bits_width_) - 1)) {
            return;
        }
        cout << prefix << base::_bin_str(_addr, _memory_addr_bits_width_) << ": " << base::_bin_str(_memory_[_addr], _memory_unit_bits_size_) << endl;
    }
   
   void MemoryBase::write_in(unsigned long addr, unsigned long data) {
        unsigned long _eff_addr_bits = base::_effective_bits(_memory_addr_bits_width_);
        unsigned long _eff_unit_bits = base::_effective_bits(_memory_unit_bits_size_);

       _memory_[addr & _eff_addr_bits] = data & _eff_unit_bits;
   }

   unsigned long MemoryBase::read_from(unsigned long addr) {
        unsigned long _eff_addr_bits = base::_effective_bits(_memory_addr_bits_width_);
        unsigned long _eff_unit_bits = base::_effective_bits(_memory_unit_bits_size_);
        return _memory_[addr & _eff_addr_bits] & _eff_unit_bits;
   }
}