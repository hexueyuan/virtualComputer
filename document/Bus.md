# bits.h位操作定义

底层的模拟会涉及大量的位运算和逻辑操作，但是C++自身的bitset库无法满足位宽度的运行时动态拓展，并且逻辑运算操作也比较麻烦，因此我实现了一个bits的基本库，使用unsigned long作为基本数据类型，通过对unsigned long的设置来实现bit操作，并将一些为操作相关的函数也放在这里。

`unsigned long _active_bits_offset(unsigned long _active_bits)`  
**描述**  
求有效位长偏移。  

**输入**  
1. (unsigned long)_active_bits, 有效位变量  

**输出**  
1. (unsigned long) 偏移  

**例子**  
1. _active_bits_offset(0b00111000000) = 6, 有效位111偏移量为6
2. _active_bits_offset(0b111110) = 1, 有效位11111偏移量为1  

**边界**  
1. 输入0返回0
2. 有效位不连续时返回最低区间长度


`unsigned long _active_bits_size(unsigned long _active_bits)`  
**描述**  
求有效位有效长度.  

**输入**  
1. (unsigned long)_active_bits, 有效位变量  

**输出**  
1. (unsigned long) 长度

**例子**  
1. _active_bits_size(0b0111100) = 4, 有效位1111长度为4  
2. _active_bits_size(0b11000000) = 2, 有效位11长度为2  

**边界**  
1. 输入0返回0
2. 有效位不连续时返回最低区间长度

`unsigned long _generate_instruction(unsigned long _ins, unsigned long _active_bits)`  
**描述**  
根据有效位和无偏移指令生成偏移指令。  

**输入**  
1. (unsigned long)_ins 无偏移指令  
2. (unsigned long)_active_bits 有效位变量  

**输出**  
1. (unsigned long)有效偏移指令  

**例子**  
1. _generate_instruction(0b1011, 0b0011110000) = 0b0010110000, 把1011指令放在有效位1111处
2. _genearte_instruction(0b10101, 0b)

**边界**  
1. 有效位为0时返回也是0  
2. 有效位长度小于指令长度时，以有效位长度为准，截取掉指令高位  

`unsigne long _extract_instruction(unsigned long _global_ins, unsigned long _active_bits)`  
**描述**  
提取无偏移指令。

**输入**  
1. (unsigned long) _global_ins, 有效偏移指令
2. (unsigned long) _active_bits, 有效位变量

**输出**  
1. (unsigned long) 无偏移指令

**例子**  
1. _extract_instruction(0b001011000, 0b001111000) = 0b1011, 根据有效位1111位置提取指令1011
2. _extract_instruction(0b001000, 0b111000) = 0b001

**边界**  
1. 有效位变量为0时返回0

`string _bin_str(unsigned long _num, unsigned long bits)`  
**描述**  
数字转二进制字符串。

**输入**  
1. (unsigned long) _num 进行转换的数字
2. (unsigned long) _bits 转换长度

**输出**  
1. (string) 二进制字符串

**例子**  
1. _bin_str(0b1100, 4) = string("1100")
2. _bin_str(0b0, 8) = string("00000000")

**边界**  
1. bits为0时输出空串  
2. 输出字符串不带"0b"前缀  

`unsigned long _str_bin(string _str)`  
**描述**  
字符串转数字。

**输入**  
1. (string)_str 进行转换的二进制字符串

**输出**  
1. (unsigned long) 转换后的值

**例子**  
1. _str_bin(string("101100")) = 0b101100
2. _str_bin(string("0")) = 0b0

**边界**  
1. 当字符串非二进制字符串时，输出截断值，如果第一个字符就是非‘0’或者‘1’的字符，则直接返回0
2. 当字符串长度超过64位之后，在第64位处截断