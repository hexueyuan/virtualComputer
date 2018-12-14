#include <gtest/gtest.h>
#include "shiftor.h"

class TestShiftor8bits:public testing::Test {
    public:
        base::BusBase* _input_bus_A_;
        base::BusBase* _input_bus_B_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;

        base::ShiftorBase* _shiftor_;

        virtual void SetUp() {
            _data_width = 8;
            _ins_active_bits = 0b11;
            _input_bus_A_ = new base::BusBase(_data_width);
            _input_bus_B_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _shiftor_ = new base::ShiftorBase(_input_bus_A_, _input_bus_B_, _output_bus_, _control_bus_,
                                            _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_A_;
            delete _input_bus_B_;
            delete _output_bus_;
            delete _control_bus_;
            delete _shiftor_;
        }
};

TEST_F(TestShiftor8bits, Test_LEFT_SHIFT_case_good) {
    unsigned long _data = 0b00010000;
    unsigned long _offset = 3;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor8bits, Test_LEFT_SHIFT_case_bad) {
    unsigned long _data = 0b00010000;
    unsigned long _offset = 7;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_NE(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor8bits, Test_RIGHT_SHIFT_case_good) {
    unsigned long _data = 0b00010000;
    unsigned long _offset = 4;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data >> _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor8bits, Test_RIGHT_SHIFT_case_bad) {
    unsigned long _data = 0b00010000;
    unsigned long _offset = 6;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_NE(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor8bits, Test_DIRECT_TRANSFORM) {
    unsigned long _data = 0b00010000;
    unsigned long _offset = 3;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data, _output_bus_ -> out());
}

class TestShiftor16bits:public testing::Test {
    public:
        base::BusBase* _input_bus_A_;
        base::BusBase* _input_bus_B_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;

        base::ShiftorBase* _shiftor_;

        virtual void SetUp() {
            _data_width = 16;
            _ins_active_bits = 0b11;
            _input_bus_A_ = new base::BusBase(_data_width);
            _input_bus_B_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _shiftor_ = new base::ShiftorBase(_input_bus_A_, _input_bus_B_, _output_bus_, _control_bus_,
                                            _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_A_;
            delete _input_bus_B_;
            delete _output_bus_;
            delete _control_bus_;
            delete _shiftor_;
        }
};

TEST_F(TestShiftor16bits, Test_LEFT_SHIFT_case_good) {
    unsigned long _data = 0b0000000100000000;
    unsigned long _offset = 7;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor16bits, Test_LEFT_SHIFT_case_bad) {
    unsigned long _data = 0b0000000100000000;
    unsigned long _offset = 15;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_NE(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor16bits, Test_RIGHT_SHIFT_case_good) {
    unsigned long _data = 0b0000000100000000;
    unsigned long _offset = 8;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data >> _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor16bits, Test_RIGHT_SHIFT_case_bad) {
    unsigned long _data = 0b0000000100000000;
    unsigned long _offset = 16;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_NE(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor16bits, Test_DIRECT_TRANSFORM) {
    unsigned long _data = 0b0000000100000000;
    unsigned long _offset = 18;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data, _output_bus_ -> out());
}

class TestShiftor32bits:public testing::Test {
    public:
        base::BusBase* _input_bus_A_;
        base::BusBase* _input_bus_B_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;

        base::ShiftorBase* _shiftor_;

        virtual void SetUp() {
            _data_width = 32;
            _ins_active_bits = 0b11;
            _input_bus_A_ = new base::BusBase(_data_width);
            _input_bus_B_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _shiftor_ = new base::ShiftorBase(_input_bus_A_, _input_bus_B_, _output_bus_, _control_bus_,
                                            _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_A_;
            delete _input_bus_B_;
            delete _output_bus_;
            delete _control_bus_;
            delete _shiftor_;
        }
};

TEST_F(TestShiftor32bits, Test_LEFT_SHIFT_case_good) {
    unsigned long _data = 0b00000000000000010000000000000000;
    unsigned long _offset = 15;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor32bits, Test_LEFT_SHIFT_case_bad) {
    unsigned long _data = 0b00000000000000010000000000000000;
    unsigned long _offset = 23;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_NE(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor32bits, Test_RIGHT_SHIFT_case_good) {
    unsigned long _data = 0b00000000000000010000000000000000;
    unsigned long _offset = 16;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data >> _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor32bits, Test_RIGHT_SHIFT_case_bad) {
    unsigned long _data = 0b00000000000000010000000000000000;
    unsigned long _offset = 24;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_NE(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor32bits, Test_DIRECT_TRANSFORM) {
    unsigned long _data = 0b00000000000000010000000000000000;
    unsigned long _offset = 32;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data, _output_bus_ -> out());
}

class TestShiftor64bits:public testing::Test {
    public:
        base::BusBase* _input_bus_A_;
        base::BusBase* _input_bus_B_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;

        base::ShiftorBase* _shiftor_;

        virtual void SetUp() {
            _data_width = 64;
            _ins_active_bits = 0b11;
            _input_bus_A_ = new base::BusBase(_data_width);
            _input_bus_B_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _shiftor_ = new base::ShiftorBase(_input_bus_A_, _input_bus_B_, _output_bus_, _control_bus_,
                                            _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_A_;
            delete _input_bus_B_;
            delete _output_bus_;
            delete _control_bus_;
            delete _shiftor_;
        }
};

TEST_F(TestShiftor64bits, Test_LEFT_SHIFT_case_good) {
    unsigned long _data = 0b0000000000000000000000000000000100000000000000000000000000000000;
    unsigned long _offset = 31;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data << _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor64bits, Test_LEFT_SHIFT_case_bad) {
    unsigned long _data = 0b0000000000000000000000000000000100000000000000000000000000000000;
    unsigned long _offset = 32;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_LEFT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ((unsigned long)0, _output_bus_ -> out());
}

TEST_F(TestShiftor64bits, Test_RIGHT_SHIFT_case_good) {
    unsigned long _data = 0b0000000000000000000000000000000100000000000000000000000000000000;
    unsigned long _offset = 32;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data >> _offset, _output_bus_ -> out());
}

TEST_F(TestShiftor64bits, Test_RIGHT_SHIFT_case_bad) {
    unsigned long _data = 0b0000000000000000000000000000000100000000000000000000000000000000;
    unsigned long _offset = 36;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ((unsigned long)0, _output_bus_ -> out());
}

TEST_F(TestShiftor64bits, Test_DIRECT_TRANSFORM) {
    unsigned long _data = 0b0000000000000000000000000000000100000000000000000000000000000000;
    unsigned long _offset = 36;

    _input_bus_A_ -> in(_data);
    _input_bus_B_ -> in(_offset);
    _control_bus_ -> in(base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, _ins_active_bits));
    (*_shiftor_)();

    EXPECT_EQ(_data, _output_bus_ -> out());
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}