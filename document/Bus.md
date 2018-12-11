# bus.h 总线类

```
class BusBase {
    public:
        BusBase(unsigned long _width_);
        ~BusBase();

        void in(unsigned long _data_);
        unsigned long out();

        void debug(string prefix = "");
        void named(string _name_);
        unsigned long width();
        string name();

    private:
        unsigned long  _bus_data_;
        unsigned long _bus_width_;

        string _bus_name_;
};
```
---
## 构造函数
`BusBase(unsigned long _width_);`  
**描述**  
构造总线对象。

**输入**  
1. (unsigned long) \_width 总线宽度，受unsigned long的大小影响不能超过64。

**输出**  
None

**例子**  
```
#include "bus.h"

int main() {
    unsigned long _data_width = 32;
    base::BusBase _inside_data_bus(_data_width);
}
```

**边界** 
1. \_width 不能超过64
---
## 析构函数
`~BusBase();`  
**描述**  
析构总线对象。

**输入**  
None

**输出**  
None

**例子**  
对象生命周期终止时自动调用。

**边界**  
None  

---

## Input操作
`void in(unsigned long _data_);`  
**描述**  
向总线写入数据。

**输入**  
1. (unsigned long) \_data\_ 写入的数据。

**输出**  
None

**例子**  
```
#include "bus.h"

int main() {
    unsigned long _data_width = 32;
    base::BusBase _inside_data_bus(_data_width);

    _inside_data_bus.in(0b0110110011);
}
```

**边界**  
1. 写入数据受总线数据宽度影响，取低有效位写入。  
---

## Output操作
`unsigned long out();`  
**描述**  
从总线内读出数据。

**输入**  
None

**输出**  
1. (unsigned long) 总线数据

**例子**  
```
#include <iostream>
#include "bus.h"

int main() {
    unsigned long _data_width = 32;
    base::BusBase _inside_data_bus(_data_width);

    _inside_data_bus.in(0b0110110011);
    std::cout << _inside_data_bus.out() << std::endl;
}
```

**边界**   
None

---

## 总线命名  
`void named(string _name_);`  
**描述**  
为总线命名。

**输入**  
1. (string) \_name\_ 总线名

**输出**  
None

**例子**  
```
#include <iostream>
#include <string>
#include "bus.h"

int main() {
    unsigned long _data_width = 32;
    base::BusBase _inside_data_bus(_data_width);

    _inside_data_bus.named(std::string("inside_data_bus"));
    std::cout << _inside_data_bus.name() << std::endl;

    return 0;
}
```

**边界** 
None

`string name();`  
**描述**  
返回总线名。

**输入**  
None

**输出**  
1. (string) 总线名

**例子**  
见named例子

**边界** 
None

---
## 总线宽度
`unsigned long width();`  
**描述**  
返回总线宽度。

**输入**  
None

**输出**  
1. (unsigned long)总线宽度

**例子**  
```
#include <iostream>
#include <string>
#include "bus.h"

int main() {
    unsigned long _data_width = 32;
    base::BusBase _inside_data_bus(_data_width);

    std::cout << _inside_data_bus.width() << std::endl;

    return 0;
}
```

**边界**  
None

---
## 调试
`void debug(string prefix = "");`  
**描述**  
输出调试信息。

**输入**  
1. (string) prefix 默认为空, 调试信息前缀

**输出**  
None

**例子**  
```
#include <iostream>
#include <string>
#include "bus.h"

int main() {
    unsigned long _data_width = 32;
    base::BusBase _inside_data_bus(_data_width);

    _inside_data_bus.debug();

    return 0;
}
```

**边界**   
None
