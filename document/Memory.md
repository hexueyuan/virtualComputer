# Memory存储设备类
Memory类应该被继承为其它类，以构造ROM、RAM、Flash等不同的设备。

```C++
class MemoryBase {
    public:
        MemoryBase();
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