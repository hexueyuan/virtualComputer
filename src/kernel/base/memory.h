#ifndef __MEMORY_BASE_H__
#define __MEMORY_BASE_H__
#include <iostream>
#include <string>

#include "bits.h"
#include "bus.h"

using namespace std;

#define MEMORY_NOT_ENABLE           0b00
#define MEMORY_READ                 0b10    //从输入总线读取数据
#define MEMORY_WRITE                0b11    //把数据写到输出总线
#define MEMORY_CONTAIN              0b01

//存储器主类
//可以被继承并生成各种存储设备
//指令长度2位
namespace base {
    class MemoryBase {
        public:
            //构造函数
            //输入：_input_ 数据输入总线
            //      _output_ 数据输出总线
            //      _control_ 控制总线
            //      _addr_ 地址选择总线
            //      _unit_bsize 存储单元字长 由于使用unsigned long来mock的，所以最大支持64位, 也就是8bytes
            //      _addr_bits_width 地址宽度 存储器空间 = 存储单元字长 * 存储单元数量 = 存储单元字长 * (2 ^ 地址宽度)
            //      _mem_active_bits 有效指令位
            MemoryBase();
            MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                        base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits);
            ~MemoryBase();

            //执行一次当前控制总线上的指令
            void operator()();

            //直接写入数据
            void write_in(unsigned long addr, unsigned long data);

            //读出数据
            unsigned long read_from(unsigned long addr);

            //命名
            void named(string _name);
            //调试
            void debug(unsigned long _addr, string prefix = "");

        protected:
            base::BusBase* _input_data_bus_;
            base::BusBase* _output_data_bus_;
            base::BusBase* _address_bus_;
            base::BusBase* _control_bus_;
            unsigned long _memory_active_bits_;

            unsigned long _memory_unit_bits_size_;
            unsigned long _memory_addr_bits_width_;
            unsigned long* _memory_;

            string _name_;
    };
}

#endif