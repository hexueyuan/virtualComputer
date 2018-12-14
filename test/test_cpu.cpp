#include <gtest/gtest.h>
#include "cpu.h"

unsigned long _ins_nop = 0b0000000000000;

class TestCPU8bits:public testing::Test {
    public:
        base::BusBase* _in_R0_; 
        base::BusBase* _in_R1_; 
        base::BusBase* _in_R2_; 
        base::BusBase* _in_R3_;
        base::BusBase* _in_IP_;
        base::BusBase* _in_PC_; 
        base::BusBase* _in_C_; 
        base::BusBase* _in_D_;
        base::BusBase* _in_MAR_; 
        base::BusBase* _in_MDR_; 
        base::BusBase* _in_PSW_; 
        base::BusBase* _in_SP_;
        base::BusBase* _out_; 
        base::BusBase* _control_;
        unsigned long _selector_A_active_bits;
        unsigned long _selector_B_active_bits;
        unsigned long _alu_active_bits;
        unsigned long _shiftor_active_bits;
        unsigned long _data_bits_width;
        unsigned long _ins_active_bits;

        computer::CPU* _CPU_;

        virtual void SetUp() {
            _selector_A_active_bits =   0b1111000000000;
            _selector_B_active_bits =   0b0000111100000;
            _alu_active_bits =          0b0000000011100;
            _shiftor_active_bits =      0b0000000000011;
            _ins_active_bits =          0b1111111111111;
            _data_bits_width = 8;
            _in_R0_ = new base::BusBase(_data_bits_width);
            _in_R1_ = new base::BusBase(_data_bits_width);
            _in_R2_ = new base::BusBase(_data_bits_width);
            _in_R3_ = new base::BusBase(_data_bits_width);
            _in_IP_ = new base::BusBase(_data_bits_width);
            _in_PC_ = new base::BusBase(_data_bits_width);
            _in_C_ = new base::BusBase(_data_bits_width);
            _in_D_ = new base::BusBase(_data_bits_width);
            _in_MAR_ = new base::BusBase(_data_bits_width);
            _in_MDR_ = new base::BusBase(_data_bits_width);
            _in_PSW_ = new base::BusBase(_data_bits_width);
            _in_SP_ = new base::BusBase(_data_bits_width);
            _out_ = new base::BusBase(_data_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _CPU_ = new computer::CPU(_in_R0_, _in_R1_, _in_R2_, _in_R3_, _in_IP_, _in_PC_,
                                    _in_C_, _in_D_, _in_MAR_, _in_MDR_, _in_PSW_, _in_SP_, 
                                    _out_, _control_, 
                                    _selector_A_active_bits, _selector_B_active_bits,
                                    _alu_active_bits, _shiftor_active_bits,
                                    _data_bits_width);
        }

        virtual void TearDown() {
            delete _in_R0_; 
            delete _in_R1_; 
            delete _in_R2_; 
            delete _in_R3_;
            delete _in_IP_;
            delete _in_PC_; 
            delete _in_C_; 
            delete _in_D_;
            delete _in_MAR_; 
            delete _in_MDR_; 
            delete _in_PSW_; 
            delete _in_SP_;
            delete _out_; 
            delete _control_;
            delete _CPU_;
        }
};

TEST_F(TestCPU8bits, Test_ADD) {
    unsigned long _data1_A = 6;
    unsigned long _data1_B = 13;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA + selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A + _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU8bits, Test_AND) {
    unsigned long _data1_A = 33;
    unsigned long _data1_B = 23;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA & selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A & _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU8bits, Test_OR) {
    unsigned long _data1_A =33;
    unsigned long _data1_B = 56;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA | selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A | _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU8bits, Test_NOT) {
    unsigned long _data1_A = 255;
    unsigned long _data1_B = 13;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //~selectorA -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (~_data1_A) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU8bits, Test_XOR) {
    unsigned long _data1_A = 59;
    unsigned long _data1_B = 28;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA ^ selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A ^ _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU8bits, Test_LEFT_SHIFTOR) {
    unsigned long _data1_A = 0b00010000;
    unsigned long _data1_B = 2;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A << _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU8bits, Test_RIGHT_SHIFTOR) {
    unsigned long _data1_A = 0b00010000;
    unsigned long _data1_B = 2;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A >> _data1_B) & base::_effective_bits(_data_bits_width));
}

