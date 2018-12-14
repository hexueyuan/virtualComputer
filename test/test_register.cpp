#include <gtest/gtest.h>
#include <string>
#include "base/register.h"

using std::string;

class TestRegister8bits: public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _control_;
        base::RegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 8;
            unsigned long _ins_width = 2;
            _in_ = new base::BusBase(_data_width);
            _out_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::RegisterBase(_in_, _out_, _control_, _data_width, 0b11);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestRegister8bits, Test_io1) {
    unsigned long _data = 0b11110000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_EQ(_data, _out_ -> out());
}

TEST_F(TestRegister8bits, Test_io2) {
    unsigned long _data = 0b1111111100000000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_NE(_data, _out_ -> out());
}

class TestRegister16bits: public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _control_;
        base::RegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 16;
            unsigned long _ins_width = 2;
            _in_ = new base::BusBase(_data_width);
            _out_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::RegisterBase(_in_, _out_, _control_, _data_width, 0b11);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestRegister16bits, Test_io1) {
    unsigned long _data = 0b1111000011110000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_EQ(_data, _out_ -> out());
}

TEST_F(TestRegister16bits, Test_io2) {
    unsigned long _data = 0b11111111000000001111111100000000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_NE(_data, _out_ -> out());
}

class TestRegister32bits: public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _control_;
        base::RegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 32;
            unsigned long _ins_width = 2;
            _in_ = new base::BusBase(_data_width);
            _out_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::RegisterBase(_in_, _out_, _control_, _data_width, 0b11);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestRegister32bits, Test_io1) {
    unsigned long _data = 0b111100001111000011110000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_EQ(_data, _out_ -> out());
}

TEST_F(TestRegister32bits, Test_io2) {
    unsigned long _data = 0b111111110000000011111111000000001111111100000000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_NE(_data, _out_ -> out());
}

class TestRegister64bits: public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _control_;
        base::RegisterBase* _reg_;

        virtual void SetUp() {
            unsigned long _data_width = 64;
            unsigned long _ins_width = 2;
            _in_ = new base::BusBase(_data_width);
            _out_ = new base::BusBase(_data_width);
            _control_ = new base::BusBase(_ins_width);
            _reg_ = new base::RegisterBase(_in_, _out_, _control_, _data_width, 0b11);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _control_;
            delete _reg_;
        }
};

TEST_F(TestRegister64bits, Test_io1) {
    unsigned long _data = 0b11110000111100001111000011110000;
    _in_ -> in(_data);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_READ, 0b11));
    (*_reg_)();

    _in_ -> in(0);
    _out_ -> in(0);
    _control_ -> in(base::_generate_instruction(REGISTER_WRITE, 0b11));
    (*_reg_)();

    EXPECT_EQ(_data, _out_ -> out());
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}