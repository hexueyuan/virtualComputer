# Register.h 寄存器类
```C++
class RegisterBase {
    public:
        RegisterBase(BusBase* _in_, BusBase* _out_, BusBase* _control_, 
                    unsigned long _d_width, unsigned long _ins_active_bits_);
        ~RegisterBase();

        void operator()();

        void named(string _name);
        void debug(string prefix="");
        string name();

    private:
        BusBase* _input_bus_;
        BusBase* _output_bus_;
        BusBase* _control_bus_;
        
        unsigned long _register_;
        unsigned long _data_width_;
        unsigned long _instruction_active_bits_;
        string _name_;
};
```
---  

## 控制指令
基础寄存器类控制指令工两位，控制读写状态以及sleep状态
```C
#define REGISTER_NOT_ENABLE     0b00    //sleep状态，寄存器不执行任何指令
#define REGISTER_CONTAIN        0b01    //保留
#define REGISTER_WRITE          0b10    //向输出总线写数据
#define REGISTER_READ           0b11    //从输入总线读数据
```
---
## 构造函数

```C++
RegisterBase(BusBase* _in_, BusBase* _out_, BusBase* _control_, unsigned long _d_width, unsigned long _ins_active_bits_);
```

**描述**  
构造寄存器对象。

**输入**  
1. (BusBase*) \_in\_ 数据输入总线
2. (BusBase*) \_out\_ 数据输出总线
3. (BusBase*) \_control\_ 控制总线
4. (unsigned long) \_d_width 数据宽度
5. (unsigned long) \_ins_active_bits\_ 指令有效位，多个寄存器和多个组件共用一条总线，不同组件使用不同位。

**输出**  
None

**例子**  
```C++
#include "register.h"
#include "bus.h"

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_width = 8;
    base::BusBase _in_(_data_width);
    base::BusBase _out_(_data_width);

    unsigned long _active_bits = 0b00001100;
    base::BusBase _control_(_ins_width);

    base::RegisterBase _reg(&_in_, &_out_, &_control_, _data_width, _active_bits);
}
```

**边界**  
None

---

## 析构函数
```C++
~RegisterBase();
```
**描述**  
析构寄存器对象

**输入**  
None

**输出**  
None

**例子**  
当寄存器对象生命周期结束时自动调用。

**边界**  
None

---
## 执行指令
```C++
void operator()();
```
**描述**  
重载()运算符，使对象成为一个伪函数，调用该方法后，寄存器从控制总线上取出指令，并根据有效位取得指令后，执行该指令。  
如果是REGISTER_WRITE则把寄存器的数据写到输出总线上，如果是REGISTER_READ则从输入总线上把数据读进来。

**输入**  
None

**输出**  
None

**例子**  
```C++
#include "register.h"
#include "bus.h"
#include "bits.h"

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_width = 8;
    base::BusBase _in_(_data_width);
    base::BusBase _out_(_data_width);

    unsigned long _active_bits = 0b00001100;
    base::BusBase _control_(_ins_width);

    base::RegisterBase _reg(&_in_, &_out_, &_control_, _data_width, _active_bits);

    //使用bits下的函数根据有效位生产有效指令并写入控制总线
    _control_.in(base::_generate_instruction(REGISTER_READ, _active_bits));
    _in_.in(0b0011111111000000);

    //执行指令
    _reg();
}
```

**边界**  
None

---
## 命名
```C++
void named(string _name);
```
同bus.h命名函数。  

```C++
string name();
```
同bus.h的name函数。

---

## 调试
```C++
void debug(string prefix="");
```
同bus.h的调试函数。
