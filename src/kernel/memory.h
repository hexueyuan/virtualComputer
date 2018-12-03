#include "base/bus.h"
#include "base/options.h"

#define MEMORY_INSTRUCTION_BITS_SIZE 2
#define MEMORY_READ 0b10
#define MEMORY_WRITE 0b11
#define MEMORY_NOT_ENABLE 0b00
#define MEMORY_CONTAIN 0b01

namespace compute {
    class MemoryBase {
        public:
            MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                        base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _space_size);
            ~MemoryBase();

            void operator()();

        private:
            base::BusBase* _input_data_bus_;
            base::BusBase* _output_data_bus_;
            base::BusBase* _address_bus_;
            base::BusBase* _control_bus_;
            unsigned long _instruction_;

            unsigned long _memory_unit_bits_size_;
            unsigned long _memory_space_size_;
            unsigned long* _memory_;

            void _write(unsigned long _addr);
            void _read(unsigned long _addr);
    };

    MemoryBase::MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                            base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _space_size) {
        _input_data_bus_ = _input_;
        _output_data_bus_ = _output_;
        _control_bus_ = _control_;
        _address_bus_ = _addr_;
        _memory_unit_bits_size_ = _unit_bsize;
        _memory_space_size_ = _space_size;
        _memory_ = new unsigned long[_space_size];
    }

    MemoryBase::~MemoryBase() {}

    void MemoryBase::_write() {
        if (_address_bus_ -> _read() < _memory_space_size_) {
            _memory_[_address_bus_ -> _read()] = (_input_data_bus -> _read()) & ((1 << _memory_unit_bits_size_) - 1);
        }
    }

    void MemoryBase::_read() {
        if (_address_bus_ -> _read() < _memory_space_size_) {
            _output_data_bus_ -> _write(_memory_[_address_bus_ -> _read()]);
        }
    }

    void MemoryBase::operator()() {
        _instruction_ = _control_bus_ -> _read();

        switch (_instruction_) {
            case MEMORY_READ:
                _read();
                break;
            case MEMORY_WRITE:
                _write();
                break;
            case MEMORY_NOT_ENABLE:
                break;
            default:
                break;
        }
    }
}
