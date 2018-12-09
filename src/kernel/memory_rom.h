#ifndef __MEMORY_ROM_H__
#define __MEMORY_ROM_H__
#include "options.h"

namespace compute {
    class MemoryROM: public MemoryBase {
        public:
            MemoryROM(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                        base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits);
            ~MemoryROM();
        private:
            void _load_data();
    };

    MemoryROM::MemoryROM(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
            base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits) {
        _input_data_bus_ = _input_;
        _output_data_bus_ = _output_;
        _control_bus_ = _control_;
        _address_bus_ = _addr_;
        _memory_unit_bits_size_ = _unit_bsize;
        _memory_addr_bits_width_ = _addr_bits_width;
        _memory_ = new unsigned long[(unsigned long)1 << _addr_bits_width];
        _memory_active_bits_ = _mem_active_bits;

        _load_data();
    }

    void MemoryROM::_load_data() {
        unsigned long _ins_list[] = {
            (unsigned long)0b00010100000000000100000000000011,
            (unsigned long)0b00010100000000001100000000000010,
            (unsigned long)0b00100000000000001100000000000000,
            (unsigned long)0b00010000000000011100000000001000,
            (unsigned long)0b00010100000000010100000000000000,
            (unsigned long)0b01100000000000100000000000000000
        };
        int _size = 6;
        for (int i = 0; i < _size; ++i) {
            _address_bus_ -> in(i);
            _input_data_bus_ -> in(_ins_list[i]);
            _write();
        }
    }

    MemoryROM::~MemoryROM() {}
}

#endif