class TestCPU16bits:public testing::Test {
    public:
        base::BusBase* _in_R0_; 
        base::BusBase* _in_R1_; 
        base::BusBase* _in_R2_; 
        base::BusBase* _in_R3_;
        base::BusBase* _in_IP_;
        base::BusBase* _in_PC_; 
        base::BusBase* _in_C_; 
        base::BusBase* _in_D_;
        base::BusBase* _in_MAR_; 
        base::BusBase* _in_MDR_; 
        base::BusBase* _in_PSW_; 
        base::BusBase* _in_SP_;
        base::BusBase* _out_; 
        base::BusBase* _control_;
        unsigned long _selector_A_active_bits;
        unsigned long _selector_B_active_bits;
        unsigned long _alu_active_bits;
        unsigned long _shiftor_active_bits;
        unsigned long _data_bits_width;
        unsigned long _ins_active_bits;

        computer::CPU* _CPU_;

        virtual void SetUp() {
            _selector_A_active_bits =   0b1111000000000;
            _selector_B_active_bits =   0b0000111100000;
            _alu_active_bits =          0b0000000011100;
            _shiftor_active_bits =      0b0000000000011;
            _ins_active_bits =          0b1111111111111;
            _data_bits_width = 16;
            _in_R0_ = new base::BusBase(_data_bits_width);
            _in_R1_ = new base::BusBase(_data_bits_width);
            _in_R2_ = new base::BusBase(_data_bits_width);
            _in_R3_ = new base::BusBase(_data_bits_width);
            _in_IP_ = new base::BusBase(_data_bits_width);
            _in_PC_ = new base::BusBase(_data_bits_width);
            _in_C_ = new base::BusBase(_data_bits_width);
            _in_D_ = new base::BusBase(_data_bits_width);
            _in_MAR_ = new base::BusBase(_data_bits_width);
            _in_MDR_ = new base::BusBase(_data_bits_width);
            _in_PSW_ = new base::BusBase(_data_bits_width);
            _in_SP_ = new base::BusBase(_data_bits_width);
            _out_ = new base::BusBase(_data_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _CPU_ = new computer::CPU(_in_R0_, _in_R1_, _in_R2_, _in_R3_, _in_IP_, _in_PC_,
                                    _in_C_, _in_D_, _in_MAR_, _in_MDR_, _in_PSW_, _in_SP_, 
                                    _out_, _control_, 
                                    _selector_A_active_bits, _selector_B_active_bits,
                                    _alu_active_bits, _shiftor_active_bits,
                                    _data_bits_width);
        }

        virtual void TearDown() {
            delete _in_R0_; 
            delete _in_R1_; 
            delete _in_R2_; 
            delete _in_R3_;
            delete _in_IP_;
            delete _in_PC_; 
            delete _in_C_; 
            delete _in_D_;
            delete _in_MAR_; 
            delete _in_MDR_; 
            delete _in_PSW_; 
            delete _in_SP_;
            delete _out_; 
            delete _control_;
            delete _CPU_;
        }
};

TEST_F(TestCPU16bits, Test_ADD) {
    unsigned long _data1_A = 233;
    unsigned long _data1_B = 876;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA + selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A + _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU16bits, Test_AND) {
    unsigned long _data1_A = 673;
    unsigned long _data1_B = 22342;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA & selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A & _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU16bits, Test_OR) {
    unsigned long _data1_A =2321;
    unsigned long _data1_B = 22333;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA | selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A | _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU16bits, Test_NOT) {
    unsigned long _data1_A = 983;
    unsigned long _data1_B = 22;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //~selectorA -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (~_data1_A) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU16bits, Test_XOR) {
    unsigned long _data1_A = 2211;
    unsigned long _data1_B = 78;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA ^ selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A ^ _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU16bits, Test_LEFT_SHIFTOR) {
    unsigned long _data1_A = 0b0000000100000000;
    unsigned long _data1_B = 2;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A << _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU16bits, Test_RIGHT_SHIFTOR) {
    unsigned long _data1_A = 0b0000000100000000;
    unsigned long _data1_B = 2;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A >> _data1_B) & base::_effective_bits(_data_bits_width));
}

class TestCPU32bits:public testing::Test {
    public:
        base::BusBase* _in_R0_; 
        base::BusBase* _in_R1_; 
        base::BusBase* _in_R2_; 
        base::BusBase* _in_R3_;
        base::BusBase* _in_IP_;
        base::BusBase* _in_PC_; 
        base::BusBase* _in_C_; 
        base::BusBase* _in_D_;
        base::BusBase* _in_MAR_; 
        base::BusBase* _in_MDR_; 
        base::BusBase* _in_PSW_; 
        base::BusBase* _in_SP_;
        base::BusBase* _out_; 
        base::BusBase* _control_;
        unsigned long _selector_A_active_bits;
        unsigned long _selector_B_active_bits;
        unsigned long _alu_active_bits;
        unsigned long _shiftor_active_bits;
        unsigned long _data_bits_width;
        unsigned long _ins_active_bits;

