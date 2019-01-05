# Instruction_generator微指令生成器类

```C++
class InstructionGeneratorBase {
    public:
        InstructionGeneratorBase(base::RegisterBase* _r0_, base::RegisterBase* _r1_,
                                base::RegisterBase* _r2_, base::RegisterBase* _r3_,
                                base::RegisterBase* _ip_, base::RegisterBase* _pc_,
                                base::RegisterBase* _sp_, base::RegisterBase* _c_,
                                base::RegisterBase* _d_, base::MutilRegisterBase* _mar_,
                                base::MutilRegisterBase* _mdr, base::RegisterBase* _psw_,
                                computer::CPU* _cpu_, base::MemoryBase* _mem_,
                                base::BusBase* _in_data_bus_, base::BusBase* _in_control_bus_,
                                base::BusBase* _out_data_bus_, base::BusBase* _out_control_bus_,
                                base::BusBase* _out_address_bus);
        ~InstructionGeneratorBase();
        
        void operator()();
        void debug();
    
    private:
        computer::CPU* _CPU_;
        base::MemoryBase* _memory_;
        
        base::RegisterBase* _R0_;
        base::RegisterBase* _R1_;
        base::RegisterBase* _R2_;
        base::RegisterBase* _R3_;
        base::RegisterBase* _IP_;
        base::RegisterBase* _PC_;
        base::RegisterBase* _SP_;
        base::RegisterBase* _C_;
        base::RegisterBase* _D_;
        base::MutilRegisterBase* _MAR_;
        base::MutilRegisterBase* _MDR_;
        base::RegisterBase* _PSW_;

        base::BusBase* _inside_data_bus_;
        base::BusBase* _inside_control_bus_;

        base::BusBase* _outside_address_bus_;
        base::BusBase* _outside_data_bus_;
        base::BusBase* _outside_control_bus_;

        void _run_once();
        void _register_write_to_inside_bus(unsigned long _reg);
        void _register_read_from_inside_bus(unsigned long _reg);
        void _memory_write_to_outside_bus();
        void _memory_read_from_outside_bus();
        void _mov_inside_bus_to_outside_address_bus();
        void _mov_inside_bus_to_outside_data_bus();
        void _mov_outside_bus_to_inside_bus();

        void _load_instruction();

        void _NOP(unsigned long _ins);
        void _MOV(unsigned long _ins);
        void _ADD(unsigned long _ins);
        void _ZERO(unsigned long _ins);
        void _LSFT(unsigned long _ins);
        void _RSFT(unsigned long _ins);
        void _AND(unsigned long _ins);
        void _OR(unsigned long _ins);
        void _NOT(unsigned long _ins);
        void _XOR(unsigned long _ins);
        void _CMP(unsigned long _ins);
        void _JMP(unsigned long _ins);
        void _JMPZ(unsigned long _ins);
        void _JMPP(unsigned long _ins);
        void _JMPN(unsigned long _ins);
};
```