# Shiftor移位器类

```C++
class ShiftorBase {
    public:
        ShiftorBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_, 
                        BusBase* _control_, unsigned long _data_width, 
                        unsigned long _ins_active_bits_);
        ~ShiftorBase();

        void operator()();

        void named(string _name);
        void debug(string prefix = "");

    private:
        BusBase* _input_bus_A_;
        BusBase* _input_bus_B_;
        BusBase* _output_bus_;
        BusBase* _control_bus_;

        unsigned long _instruction_;
        unsigned long _data_width;
        unsigned long _instruction_active_bits_;
        string _name_;

        void _left_shift();
        void _right_shift();
        void _direct_transmission();
};
```

## 控制指令
指令长度2位
```C++
#define SHIFTOR_NOT_ENABLE          0b00    //移位器不执行指令
#define SHIFTOR_LEFT_SHIFT          0b01    //逻辑左移
#define SHIFTOR_RIGHT_SHIFT         0b10    //逻辑右移
#define SHIFTOR_DIRECT_TRANSMISSION 0b11    //数据直传
```

## 构造函数
```C++
ShiftorBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_, 
            BusBase* _control_, unsigned long _data_width, 
            unsigned long _ins_active_bits_);
```

**描述**
根据输入参数构造函数创建一个shiftor对象。

**输入**
1. (BusBase*) \_in_A_ 数据输入总线A，该总线输入操作数
2. (BusBase*) \_in_B_ 数据输入总线B，该总线输入操作数移位数
3. (BusBase*) \_out_ 数据输出总线
4. (BusBase*) \_control_ 控制指令输入总线
5. (unsigned long) \_data_width 数据宽度
6. (unsigned long) \_ins_active_bits_ 指令有效位

**输出**
None

**例子**
```C++
include "shiftor.h"
include "bus.h"

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_active_bits = 0b11;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_(_data_width);
    base::BusBase _control_(base::_active_bits_size(_ins_active_bits));

    base::ShiftorBase shif(&_in_A_, &_in_B_, &_out_, &_control_, _data_width, _ins_active_bits);
    shif.debug();
}
```

---

## 析构函数
```C++
~ShiftorBase();
```

**描述**
销毁ShiftorBase对象。

**输入**
None

**输出**
None

**例子**
None
析构函数在对象生命周期结束时自动被调用。

---

## 执行指令
```C++
void operator()();
```

**描述**
重载()运算符，使ShiftorBase对象成为一个伪函数，调用时从控制总线上获取一条指令并执行。指令由`控制指令`节定义。

**输入**
None

**输出**
None

**例子**
```C++
include<iostream>

include "shiftor.h"
include "bus.h"

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_active_bits = 0b11;
    base::BusBase _in_A_(_data_width);
    base::BusBase _in_B_(_data_width);
    base::BusBase _out_(_data_width);
    base::BusBase _control_(base::_active_bits_size(_ins_active_bits));

    base::ShiftorBase shif(&_in_A_, &_in_B_, &_out_, &_control_, _data_width, _ins_active_bits);
    
    //把0b0000110000左移3位
    _in_A_.in(0b0000110000);
    _in_B_.in(3);
    _control_.in(SHIFTOR_LEFT_SHIFT);
    shif();
    std::cout << "0b" << base::bin_str(_out_.out(), _data_width) << endl;

    return 0;
}
```