#include <gtest/gtest.h>
#include "selector.h"

class TestSelector8bits:public testing::Test {
    public:
        base::BusBase* _input_bus_0_;
        base::BusBase* _input_bus_1_;
        base::BusBase* _input_bus_2_;
        base::BusBase* _input_bus_3_;
        base::BusBase* _input_bus_4_;
        base::BusBase* _input_bus_5_;
        base::BusBase* _input_bus_6_;
        base::BusBase* _input_bus_7_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;
        base::SelectorBase* _selector_;

        virtual void SetUp() {
            _data_width = 8;
            _ins_active_bits = 0b1111;
            _input_bus_0_ = new base::BusBase(_data_width);
            _input_bus_1_ = new base::BusBase(_data_width);
            _input_bus_2_ = new base::BusBase(_data_width);
            _input_bus_3_ = new base::BusBase(_data_width);
            _input_bus_4_ = new base::BusBase(_data_width);
            _input_bus_5_ = new base::BusBase(_data_width);
            _input_bus_6_ = new base::BusBase(_data_width);
            _input_bus_7_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _selector_ = new base::SelectorBase(_input_bus_0_, _input_bus_1_, _input_bus_2_,
                                        _input_bus_3_, _input_bus_4_, _input_bus_5_, 
                                        _input_bus_6_, _input_bus_7_, _output_bus_, _control_bus_,
                                        _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_0_;
            delete _input_bus_1_;
            delete _input_bus_2_;
            delete _input_bus_3_;
            delete _input_bus_4_;
            delete _input_bus_5_;
            delete _input_bus_6_;
            delete _input_bus_7_;
            delete _output_bus_;
            delete _control_bus_;
            delete _selector_;
        }
};

TEST_F(TestSelector8bits, Test_io_case1) {
    _input_bus_0_ -> in(0);
    _input_bus_1_ -> in(1);
    _input_bus_2_ -> in(2);
    _input_bus_3_ -> in(3);
    _input_bus_4_ -> in(4);
    _input_bus_5_ -> in(5);
    _input_bus_6_ -> in(6);
    _input_bus_7_ -> in(7);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 7);
}

TEST_F(TestSelector8bits, Test_io_case2) {
    _input_bus_0_ -> in(0b111111111);
    _input_bus_1_ -> in(0b1111111111);
    _input_bus_2_ -> in(0b11111111111);
    _input_bus_3_ -> in(0b111111111111);
    _input_bus_4_ -> in(0b1111111111111);
    _input_bus_5_ -> in(0b11111111111111);
    _input_bus_6_ -> in(0b111111111111111);
    _input_bus_7_ -> in(0b1111111111111111);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 7);
}

class TestSelector16bits:public testing::Test {
    public:
        base::BusBase* _input_bus_0_;
        base::BusBase* _input_bus_1_;
        base::BusBase* _input_bus_2_;
        base::BusBase* _input_bus_3_;
        base::BusBase* _input_bus_4_;
        base::BusBase* _input_bus_5_;
        base::BusBase* _input_bus_6_;
        base::BusBase* _input_bus_7_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;
        base::SelectorBase* _selector_;

        virtual void SetUp() {
            _data_width = 16;
            _ins_active_bits = 0b1111;
            _input_bus_0_ = new base::BusBase(_data_width);
            _input_bus_1_ = new base::BusBase(_data_width);
            _input_bus_2_ = new base::BusBase(_data_width);
            _input_bus_3_ = new base::BusBase(_data_width);
            _input_bus_4_ = new base::BusBase(_data_width);
            _input_bus_5_ = new base::BusBase(_data_width);
            _input_bus_6_ = new base::BusBase(_data_width);
            _input_bus_7_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _selector_ = new base::SelectorBase(_input_bus_0_, _input_bus_1_, _input_bus_2_,
                                        _input_bus_3_, _input_bus_4_, _input_bus_5_, 
                                        _input_bus_6_, _input_bus_7_, _output_bus_, _control_bus_,
                                        _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_0_;
            delete _input_bus_1_;
            delete _input_bus_2_;
            delete _input_bus_3_;
            delete _input_bus_4_;
            delete _input_bus_5_;
            delete _input_bus_6_;
            delete _input_bus_7_;
            delete _output_bus_;
            delete _control_bus_;
            delete _selector_;
        }
};

TEST_F(TestSelector16bits, Test_io_case1) {
    _input_bus_0_ -> in(0);
    _input_bus_1_ -> in(1);
    _input_bus_2_ -> in(2);
    _input_bus_3_ -> in(3);
    _input_bus_4_ -> in(4);
    _input_bus_5_ -> in(5);
    _input_bus_6_ -> in(6);
    _input_bus_7_ -> in(7);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 7);
}

TEST_F(TestSelector16bits, Test_io_case2) {
    _input_bus_0_ -> in(0b11111111111111111);
    _input_bus_1_ -> in(0b111111111111111111);
    _input_bus_2_ -> in(0b1111111111111111111);
    _input_bus_3_ -> in(0b11111111111111111111);
    _input_bus_4_ -> in(0b111111111111111111111);
    _input_bus_5_ -> in(0b1111111111111111111111);
    _input_bus_6_ -> in(0b11111111111111111111111);
    _input_bus_7_ -> in(0b111111111111111111111111);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 7);
}

