#include <iostream>
#include "options.h"
#include "bus.h"

using namespace std;

int main() {
    base::BusBase _bus1(1);
    base::BusBase _bus2(2);
    base::BusBase _bus3(4);
    base::BusBase _bus4(8);
    base::BusBase _bus5(16);
    _bus1.named("Bus_1");
    _bus2.named("Bus_2");
    _bus3.named("Bus_3");
    _bus4.named("Bus_4");
    _bus5.named("Bus_5");
    unsigned long _data = 0b1110110001110011;
    _bus1.write(_data);
    _bus2.write(_data);
    _bus3.write(_data);
    _bus4.write(_data);
    _bus5.write(_data);

    cout << "input: " << "0b" << base::_bin_str(_data, 16) << endl;
    _bus1.debug();
    _bus2.debug();
    _bus3.debug();
    _bus4.debug();
    _bus5.debug();

    return 0;
}
