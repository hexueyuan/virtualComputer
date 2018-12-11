# mutil_register.h 双I/O端口寄存器

```C++
class MutilRegisterBase {
    public:
        MutilRegisterBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                    BusBase* _control_, unsigned long _d_width, unsigned long _ins_active_bits_);
        ~MutilRegisterBase();

        void operator()();

        void named(string _name);
        void debug(string prefix="");
        string name();

    private:
        BusBase* _input_bus_A_;
        BusBase* _input_bus_B_;
        BusBase* _output_bus_A_;
        BusBase* _output_bus_B_;
        BusBase* _control_bus_;
        
        unsigned long _register_;
        unsigned long _data_width_;
        unsigned long _instruction_active_bits_;
        string _name_;
};
```

## 说明
该组件和普通的寄存器组件register.h方法一致，因此直接参考register.h的说明文档即可，唯一的区别在于双I/O端口的寄存器有两个输入端口和两个输出端口，因此在构造函数上会多两个参数，并且由于需要控制的因素增加，两个bit的指令无法满足，所以双I/O端口的寄存器指令扩展为3位。设计这类寄存器掉原因是像MAR和MDR这类寄存器需要在外总线和内总线上读写数据，因此需要有两个I/O端口。

## 指令  
```C++
#define MUTIL_REGISTER_NOT_ENABLE   0b000   //空指令，寄存器无动作
#define MUTIL_REGISTER_READ_A       0b100   //从输入总线A读取数据
#define MUTIL_REGISTER_READ_B       0b101   //从输入总线B读取数据
#define MUTIL_REGISTER_WRITE_A      0b110   //向输出总线A输出数据
#define MUTIL_REGISTER_WRITE_B      0b111   //向输出总线B输出数据
```