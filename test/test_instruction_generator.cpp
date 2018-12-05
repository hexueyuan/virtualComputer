#include <iostream>
#include "instruction_generator.h"
#include "base/bits.h"

using namespace std;

int main() {
    compute::InstructionGeneratorBase ig;

    //MOV 3 R0
    unsigned long ins1 = (base::_generate_instruction(INSTRUCTION_MOV, INSTRUCTION_TYPE) |
                        base::_generate_instruction(ADDRESS_NUMBER, OPERATE_NUMBER_1_ADDRESS_METHOD) |
                        base::_generate_instruction(3, OPERATE_NUMBER_1) |
                        base::_generate_instruction(ADDRESS_REGISTER, OPERATE_NUMBER_2_ADDRESS_METHOD) |
                        base::_generate_instruction(REGISTER_0, OPERATE_NUMBER_2));
    //ig.debug();
    cout << "=============================" << endl;
    ig(ins1);
    ig.debug();

    return 0;
}