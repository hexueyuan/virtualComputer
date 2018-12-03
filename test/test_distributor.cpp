#include <iostream>
#include <bitset>
#include "distributor.h"
#include "bus.h"

using namespace std;

int main() {
    base::BusBase _in_;
    base::BusBase _out_A_;
    base::BusBase _out_B_;

    base::Distributor dt(&_in_, &_out_A_, &_out_B_);

    _in_._write(0b001110010000);
    dt();
    cout << bitset<DATA_BITS_SIZE>(_out_A_._read()) << endl;
    cout << bitset<DATA_BITS_SIZE>(_out_B_._read()) << endl;

    return 0;
}
