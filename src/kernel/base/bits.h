#include <string>

using std::string;

#ifndef __BITS_H__
#define __BITS_H__

//基础比特位mock类，因为所有的数据在计算机中以比特位进行运算，为了进行模拟必须从底层开始模拟
//这里考虑过c++自带的bit库，因为这个库不能很好地支持动态位长，所以我选择自己写了一个简单的库
//来实现我的项目需求。
namespace base {
    //desc: 求有效位长偏移
    //in: _active_bits(unsigned long) 有效值存储变量，有效值表示值为1的值，返回最低一位为1的
    //  偏移。
    //out: _cnt(unsigned long) 有效值偏移。
    //example：func(0b0011100)=3
    unsigned long _active_bits_offset(unsigned long _active_bits) {
        unsigned long _cnt = 0;
        while (!((_active_bits >> _cnt) & 0b1)) ++_cnt;
        return _cnt;
    }

    //desc: 求有效位长
    //in: _active_bits(unsigned long) 有效值存储变量
    //out: _cnt(unsigned long) 有效值长度
    //example: func(0b0011000)=2
    unsigned long _active_bits_size(unsigned long _active_bits) {
        unsigned long _cnt = 0;
        _active_bits = _active_bits >> _active_bits_offset(_active_bits);
        while ((_active_bits >> _cnt) & 0b1) ++_cnt;
        return _cnt;
    }

    //desc: 抽取指令二进制
    //in: _global_ins(unsigned long) 微指令，一条包含所有逻辑部件的指令
    //      _active_bits(unsigned long) 有效位存储变量
    //out: none 有效位控制的有效指令
    //example: func(0b01101100101, 0b00111000000)=0b101
    unsigned long _extract_instruction(unsigned long _global_ins, unsigned long _active_bits) {
        return (_global_ins & _active_bits) >> _active_bits_offset(_active_bits);
    }

    //desc: 生成指令二进制
    //in: _ins(unsigned long) 指令
    //  _active_bits(unsigned long) 有效比特位
    //out: _active_ins(unsigned long) 有效指令
    //example: func(0b101, 0b00011100)=0b00010100
    unsigned long _generate_instruction(unsigned long _ins, unsigned long _active_bits) {
        return (_ins << _active_bits_offset(_active_bits)) & _active_bits;
    }

    //比特值转字符串
    //in: _num(unsigned long) 转换的值，bits(unsigned long)位长, 不超过64
    //out: _str(string) 字符串格式二进制
    //example: func(0b11011, 5)="11011"
    string _bin_str(unsigned long _num, unsigned long bits) {
        string _str = "";
        for (int i = bits - 1; i >= 0; --i) {
            _str += (char)(((_num >> i) & 0b1) + '0');
        }
        return _str;
    }
}
#endif
