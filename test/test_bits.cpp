#include <iostream>
#include <bitset>
#include "bits.h"

using namespace std;

int main() {
    cout << "Test: " << base::_active_bits_offset(0b00001100000) << endl;
    cout << "Except: " << 5 << endl;
    cout << "Test: " << base::_active_bits_size(0b00001100000) << endl;
    cout << "Except: " << 2 << endl;
    cout << "Test: " << base::_bin_str(0b0011010, 7) << endl;
    cout << "Except: " << "0011010" << endl;
    cout << "Test: " << base::_bin_str(base::_extract_instruction(0b0101001110001100, 0b0001111110000000), 6) << endl;
    cout << "Except: " << "100111" << endl;
    return 0;
}
