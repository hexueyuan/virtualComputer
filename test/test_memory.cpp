#include <gtest/gtest.h>
#include "memory.h"

class TestMemory16bytes_with_1byte_unit:public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _addr_;
        base::BusBase* _control_;
        unsigned long _unit_bsize;
        unsigned long _addr_bits_width;
        unsigned long _mem_active_bits;

        base::MemoryBase* _mem_;

        virtual void SetUp() {
            _unit_bsize = 8; //8bits = 1 byte
            _addr_bits_width = 4; //2 ^ 4 = 16
            _mem_active_bits = 0b11;

            _in_ = new base::BusBase(_unit_bsize);
            _out_ = new base::BusBase(_unit_bsize);
            _addr_ = new base::BusBase(_addr_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_mem_active_bits));

            _mem_ = new base::MemoryBase(_in_, _out_, _control_, _addr_,
                                        _unit_bsize, _addr_bits_width, _mem_active_bits);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _addr_;
            delete _control_;
            delete _mem_;
        }
};

TEST_F(TestMemory16bytes_with_1byte_unit, Test_IO) {
    unsigned long _data1 = 0b10101010;
    unsigned long _data2 = 0b110101010;
    unsigned long _addr = 0b1010;

    _in_ -> in(_data1);
    _out_ -> in(0);
    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_READ, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_mem_ -> read_from(_addr), _data1);

    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_WRITE, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_out_ -> out(), _mem_ -> read_from(_addr));

    _in_ -> in(_data2);
    _out_ -> in(0);
    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_READ, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_mem_ -> read_from(_addr), _data2 & base::_effective_bits(_unit_bsize));
}

class TestMemory64bytes_with_4byte_unit:public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _addr_;
        base::BusBase* _control_;
        unsigned long _unit_bsize;
        unsigned long _addr_bits_width;
        unsigned long _mem_active_bits;

        base::MemoryBase* _mem_;

        virtual void SetUp() {
            _unit_bsize = 64; //8bits = 1 byte
            _addr_bits_width = 4; //2 ^ 4 = 16
            _mem_active_bits = 0b11;

            _in_ = new base::BusBase(_unit_bsize);
            _out_ = new base::BusBase(_unit_bsize);
            _addr_ = new base::BusBase(_addr_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_mem_active_bits));

            _mem_ = new base::MemoryBase(_in_, _out_, _control_, _addr_,
                                        _unit_bsize, _addr_bits_width, _mem_active_bits);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _addr_;
            delete _control_;
            delete _mem_;
        }
};

TEST_F(TestMemory64bytes_with_4byte_unit, Test_IO) {
    unsigned long _data1 = 0b1010101010101010101010101010101010101010101010101010101010101010;
    unsigned long _addr = 0b1010;

    _in_ -> in(_data1);
    _out_ -> in(0);
    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_READ, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_mem_ -> read_from(_addr), _data1);

    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_WRITE, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_out_ -> out(), _mem_ -> read_from(_addr));
}

class TestMemory32Mbytes_with_1byte_unit:public testing::Test {
    public:
        base::BusBase* _in_;
        base::BusBase* _out_;
        base::BusBase* _addr_;
        base::BusBase* _control_;
        unsigned long _unit_bsize;
        unsigned long _addr_bits_width;
        unsigned long _mem_active_bits;

        base::MemoryBase* _mem_;

        virtual void SetUp() {
            _unit_bsize = 8; //8bits = 1 byte
            _addr_bits_width = 25; //2 ^ 15 = 32 * 1024 * 1024 = 32M
            _mem_active_bits = 0b11;

            _in_ = new base::BusBase(_unit_bsize);
            _out_ = new base::BusBase(_unit_bsize);
            _addr_ = new base::BusBase(_addr_bits_width);
            _control_ = new base::BusBase(base::_active_bits_size(_mem_active_bits));

            _mem_ = new base::MemoryBase(_in_, _out_, _control_, _addr_,
                                        _unit_bsize, _addr_bits_width, _mem_active_bits);
        }

        virtual void TearDown() {
            delete _in_;
            delete _out_;
            delete _addr_;
            delete _control_;
            delete _mem_;
        }
};

TEST_F(TestMemory32Mbytes_with_1byte_unit, Test_IO) {
    unsigned long _data1 = 0b10101010;
    unsigned long _addr = 0b100000100001000010001001;

    _in_ -> in(_data1);
    _out_ -> in(0);
    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_READ, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_mem_ -> read_from(_addr), _data1);

    _addr_ -> in(_addr);
    _control_ -> in(base::_generate_instruction(MEMORY_WRITE, _mem_active_bits));
    (*_mem_)();

    EXPECT_EQ(_out_ -> out(), _mem_ -> read_from(_addr));
}

GTEST_API_ int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}