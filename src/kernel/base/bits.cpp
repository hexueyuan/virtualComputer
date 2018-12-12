#include "bits.h"

namespace base {
    unsigned long _active_bits_offset(unsigned long _active_bits) {
        if (_active_bits == 0) {
            return sizeof(unsigned long);
        }
        unsigned long _cnt = 0;
        while (!((_active_bits >> _cnt) & 0b1)) ++_cnt;
        return _cnt;
    }

    unsigned long _active_bits_size(unsigned long _active_bits) {
        if (_active_bits == 0) {
            return 0;
        }
        unsigned long _cnt = 0;
        _active_bits = _active_bits >> _active_bits_offset(_active_bits);
        while ((_active_bits >> _cnt) & 0b1) ++_cnt;
        return _cnt;
    }

    unsigned long _extract_instruction(unsigned long _global_ins, unsigned long _active_bits) {
        return (_global_ins & _active_bits) >> _active_bits_offset(_active_bits);
    }

    unsigned long _generate_instruction(unsigned long _ins, unsigned long _active_bits) {
        return (_ins << _active_bits_offset(_active_bits)) & _active_bits;
    }

    string _bin_str(unsigned long _num, unsigned long bits) {
        string _str = "";
        for (int i = bits - 1; i >= 0; --i) {
            _str += (char)(((_num >> i) & 0b1) + '0');
        }
        return _str;
    }

    unsigned long _str_bin(string _str) {
        unsigned long _num = 0;
        int _size = (_str.length() < 64)?_str.length():64;

        for (int i = 0; i < _size; ++i) {
            if (_str[i] != '0' && _str[i] != '1') {
                return 0;
            }
            _num = (_num << 1) + (_str[i] - '0');
        }
        return _num;
    }
}