#include <gtest/gtest.h>
#include "base/bus.h"

TEST(Test_BusBase_width, case1) {
    unsigned long _bus_width = 16;
    base::BusBase bus(_bus_width);

    EXPECT_EQ(bus.width(), _bus_width);
}

TEST(Test_BusBase_named, case2) {
    unsigned long _bus_width = 16;
    base::BusBase bus(_bus_width);

    bus.named("TestBus");
    EXPECT_EQ(bus.name(), string("TestBus"));
}

TEST(Test_BusBase_io, case3) {
    unsigned long _bus_width = 8;
    base::BusBase bus(_bus_width);

    unsigned long _case0 = 0b11110000;
    bus.in(_case0);
    EXPECT_EQ(bus.out(), _case0);

    unsigned long _case1 = 0b111111111111111111;
    bus.in(_case1);
    EXPECT_NE(bus.out(), _case1);
}

TEST(Test_BusBase_io, case4) {
    unsigned long _bus_width = 16;
    base::BusBase bus(_bus_width);

    unsigned long _case0 = 0b1111111100000000;
    bus.in(_case0);
    EXPECT_EQ(bus.out(), _case0);

    unsigned long _case1 = 0b111111111111111111;
    bus.in(_case1);
    EXPECT_NE(bus.out(), _case1);
}

TEST(Test_BusBase_io, case5) {
    unsigned long _bus_width = 32;
    base::BusBase bus(_bus_width);

    unsigned long _case0 = 0b11111111111111110000000000000000;
    bus.in(_case0);
    EXPECT_EQ(bus.out(), _case0);

    unsigned long _case1 = 0b11111111111111111111111111111111111111;
    bus.in(_case1);
    EXPECT_NE(bus.out(), _case1);
}

TEST(Test_BusBase_io, case6) {
    unsigned long _bus_width = 64;
    base::BusBase bus(_bus_width);

    unsigned long _case0 = 0b1111111111111111111111110000000011111111111111111111111100000000;
    bus.in(_case0);
    EXPECT_EQ(bus.out(), _case0);
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
