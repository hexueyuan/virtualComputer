#include <gtest/gtest.h>
#include "base/bus.h"

TEST(Test_BusBase_width, case1) {
    unsigned long _bus_wdith = 16;
    base::BusBase bus(_bus_wdith);

    EXPECT_EQ(bus.width(), _bus_wdith);
}

TEST(Test_BusBase_io, case2) {
    unsigned long _bus_wdith = 16;
    base::BusBase bus(_bus_wdith);

    unsigned long _case0 = 0b0011;
    bus.in(_case0);
    EXPECT_EQ(bus.out(), _case0);

    unsigned long _case1 = 0b111111111111111111;
    bus.in(_case1);
    EXPECT_NE(bus.out(), _case1);
}

TEST(Test_BusBase_named, case1) {
    unsigned long _bus_wdith = 16;
    base::BusBase bus(_bus_wdith);

    bus.named("TestBus");
    EXPECT_EQ(bus.name(), string("TestBus"));
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
