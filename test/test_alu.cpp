#include <gtest/gtest.h>
#include <string>
#include "alu.h"

using std::string;

class TestAlu8bits:public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::AluBase* _alu_;
        unsigned long _data_width;
        unsigned long _active_bits;
        
        virtual void SetUp() {
            _data_width = 8;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _active_bits = 0b111;
            _control_ = new base::BusBase(base::_active_bits_size(_active_bits));
            _alu_ = new base::AluBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, _active_bits);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _alu_;
            _in_A_ = NULL;
            _in_B_ = NULL;
            _out_A_ = NULL;
            _out_B_ = NULL;
            _control_ = NULL;
            _alu_ = NULL;
        }
};

TEST_F(TestAlu8bits, test_ADD) {
    unsigned long _data1_A = 0b10101010;
    unsigned long _data1_B = 0b01010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A + _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu8bits, test_AND) {
    unsigned long _data1_A = 0b10101010;
    unsigned long _data1_B = 0b01010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A & _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu8bits, test_OR) {
    unsigned long _data1_A = 0b10101010;
    unsigned long _data1_B = 0b01010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A | _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu8bits, test_NOT) {
    unsigned long _data1_A = 0b10101010;
    unsigned long _data1_B = 0b01010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _active_bits));
    (*_alu_)();

    EXPECT_EQ((~_data1_A) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu8bits, test_XOR) {
    unsigned long _data1_A = 0b10101010;
    unsigned long _data1_B = 0b01010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A ^ _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

class TestAlu16bits:public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::AluBase* _alu_;
        unsigned long _data_width;
        unsigned long _active_bits;
        
        virtual void SetUp() {
            _data_width = 16;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _active_bits = 0b111;
            _control_ = new base::BusBase(base::_active_bits_size(_active_bits));
            _alu_ = new base::AluBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, _active_bits);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _alu_;
            _in_A_ = NULL;
            _in_B_ = NULL;
            _out_A_ = NULL;
            _out_B_ = NULL;
            _control_ = NULL;
            _alu_ = NULL;
        }
};

TEST_F(TestAlu16bits, test_ADD) {
    unsigned long _data1_A = 0b1010101010101010;
    unsigned long _data1_B = 0b0101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A + _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu16bits, test_AND) {
    unsigned long _data1_A = 0b1010101010101010;
    unsigned long _data1_B = 0b0101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A & _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu16bits, test_OR) {
    unsigned long _data1_A = 0b1010101010101010;
    unsigned long _data1_B = 0b0101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A | _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu16bits, test_NOT) {
    unsigned long _data1_A = 0b1010101010101010;
    unsigned long _data1_B = 0b0101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _active_bits));
    (*_alu_)();

    EXPECT_EQ((~_data1_A) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu16bits, test_XOR) {
    unsigned long _data1_A = 0b1010101010101010;
    unsigned long _data1_B = 0b0101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A ^ _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

class TestAlu32bits:public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::AluBase* _alu_;
        unsigned long _data_width;
        unsigned long _active_bits;
        
        virtual void SetUp() {
            _data_width = 32;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _active_bits = 0b111;
            _control_ = new base::BusBase(base::_active_bits_size(_active_bits));
            _alu_ = new base::AluBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, _active_bits);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _alu_;
            _in_A_ = NULL;
            _in_B_ = NULL;
            _out_A_ = NULL;
            _out_B_ = NULL;
            _control_ = NULL;
            _alu_ = NULL;
        }
};

TEST_F(TestAlu32bits, test_ADD) {
    unsigned long _data1_A = 0b10101010101010101010101010101010;
    unsigned long _data1_B = 0b01010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A + _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu32bits, test_AND) {
    unsigned long _data1_A = 0b10101010101010101010101010101010;
    unsigned long _data1_B = 0b01010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A & _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu32bits, test_OR) {
    unsigned long _data1_A = 0b10101010101010101010101010101010;
    unsigned long _data1_B = 0b01010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A | _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu32bits, test_NOT) {
    unsigned long _data1_A = 0b10101010101010101010101010101010;
    unsigned long _data1_B = 0b01010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _active_bits));
    (*_alu_)();

    EXPECT_EQ((~_data1_A) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu32bits, test_XOR) {
    unsigned long _data1_A = 0b10101010101010101010101010101010;
    unsigned long _data1_B = 0b01010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A ^ _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

class TestAlu64bits:public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::AluBase* _alu_;
        unsigned long _data_width;
        unsigned long _active_bits;
        
        virtual void SetUp() {
            _data_width = 64;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _active_bits = 0b111;
            _control_ = new base::BusBase(base::_active_bits_size(_active_bits));
            _alu_ = new base::AluBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, _active_bits);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _alu_;
        }
};

TEST_F(TestAlu64bits, test_ADD) {
    unsigned long _data1_A = 0b1010101010101010101010101111101110101011101010101010101010101010;
    unsigned long _data1_B = 0b0101010101010101010101010101010101010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A + _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu64bits, test_AND) {
    unsigned long _data1_A = 0b1010101010101010101010111011101010101010101010101010101010101010;
    unsigned long _data1_B = 0b0101010101010101010101010101010101010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_AND, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A & _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu64bits, test_OR) {
    unsigned long _data1_A = 0b1010101010101010101010101010101010101010101010101010101010101010;
    unsigned long _data1_B = 0b0101010101010101010101011101110101010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_OR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A | _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu64bits, test_NOT) {
    unsigned long _data1_A = 0b1010101010101010101010111011101010101010101010101010101010101010;
    unsigned long _data1_B = 0b0101010101010101010101010101110111010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_NOT, _active_bits));
    (*_alu_)();

    EXPECT_EQ((~_data1_A) & base::_effective_bits(_data_width), _out_A_ -> out());
}

TEST_F(TestAlu64bits, test_XOR) {
    unsigned long _data1_A = 0b1010101010101010101010101011101110101010101010101010101010101010;
    unsigned long _data1_B = 0b0101010101010101010101010101010101010101010101010101010101010101;
    _in_A_ -> in(_data1_A);
    _in_B_ -> in(_data1_B);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(ALU_LOGIC_XOR, _active_bits));
    (*_alu_)();

    EXPECT_EQ((_data1_A ^ _data1_B) & base::_effective_bits(_data_width), _out_A_ -> out());
}



GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