        computer::CPU* _CPU_;

        virtual void SetUp() {
            _selector_A_active_bits =   0b1111000000000;
            _selector_B_active_bits =   0b0000111100000;
            _alu_active_bits =          0b0000000011100;
            _shiftor_active_bits =      0b0000000000011;
            _ins_active_bits =          0b1111111111111;
            _data_bits_width = 32;
            _in_R0_ = new base::BusBase(_data_bits_width);
            _in_R1_ = new base::BusBase(_data_bits_width);
            _in_R2_ = new base::BusBase(_data_bits_width);
            _in_R3_ = new base::BusBase(_data_bits_width);
            _in_IP_ = new base::BusBase(_data_bits_width);
            _in_PC_ = new base::BusBase(_data_bits_width);
            _in_C_ = new base::BusBase(_data_bits_width);
            _in_D_ = new base::BusBase(_data_bits_width);
            _in_MAR_ = new base::BusBase(_data_bits_width);
            _in_MDR_ = new base::BusBase(_data_bits_width);
            _in_PSW_ = new base::BusBase(_data_bits_width);
            _in_SP_ = new base::BusBase(_data_bits_width);
            _out_ = new base::BusBase(_data_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _CPU_ = new computer::CPU(_in_R0_, _in_R1_, _in_R2_, _in_R3_, _in_IP_, _in_PC_,
                                    _in_C_, _in_D_, _in_MAR_, _in_MDR_, _in_PSW_, _in_SP_, 
                                    _out_, _control_, 
                                    _selector_A_active_bits, _selector_B_active_bits,
                                    _alu_active_bits, _shiftor_active_bits,
                                    _data_bits_width);
        }

        virtual void TearDown() {
            delete _in_R0_; 
            delete _in_R1_; 
            delete _in_R2_; 
            delete _in_R3_;
            delete _in_IP_;
            delete _in_PC_; 
            delete _in_C_; 
            delete _in_D_;
            delete _in_MAR_; 
            delete _in_MDR_; 
            delete _in_PSW_; 
            delete _in_SP_;
            delete _out_; 
            delete _control_;
            delete _CPU_;
        }
};

TEST_F(TestCPU32bits, Test_ADD) {
    unsigned long _data1_A = 2316;
    unsigned long _data1_B = 13123;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA + selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A + _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU32bits, Test_AND) {
    unsigned long _data1_A = 3321;
    unsigned long _data1_B = 23321;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA & selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A & _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU32bits, Test_OR) {
    unsigned long _data1_A = (unsigned long)784;
    unsigned long _data1_B = (unsigned long)2311;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA | selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A | _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU32bits, Test_NOT) {
    unsigned long _data1_A = (unsigned long)12311;
    unsigned long _data1_B = (unsigned long)231;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //~selectorA -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (~_data1_A) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU32bits, Test_XOR) {
    unsigned long _data1_A = (unsigned long)7812;
    unsigned long _data1_B = (unsigned long)23434;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA ^ selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A ^ _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU32bits, Test_LEFT_SHIFTOR) {
    unsigned long _data1_A = 0b00000000000000001000000000000000;
    unsigned long _data1_B = 16;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A << _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU32bits, Test_RIGHT_SHIFTOR) {
    unsigned long _data1_A = 0b00000000000000001000000000000000;
    unsigned long _data1_B = 15;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A >> _data1_B) & base::_effective_bits(_data_bits_width));
}

class TestCPU64bits:public testing::Test {
    public:
        base::BusBase* _in_R0_; 
        base::BusBase* _in_R1_; 
        base::BusBase* _in_R2_; 
        base::BusBase* _in_R3_;
        base::BusBase* _in_IP_;
        base::BusBase* _in_PC_; 
        base::BusBase* _in_C_; 
        base::BusBase* _in_D_;
        base::BusBase* _in_MAR_; 
        base::BusBase* _in_MDR_; 
        base::BusBase* _in_PSW_; 
        base::BusBase* _in_SP_;
        base::BusBase* _out_; 
        base::BusBase* _control_;
        unsigned long _selector_A_active_bits;
        unsigned long _selector_B_active_bits;
        unsigned long _alu_active_bits;
        unsigned long _shiftor_active_bits;
        unsigned long _data_bits_width;
        unsigned long _ins_active_bits;

        computer::CPU* _CPU_;

