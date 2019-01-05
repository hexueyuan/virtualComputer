# CPU中央处理器类

```C++
class CPU {
    public:
        CPU(base::BusBase* _in_R0_, base::BusBase* _in_R1_, base::BusBase* _in_R2_, base::BusBase* _in_R3_,
                base::BusBase* _in_IP_, base::BusBase* _in_PC_, base::BusBase* _in_C_, base::BusBase* _in_D_,
                base::BusBase* _in_MAR_, base::BusBase* _in_MDR_, base::BusBase* _in_PSW_, base::BusBase* _in_SP_,
                base::BusBase* _out_, base::BusBase* _control_, 
                unsigned long _selector_A_active_bits,
                unsigned long _selector_B_active_bits,
                unsigned long _alu_active_bits,
                unsigned long _shiftor_active_bits,
                unsigned long _data_bits_width);
        ~CPU();

        void operator()();
        void named(string _name);
        void debug(string prefix = "");

    private:
        base::SelectorBase* _selector_A_;
        base::SelectorBase* _selector_B_;
        base::AluBase* _alu_;
        base::ShiftorBase* _shiftor_;
        base::BusBase* _selector_A_out_bus_;
        base::BusBase* _selector_B_out_bus_;
        base::BusBase* _alu_out_bus_A_;
        base::BusBase* _alu_out_bus_B_;
        string _name_;
};
```