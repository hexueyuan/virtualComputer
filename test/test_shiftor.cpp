#include <iostream>
#include "shiftor.h"
#include "bus.h"

using namespace std;

int main() {
    base::BusBase _in_A_;
    base::BusBase _in_B_;
    base::BusBase _out_;
    base::BusBase _control_;
    unsigned long _ins_offset = 9;

    base::ShiftorBase s(&_in_A_, &_in_B_, &_out_, &_control_, _ins_offset);
    _in_A_._write(0b00010000);
    _in_B_._write(0b00000011);

    cout << "num_A:" << " 0b" << bitset<DATA_BITS_SIZE>(0b00010000) << endl;
    cout << "num_A:" << " 0b" << bitset<DATA_BITS_SIZE>(0b00000011) << endl;

    _control_._write(SHIFTOR_LEFT_SHIFT << _ins_offset);
    s();
    cout << "answer:" << " 0b" << bitset<DATA_BITS_SIZE>(_out_._read()) << endl;

    _control_._write(SHIFTOR_RIGHT_SHIFT << _ins_offset);
    s();
    cout << "answer:" << " 0b" << bitset<DATA_BITS_SIZE>(_out_._read()) << endl;

    _control_._write(SHIFTOR_NOT_ENABLE << _ins_offset);
    _out_._write(0);
    s();
    cout << "answer:" << " 0b" << bitset<DATA_BITS_SIZE>(_out_._read()) << endl;

    return 0;
}
