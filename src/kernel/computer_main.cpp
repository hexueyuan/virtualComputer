#include "options.h"

//微型计算机
class ComputerBase {
    public:
        ComputerBase();
        ~ComputerBase();

        //执行单条汇编代码
        void step_run();
        //交互终端
        void client();

    private:
        compute::CPU* _CPU_;
        compute::MemoryROM* _memory_;
        
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

        compute::InstructionGeneratorBase* _instruction_generator_;
};

ComputerBase::ComputerBase() {
    //创建寄存器组
    _R0_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_0_ACTIVE_BITS);
    _R1_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_1_ACTIVE_BITS);
    _R2_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_2_ACTIVE_BITS);
    _R3_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_3_ACTIVE_BITS);
    _IP_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_IP_ACTIVE_BITS);
    _PC_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_PC_ACTIVE_BITS);
    _SP_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_SP_ACTIVE_BITS);
    _PSW_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_PSW_ACTIVE_BITS);
    _C_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_C_ACTIVE_BITS);
    _D_ = new base::RegisterBase(_inside_data_bus_, _inside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_D_ACTIVE_BITS);
    _MAR_ = new base::MutilRegisterBase(_inside_data_bus_, _outside_address_bus_, _inside_data_bus_, _outside_address_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_MAR_ACTIVE_BITS);
    _MDR_ = new base::MutilRegisterBase(_inside_data_bus_, _outside_data_bus_, _inside_data_bus_, _outside_data_bus_, _inside_control_bus_, DATA_BITS_WIDTH, REGISTER_MDR_ACTIVE_BITS);

    _R0_ -> named("Register0");
    _R1_ -> named("Register1");
    _R2_ -> named("Register2");
    _R3_ -> named("Register3");
    _IP_ -> named("RegisterIP");
    _PC_ -> named("RegisterPC");
    _SP_ -> named("RegisterSP");
    _PSW_ -> named("RegisterPSW");
    _C_ -> named("RegisterC");
    _D_ -> named("RegisterD");
    _MAR_ -> named("RegisterMAR");
    _MDR_ -> named("RegisterMDR");

    //创建CPU
    _CPU_ = new compute::CPU(_inside_data_bus_, _inside_data_bus_, _inside_data_bus_, 
                                _inside_data_bus_, _inside_data_bus_, _inside_data_bus_, 
                                _inside_data_bus_, _inside_data_bus_, _inside_data_bus_,
                                _inside_data_bus_, _inside_data_bus_, _inside_data_bus_,
                                _inside_data_bus_, _inside_control_bus_,
                                SELECTOR_A_ACTIVE_BITS,
                                SELECTOR_B_ACTIVE_BITS,
                                ALU_ACTIVE_BITS,
                                SHIFTOR_ACTIVE_BITS,
                                DATA_BITS_WIDTH);
    _CPU_ -> named("CPU");

    //创建内存
    _memory_ = new compute::MemoryROM(_outside_data_bus_, _outside_data_bus_, 
                                        _outside_control_bus_, _outside_address_bus_, 
                                        MEMORY_UNIT_BITS_SIZE, OUTSIDE_ADDRESS_BITS_WIDTH, MEMORY_ACTIVE_BITS);
    _memory_ -> named("Memory");
}

ComputerBase::~ComputerBase() {
       delete _R0_;
       delete _R1_;
       delete _R2_;
       delete _R3_;
       delete _IP_;
       delete _PC_;
       delete _SP_;
       delete _PSW_;
       delete _MAR_;
       delete _MDR_;
       delete _CPU_;
        delete _memory_;
}

void ComputerBase::client() {
    string prefix("Virtual Computer V0.01> ");
    
}