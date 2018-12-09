#include <iostream>
#include "instruction_generator.h"
#include "base/bits.h"

using namespace std;

int main() {
    compute::InstructionGeneratorBase ig;

    ig();
    ig.debug();
    cout << "------------------------" << endl;

    ig();
    ig.debug();
    cout << "------------------------" << endl;

    ig();
    ig.debug();
    cout << "------------------------" << endl;

    ig();
    ig.debug();
    cout << "------------------------" << endl;

    ig();
    ig.debug();
    cout << "------------------------" << endl;

    ig();
    ig.debug();
    cout << "------------------------" << endl;

    return 0;
}
