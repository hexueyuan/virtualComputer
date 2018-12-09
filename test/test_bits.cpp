#include <gtest/gtest.h>
#include "base/bits.h"

TEST(Test_active_bits_offset, case1) {
    unsigned long _case0 = 0b0011000000000000;
    unsigned long _case1 = 0b11000000000000000000000000000000;
    unsigned long _case2 = 0b0;
    EXPECT_EQ(base::_active_bits_offset(_case0), 12);
    EXPECT_EQ(base::_active_bits_offset(_case1), 30);
    EXPECT_EQ(base::_active_bits_offset(_case2), sizeof(unsigned long));
}

TEST(Test_active_bits_size, case2) {
    unsigned long _case0 = 0b01111000000000;
    unsigned long _case1 = 0b11111111111111;
    unsigned long _case2 = 0b0;
    EXPECT_EQ(base::_active_bits_size(_case0), 4);
    EXPECT_EQ(base::_active_bits_size(_case1), 14);
    EXPECT_EQ(base::_active_bits_size(_case2), 0);
}

TEST(Test_extract_instruction, case3) {
    unsigned long _case0_ins =          0b1111111111111111;
    unsigned long _case0_active_bits =  0b1111000000000000;
    unsigned long _case1_ins =          0b1001111000101101;
    unsigned long _case1_active_bits =  0b0000001111100000;
    unsigned long _case2_ins =          0b1111111111111111;
    unsigned long _case2_active_bits =  0b0000000000000000;
    EXPECT_EQ(base::_extract_instruction(_case0_ins, _case0_active_bits), 0b1111);
    EXPECT_EQ(base::_extract_instruction(_case1_ins, _case1_active_bits), 0b10001);
    EXPECT_EQ(base::_extract_instruction(_case2_ins, _case2_active_bits), 0b0);
}

TEST(Test_generate_instruction, case4) {
    unsigned long _case0_ins =  0b1001;
    unsigned long _case0_active_bits = 0b111100000000000;
    unsigned long _case1_ins = 0b1111;
    unsigned long _case1_active_bits = 0b011110000;
    unsigned long _case2_ins = 0b0;
    unsigned long _case2_active_bits = 0b1100000;
    EXPECT_EQ(base::_generate_instruction(_case0_ins, _case0_active_bits), 0b100100000000000);
    EXPECT_EQ(base::_generate_instruction(_case1_ins, _case1_active_bits), 0b011110000);
    EXPECT_EQ(base::_generate_instruction(_case2_ins, _case2_active_bits), 0b0000000);
}

TEST(Test_bin_str, case5) {
    unsigned long _case0 = 0b10001000;
    unsigned long _case1 = 0b0;
    unsigned long _case2 = 0b10101010;
    EXPECT_EQ(base::_bin_str(_case0, 8), string("10001000"));
    EXPECT_EQ(base::_bin_str(_case1, 5), string("00000"));
    EXPECT_EQ(base::_bin_str(_case2, 5), string("01010"));
}

TEST(Test_str_bin, case6) {
    string _case0("11001100101010");
    string _case1("0");
    string _case2("1111111111111111111111111111111111111111111111111111111111111111111111");
    EXPECT_EQ(base::_str_bin(_case0), 0b11001100101010);
    EXPECT_EQ(base::_str_bin(_case1), 0b0);
    EXPECT_EQ(base::_str_bin(_case2), ~(0b0));
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
