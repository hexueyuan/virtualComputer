# alu.h 运算器ALU类
```C++
class AluBase {
    public:
        AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                BusBase* _control_, unsigned long _d_width, unsigned long _ins_active_bits_);
        ~AluBase();

        void operator()();
        void debug(string prefix = "");
        void named(string _name_);

    private:
        BusBase* _input_bus_A_;
        BusBase* _input_bus_B_;
        BusBase* _output_bus_A_;
        BusBase* _output_bus_B_;
        BusBase* _control_bus_;

        unsigned long _data_width;
        unsigned long _instruction_active_bits_;
        string _alu_name_;

        void _ARITHMETIC_ADD();
        void _LOGIC_AND();
        void _LOGIC_OR();
        void _LOGIC_NOT();
        void _DIRECT_TRANSMISSION();
        void _LOGIC_XOR();
};
```
---
## 控制指令
```C
#define ALU_NOT_ENABLE          0b000   //ALU不执行指令
#define ALU_ARITHMETIC_ADD      0b001   //算术加法
#define ALU_LOGIC_AND           0b010   //逻辑与
#define ALU_LOGIC_OR            0b011   //逻辑或
#define ALU_LOGIC_NOT           0b100   //逻辑非
#define ALU_DIRECT_TRANSMISSION 0b101   //数据直传
#define ALU_LOGIC_XOR           0b110   //保留
#define ALU_CONTAIN_2           0b111   //保留
```

## 构造函数
```C++
AluBase(BusBase* _in_A_, BusBase* _in_B_, 
        BusBase* _out_A_, BusBase* _out_B_, 
        BusBase* _control_, 
        unsigned long _d_width, 
        unsigned long _ins_active_bits_);
```
**描述**  
输入ALU的IO总线和ALU参数，构造返回一个ALU运算器对象。

**输入**  
1. (BusBase*) \_in_A\_ 输入总线A
2. (BusBase*) \_in_B\_ 输入总线B
3. (BusBase*) \_out_A\_ 输出总线A
4. (BusBase*) \_out_B\_ 输出总线B
5. (BusBase*) \_control\_ 控制总线
6. (unsigned long) \_d_width 数据宽度
7. (unsigned long) \_ins_active_bits\_ 指令有效位

**输出**  
None

**例子**  
```C++
#include "alu.h"
#include "bus.h"

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_active_bits = 0b111;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_A_(_data_width);
    base::BusBase _out_B_(_data_width);
    base::BusBase _control_(base::_active_bits_size(_ins_active_bits));

    base::AluBase ALU(&_in_A_, &_in_B, &_out_A_, &_out_B_, 
                    &_control_, _data_width, _ins_active_bits);
    
    return 0;
}
```

**边界**  
None

---

## 析构函数
```C++
~AluBase();
```

**描述**  
析构ALU运算器对象

**输入**  
None

**输出**  
None

**例子**  
当运算器对象生命周期结束时自动调用。

**边界**  
None

---

## 执行指令
```C++
void operator()();
```

**描述**  
重载()运算符，该函数从控制总线上把指令有效位处的指令取出并根据预定义指令执行。  

**输入**  
None  

**输出**  
None

**例子**  
```C++
#include <iostream>
#include "alu.h"
#include "bus.h"

using namespace std;

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_active_bits = 0b111;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_A_(_data_width);
    base::BusBase _out_B_(_data_width);
    base::BusBase _control_(base::_active_bits_size(_ins_active_bits));

    base::AluBase ALU(&_in_A_, &_in_B, &_out_A_, &_out_B_, 
                    &_control_, _data_width, _ins_active_bits);
    //8 + 13
    //写入数据
    _in_A_.in(8);
    _in_B_.in(13);
    //写入指令
    _control_.in(base::_generate_instruction(ALU_ARITHMETIC_ADD, _ins_active_bits));
    //执行指令
    ALU();
    //输出
    cout << _out_A_.out() << endl;

    return 0;
}
```

---

## 调试信息
```C++
void debug(string prefix="");
```
同bus.h的调试函数。

---

## 对象命名
```C++
void named(string _name);
```
同bus.h命名函数。