        virtual void SetUp() {
            _selector_A_active_bits =   0b1111000000000;
            _selector_B_active_bits =   0b0000111100000;
            _alu_active_bits =          0b0000000011100;
            _shiftor_active_bits =      0b0000000000011;
            _ins_active_bits =          0b1111111111111;
            _data_bits_width = 64;
            _in_R0_ = new base::BusBase(_data_bits_width);
            _in_R1_ = new base::BusBase(_data_bits_width);
            _in_R2_ = new base::BusBase(_data_bits_width);
            _in_R3_ = new base::BusBase(_data_bits_width);
            _in_IP_ = new base::BusBase(_data_bits_width);
            _in_PC_ = new base::BusBase(_data_bits_width);
            _in_C_ = new base::BusBase(_data_bits_width);
            _in_D_ = new base::BusBase(_data_bits_width);
            _in_MAR_ = new base::BusBase(_data_bits_width);
            _in_MDR_ = new base::BusBase(_data_bits_width);
            _in_PSW_ = new base::BusBase(_data_bits_width);
            _in_SP_ = new base::BusBase(_data_bits_width);
            _out_ = new base::BusBase(_data_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _CPU_ = new computer::CPU(_in_R0_, _in_R1_, _in_R2_, _in_R3_, _in_IP_, _in_PC_,
                                    _in_C_, _in_D_, _in_MAR_, _in_MDR_, _in_PSW_, _in_SP_, 
                                    _out_, _control_, 
                                    _selector_A_active_bits, _selector_B_active_bits,
                                    _alu_active_bits, _shiftor_active_bits,
                                    _data_bits_width);
        }

        virtual void TearDown() {
            delete _in_R0_; 
            delete _in_R1_; 
            delete _in_R2_; 
            delete _in_R3_;
            delete _in_IP_;
            delete _in_PC_; 
            delete _in_C_; 
            delete _in_D_;
            delete _in_MAR_; 
            delete _in_MDR_; 
            delete _in_PSW_; 
            delete _in_SP_;
            delete _out_; 
            delete _control_;
            delete _CPU_;
        }
};

TEST_F(TestCPU64bits, Test_ADD) {
    unsigned long _data1_A = 0b1000000010000000000000100001000010000000000000000000000000000001;
    unsigned long _data1_B = 0b0100010000100000100000010000000010000000100000010000001000001000;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA + selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A + _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU64bits, Test_AND) {
    unsigned long _data1_A = 0b1000000010000000000000100001000010000000000000000000000000000001;
    unsigned long _data1_B = 0b0100010000100000100000010000000010000000100000010000001000001000;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA & selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A & _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU64bits, Test_OR) {
    unsigned long _data1_A = 0b1000000010000000000000100001000010000000000000000000000000000001;
    unsigned long _data1_B = 0b0100010000100000100000010000000010000000100000010000001000001000;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA | selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A | _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU64bits, Test_NOT) {
    unsigned long _data1_A = 0b1000000010000000000000100001000010000000000000000000000000000001;
    unsigned long _data1_B = 0b0100010000100000100000010000000010000000100000010000001000001000;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //~selectorA -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (~_data1_A) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU64bits, Test_XOR) {
    unsigned long _data1_A = 0b1000000010000000000000100001000010000000000000000000000000000001;
    unsigned long _data1_B = 0b0100010000100000100000010000000010000000100000010000001000001000;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA ^ selectorB -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //shiftor direct transform to out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A ^ _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU64bits, Test_LEFT_SHIFTOR) {
    unsigned long _data1_A = 0b0000000000000000000000000000000010000000000000000000000000000000;
    unsigned long _data1_B = 32;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A << _data1_B) & base::_effective_bits(_data_bits_width));
}

TEST_F(TestCPU64bits, Test_RIGHT_SHIFTOR) {
    unsigned long _data1_A = 0b0000000000000000000000000000000010000000000000000000000000000000;
    unsigned long _data1_B = 31;
    _in_R0_ -> in(_data1_A);
    _in_R1_ -> in(_data1_B);
    //R0 -> selectorA
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _selector_A_active_bits) | _ins_nop);
    (*_CPU_)();
    //R1 -> selectorB
    _control_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _selector_B_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA , selectorB direct transform -> shiftor
    _control_ -> in(base::_generate_instruction(ALU_DIRECT_TRANSMISSION, _alu_active_bits) | _ins_nop);
    (*_CPU_)();
    //selectorA << selectorB -> out bus
    _control_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _shiftor_active_bits) | _ins_nop);
    (*_CPU_)();

    EXPECT_EQ(_out_ -> out(), (_data1_A >> _data1_B) & base::_effective_bits(_data_bits_width));
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}