# Memory存储设备类
Memory类应该被继承为其它类，以构造ROM、RAM、Flash等不同的设备。

```C++
class MemoryBase {
    public:
        MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                    base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits);
        ~MemoryBase();

        void operator()();

        void write_in(unsigned long addr, unsigned long data);

        unsigned long read_from(unsigned long addr);

        void named(string _name);
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
```
---

## 控制命令
```C++
#define MEMORY_NOT_ENABLE           0b00    //禁能
#define MEMORY_READ                 0b10    //从输入总线读取数据
#define MEMORY_WRITE                0b11    //把数据写到输出总线
#define MEMORY_CONTAIN              0b01    //保留
```

## 构造函数
```C++
MemoryBase::MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                    base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits);
```

**描述**
创建MemoryBase对象，传入参数包括输入总线(\_input\_)，输出总线(\_output\_)，控制总线(\_control\_)，地址总线(\_addr\_)，存储单元位长(\_unit_bsize)，地址宽度(\_addr_bits_width)，指令有效位(\_mem_active_bits)。

## 运行
```C++
void MemoryBase::operator()();
```

**描述**
从指令总线上取出指令一条并执行。

## 手动写入数据
```C++
void MemoryBase::write_in(unsigned long addr, unsigned long data);
```

**描述**
提供初始化直接写入数据的方法，在计算机Init时可以写入数据，使Memory可以伪装成一个Rom存储器。

## 调试读取数据
```C++
unsigned long MemoryBase::read_from(unsigned long addr);
```

**描述**
提供直接读取数据的方法，用于调试，对外透明。

## 命名
```C++
void MemoryBase::named(string _name);
```

**描述**
设备命名

## 调试信息输出
```C++
void Memorybase::debug(unsigned long _addr, string prefix = "");
```

**描述**
输出设备的调试信息。