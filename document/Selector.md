# Selector.h 选择器类
```C++
class SelectorBase {
    public:
        SelectorBase(BusBase* _in_0_, BusBase* _in_1_, 
                    BusBase* _in_2_, BusBase* _in_3_,
                    BusBase* _in_4_, BusBase* _in_5_, 
                    BusBase* _in_6_, BusBase* _in_7_,
                    BusBase* _out_, BusBase* _control_, 
                    unsigned long _d_width_, 
                    unsigned long _ins_active_bits_);
        ~SelectorBase();

        void operator()();

        void named(string _name);
        void debug(string prefix="");
        string name();

    private:
        BusBase* _input_bus_0_;
        BusBase* _input_bus_1_;
        BusBase* _input_bus_2_;
        BusBase* _input_bus_3_;
        BusBase* _input_bus_4_;
        BusBase* _input_bus_5_;
        BusBase* _input_bus_6_;
        BusBase* _input_bus_7_;
        BusBase* _output_bus_;
        BusBase* _control_bus_;

        unsigned long _instruction_;
        unsigned long _data_width_;
        unsigned long _instruction_active_bits_;
        string _name_;
};
```

---

## 控制指令
```C
#define SELECTOR_NOT_ENABLE     0b0000  //选择器不执行指令
#define SELECTOR_CONTAIN_0      0b0001  //保留
#define SELECTOR_CONTAIN_1      0b0010  //保留
#define SELECTOR_CONTAIN_2      0b0011  //保留
#define SELECTOR_CONTAIN_3      0b0100  //保留
#define SELECTOR_CONTAIN_4      0b0101  //保留
#define SELECTOR_CONTAIN_5      0b0110  //保留
#define SELECTOR_CONTAIN_6      0b0111  //保留
#define SELECTOR_ROUTE_0        0b1000  //选择路由0
#define SELECTOR_ROUTE_1        0b1001  //选择路由1
#define SELECTOR_ROUTE_2        0b1010  //选择路由2
#define SELECTOR_ROUTE_3        0b1011  //选择路由3
#define SELECTOR_ROUTE_4        0b1100  //选择路由4
#define SELECTOR_ROUTE_5        0b1101  //选择路由5
#define SELECTOR_ROUTE_6        0b1110  //选择路由6
#define SELECTOR_ROUTE_7        0b1111  //选择路由7
```

---
## 构造函数
```C++
SelectorBase(BusBase* _in_0_, BusBase* _in_1_, 
                    BusBase* _in_2_, BusBase* _in_3_,
                    BusBase* _in_4_, BusBase* _in_5_, 
                    BusBase* _in_6_, BusBase* _in_7_,
                    BusBase* _out_, BusBase* _control_, 
                    unsigned long _d_width_, 
                    unsigned long _ins_active_bits_);
```

**描述**  
输入参数为选择器的IO总线指针和选择器的参数，构造一个选择器对象。  

**输入**  
1. (BusBase*) \_in_0\_ 输入总线0  
2. (BusBase*) \_in_1\_ 输入总线1  
3. (BusBase*) \_in_2\_ 输入总线2  
4. (BusBase*) \_in_3\_ 输入总线3  
5. (BusBase*) \_in_4\_ 输入总线4  
6. (BusBase*) \_in_5\_ 输入总线5  
7. (BusBase*) \_in_6\_ 输入总线6  
8. (BusBase*) \_in_7\_ 输入总线7  
9. (BusBase*) \_out_ 输出总线
10. (BusBase*) \_control\_ 控制总线  
11. (unsigned long) \_d_width\_ 数据宽度  
12. (unsigned long) \_ins_active_bits\_ 指令有效位  

**输出**  
None  

**例子**  
```C++
#include "selector.h"
#include "bus.h"

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_active_bits = 0b1111;
    base::BusBase _in_0_(_data_width);
    base::BusBase _in_1_(_data_width);
    base::BusBase _in_2_(_data_width);
    base::BusBase _in_3_(_data_width);
    base::BusBase _in_4_(_data_width);
    base::BusBase _in_5_(_data_width);
    base::BusBase _in_6_(_data_width);
    base::BusBase _in_7_(_data_width);

    base::BusBase _out_(_data_width);
    base::BusBase _control_(base::_active_bits_size(_ins_active_bits));

    //构造选择器对象
    base::SelectorBase selec(&_in_0_, &_in_1_, &_in_2_, 
                            &_in_3_, &_in_4_, &_in_5_,
                            &_in_6_, &_in_7_, &_out_,
                            &_control_, _data_width,
                            _ins_active_bits);
    return 0;
}
```

**边界**  
1. 在单内总线结构中所有的输入总线可以是一根总线  

---
## 析构函数
```C++
~SelectorBase();
```
**描述**  
析构选择器对象

**输入**  
None

**输出**  
None

**例子**  
当选择器对象生命周期结束时自动调用。

**边界**  
None

---
## 执行指令  
```C++
void operator()();
```

**描述**  
执行控制总线上指令有效位处的一条指令，指令在文档开头处有记录。  

**输入**  
None

**输出**  
None

**例子**
```C++
#include <iostream>
#include "selector.h"
#include "bus.h"

using namespace std;

int main() {
    unsigned long _data_width = 16;
    unsigned long _ins_active_bits = 0b1111;
    base::BusBase _in_0_(_data_width);
    base::BusBase _in_1_(_data_width);
    base::BusBase _in_2_(_data_width);
    base::BusBase _in_3_(_data_width);
    base::BusBase _in_4_(_data_width);
    base::BusBase _in_5_(_data_width);
    base::BusBase _in_6_(_data_width);
    base::BusBase _in_7_(_data_width);

    base::BusBase _out_(_data_width);
    base::BusBase _control_(base::_active_bits_size(_ins_active_bits));

    //构造选择器对象
    base::SelectorBase selec(&_in_0_, &_in_1_, &_in_2_, 
                            &_in_3_, &_in_4_, &_in_5_,
                            &_in_6_, &_in_7_, &_out_,
                            &_control_, _data_width,
                            _ins_active_bits);
    
    //输入总线0写入数据
    _in_0_.in(0b10101011);
    //控制指令选择第0号路由总线数据
    _control_.in(base::_generate_instruction(SELECTOR_ROUTE_0, _ins_active_bits));
    //执行指令
    selec();
    //检查输出
    cout << _out_.out() << endl;

    return 0;
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