class TestSelector32bits:public testing::Test {
    public:
        base::BusBase* _input_bus_0_;
        base::BusBase* _input_bus_1_;
        base::BusBase* _input_bus_2_;
        base::BusBase* _input_bus_3_;
        base::BusBase* _input_bus_4_;
        base::BusBase* _input_bus_5_;
        base::BusBase* _input_bus_6_;
        base::BusBase* _input_bus_7_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;
        base::SelectorBase* _selector_;

        virtual void SetUp() {
            _data_width = 32;
            _ins_active_bits = 0b1111;
            _input_bus_0_ = new base::BusBase(_data_width);
            _input_bus_1_ = new base::BusBase(_data_width);
            _input_bus_2_ = new base::BusBase(_data_width);
            _input_bus_3_ = new base::BusBase(_data_width);
            _input_bus_4_ = new base::BusBase(_data_width);
            _input_bus_5_ = new base::BusBase(_data_width);
            _input_bus_6_ = new base::BusBase(_data_width);
            _input_bus_7_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _selector_ = new base::SelectorBase(_input_bus_0_, _input_bus_1_, _input_bus_2_,
                                        _input_bus_3_, _input_bus_4_, _input_bus_5_, 
                                        _input_bus_6_, _input_bus_7_, _output_bus_, _control_bus_,
                                        _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_0_;
            delete _input_bus_1_;
            delete _input_bus_2_;
            delete _input_bus_3_;
            delete _input_bus_4_;
            delete _input_bus_5_;
            delete _input_bus_6_;
            delete _input_bus_7_;
            delete _output_bus_;
            delete _control_bus_;
            delete _selector_;
        }
};

TEST_F(TestSelector32bits, Test_io_case1) {
    _input_bus_0_ -> in(0);
    _input_bus_1_ -> in(1);
    _input_bus_2_ -> in(2);
    _input_bus_3_ -> in(3);
    _input_bus_4_ -> in(4);
    _input_bus_5_ -> in(5);
    _input_bus_6_ -> in(6);
    _input_bus_7_ -> in(7);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 7);
}

TEST_F(TestSelector32bits, Test_io_case2) {
    _input_bus_0_ -> in(0b111111111111111111111111111111111);
    _input_bus_1_ -> in(0b1111111111111111111111111111111111);
    _input_bus_2_ -> in(0b11111111111111111111111111111111111);
    _input_bus_3_ -> in(0b111111111111111111111111111111111111);
    _input_bus_4_ -> in(0b1111111111111111111111111111111111111);
    _input_bus_5_ -> in(0b11111111111111111111111111111111111111);
    _input_bus_6_ -> in(0b111111111111111111111111111111111111111);
    _input_bus_7_ -> in(0b1111111111111111111111111111111111111111);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_NE(_output_bus_ -> out(), 7);
}

class TestSelector64bits:public testing::Test {
    public:
        base::BusBase* _input_bus_0_;
        base::BusBase* _input_bus_1_;
        base::BusBase* _input_bus_2_;
        base::BusBase* _input_bus_3_;
        base::BusBase* _input_bus_4_;
        base::BusBase* _input_bus_5_;
        base::BusBase* _input_bus_6_;
        base::BusBase* _input_bus_7_;
        base::BusBase* _output_bus_;
        base::BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _ins_active_bits;
        base::SelectorBase* _selector_;

        virtual void SetUp() {
            _data_width = 64;
            _ins_active_bits = 0b1111;
            _input_bus_0_ = new base::BusBase(_data_width);
            _input_bus_1_ = new base::BusBase(_data_width);
            _input_bus_2_ = new base::BusBase(_data_width);
            _input_bus_3_ = new base::BusBase(_data_width);
            _input_bus_4_ = new base::BusBase(_data_width);
            _input_bus_5_ = new base::BusBase(_data_width);
            _input_bus_6_ = new base::BusBase(_data_width);
            _input_bus_7_ = new base::BusBase(_data_width);
            _output_bus_ = new base::BusBase(_data_width);
            _control_bus_ = new base::BusBase(base::_active_bits_size(_ins_active_bits));

            _selector_ = new base::SelectorBase(_input_bus_0_, _input_bus_1_, _input_bus_2_,
                                        _input_bus_3_, _input_bus_4_, _input_bus_5_, 
                                        _input_bus_6_, _input_bus_7_, _output_bus_, _control_bus_,
                                        _data_width, _ins_active_bits);
        }

        virtual void TearDown() {
            delete _input_bus_0_;
            delete _input_bus_1_;
            delete _input_bus_2_;
            delete _input_bus_3_;
            delete _input_bus_4_;
            delete _input_bus_5_;
            delete _input_bus_6_;
            delete _input_bus_7_;
            delete _output_bus_;
            delete _control_bus_;
            delete _selector_;
        }
};

TEST_F(TestSelector64bits, Test_io_case1) {
    _input_bus_0_ -> in(0);
    _input_bus_1_ -> in(1);
    _input_bus_2_ -> in(2);
    _input_bus_3_ -> in(3);
    _input_bus_4_ -> in(4);
    _input_bus_5_ -> in(5);
    _input_bus_6_ -> in(6);
    _input_bus_7_ -> in(7);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 0);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_1, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 1);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_2, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 2);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_3, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 3);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_4, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 4);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_5, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 5);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_6, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 6);

    _output_bus_ -> in(0);

    _control_bus_ -> in(base::_generate_instruction(SELECTOR_ROUTE_7, _ins_active_bits));
    (*_selector_)();
    EXPECT_EQ(_output_bus_ -> out(), 7);
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}