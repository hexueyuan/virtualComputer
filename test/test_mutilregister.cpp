#include <gtest/gtest.h>
#include <string>
#include "base/mutil_register.h"

using std::string;

class TestMutilRegister8bits: public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::MutilRegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 8;
            unsigned long _ins_width = 3;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::MutilRegisterBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, 0b111);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestMutilRegister8bits, Test_io_case1) {
    unsigned long _data1 = 0b10101010;
    unsigned long _data2 = 0b01010101;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_B_ -> out());
}

TEST_F(TestMutilRegister8bits, Test_io_case2) {
    unsigned long _data1 = 0b101010101111;
    unsigned long _data2 = 0b010101011111;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_NE(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_NE(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_NE(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_NE(_data2, _out_B_ -> out());
}

class TestMutilRegister16bits: public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::MutilRegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 16;
            unsigned long _ins_width = 3;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::MutilRegisterBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, 0b111);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestMutilRegister16bits, Test_io_case1) {
    unsigned long _data1 = 0b101010101111;
    unsigned long _data2 = 0b010101011111;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_B_ -> out());
}

TEST_F(TestMutilRegister16bits, Test_io_case2) {
    unsigned long _data1 = 0b10101010111100001111;
    unsigned long _data2 = 0b01010101111100001111;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_NE(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_NE(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_NE(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_NE(_data2, _out_B_ -> out());
}

class TestMutilRegister32bits: public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::MutilRegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 32;
            unsigned long _ins_width = 3;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::MutilRegisterBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, 0b111);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestMutilRegister32bits, Test_io_case1) {
    unsigned long _data1 = 0b10101010000011111111000011111111;
    unsigned long _data2 = 0b01010101000011110101010100011100;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_B_ -> out());
}

TEST_F(TestMutilRegister32bits, Test_io_case2) {
    unsigned long _data1 = 0b10101010111100000111010101010100011;
    unsigned long _data2 = 0b01010101111100111010101000111001010;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_NE(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_NE(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_NE(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_NE(_data2, _out_B_ -> out());
}

class TestMutilRegister64bits: public testing::Test {
    public:
        base::BusBase* _in_A_;
        base::BusBase* _in_B_;
        base::BusBase* _out_A_;
        base::BusBase* _out_B_;
        base::BusBase* _control_;
        base::MutilRegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 64;
            unsigned long _ins_width = 3;
            _in_A_ = new base::BusBase(_data_width);
            _in_B_ = new base::BusBase(_data_width);
            _out_A_ = new base::BusBase(_data_width);
            _out_B_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::MutilRegisterBase(_in_A_, _in_B_, _out_A_, _out_B_, _control_, _data_width, 0b111);
        }

        virtual void TearDown() {
            delete _in_A_;
            delete _in_B_;
            delete _out_A_;
            delete _out_B_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestMutilRegister64bits, Test_io_case1) {
    unsigned long _data1 = 0b1010101011100101001010001010000111001001010111111111111111111110;
    unsigned long _data2 = 0b0101010100000111010101010100011111110101010011001010000111101000;

    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_A, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_A_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_A, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data1, _out_B_ -> out());
    
    _in_A_ -> in(_data1);
    _in_B_ -> in(_data2);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_READ_B, 0b111));
    (*_reg_)();

    _in_A_ -> in(0);
    _in_B_ -> in(0);
    _out_A_ -> in(0);
    _out_B_ -> in(0);
    _control_ -> in(base::_generate_instruction(MUTIL_REGISTER_WRITE_B, 0b111));
    (*_reg_)();

    EXPECT_EQ(_data2, _out_B_ -> out());
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}