#include <sstream>
#include <fstream>
#include <cstdio>
#include <unistd.h>

#include "options.h"
#include "cpu.h"
#include "memory.h"
#include "memory_rom.h"
#include "instruction_generator.h"

//#include "base/base.h"
#include "base/register.h"
#include "base/mutil_register.h"

using namespace std;

//检测文件是否存在
bool isExist(const string& name) {
    return access(name.c_str(), F_OK) != -1;
}

void _error(string _err) {
    cout << "\033[41mError\033[0m: " << _err << endl;
}

void _warn(string _war) {
    cout << "\033[45mWarning\033[0m: " << _war << endl;
}

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
        compute::MemoryBase* _memory_;
        
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

        compute::InstructionGeneratorBase* _instruction_generator_;

        void _load_bin(string file);
        void _debug_info(string argv, string val);
};

ComputerBase::ComputerBase() {
    //创建内总线
    _inside_data_bus_ = new base::BusBase(DATA_BITS_WIDTH);
    _inside_data_bus_ -> named("inside_data_bus");

    _inside_control_bus_ = new base::BusBase(INSIDE_CONTROL_BITS_WIDTH);
    _inside_control_bus_ -> named("inside_control_bus");

    //创建外总线
    _outside_address_bus_ = new base::BusBase(OUTSIDE_ADDRESS_BITS_WIDTH);
    _outside_address_bus_ -> named("outside_address_bus");

    _outside_data_bus_ = new base::BusBase(OUTSIDE_DATA_BITS_WIDTH);
    _outside_data_bus_ -> named("outside_data_bus");

    _outside_control_bus_ = new base::BusBase(OUTSIZE_CONTROL_BITS_WIDTH);
    _outside_control_bus_ -> named("outside_control_bus");
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
    _memory_ = new compute::MemoryBase(_outside_data_bus_, _outside_data_bus_, 
                                        _outside_control_bus_, _outside_address_bus_, 
                                        MEMORY_UNIT_BITS_SIZE, OUTSIDE_ADDRESS_BITS_WIDTH, MEMORY_ACTIVE_BITS);
    _memory_ -> named("Memory");
    _instruction_generator_ = new compute::InstructionGeneratorBase(
                            _R0_, _R1_,
                            _R2_, _R3_,
                            _IP_, _PC_,
                            _SP_, _C_,
                            _D_, _MAR_,
                            _MDR_, _PSW_,
                            _CPU_, _memory_,
                            _inside_data_bus_, _inside_control_bus_,
                            _outside_data_bus_, _outside_control_bus_,
                            _outside_address_bus_);
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
    bool flag = false;
    string line;
    while(!flag) {
        cout << prefix;
        if (getline(cin, line)) {
            string ins, op, val;
            stringstream ss(line);
            ss >> ins >> op >> val;
            if (ins == "load") {
                _load_bin(op);
            } else if (ins == "exit") {
                flag = true;
            } else if (ins == "debug") {
                _debug_info(op, val);
            } else if (ins == "step") {
                (*_instruction_generator_)();
            }
        }
    }
    cout << "Thank & Bye!" << endl;
}

void ComputerBase::_load_bin(string file) {
    if (!isExist(file)) {
        _error(file + ": No this file.");
        return;
    }
    ifstream _in(file.c_str());
    string _ins;
    int __addr__ = 0;
    while (getline(_in, _ins)) {
        unsigned long _code = base::_str_bin(_ins);
        _memory_ -> write_in(__addr__, _code);
        __addr__++;
    }
    _in.close();
    return;
}

void ComputerBase::_debug_info(string argv, string val) {
    string prefix("  ");
    if (argv == "R0") {
        _R0_ -> debug(prefix);
    } else if (argv == "R1") {
        _R1_ -> debug(prefix);
    } else if (argv == "R2") {
        _R2_ -> debug(prefix);
    } else if (argv == "R3") {
        _R3_ -> debug(prefix);
    } else if (argv == "IP") {
        _IP_ -> debug(prefix);
    } else if (argv == "PC") {
        _PC_ -> debug(prefix);
    } else if (argv == "SP") {
        _SP_ -> debug(prefix);
    } else if (argv == "PSW") {
        _PSW_ -> debug(prefix);
    } else if (argv == "MAR") {
        _MAR_ -> debug(prefix);
    } else if (argv == "MDR") {
        _MDR_ -> debug(prefix);
    } else if (argv == "C") {
        _C_ -> debug(prefix);
    } else if (argv == "D") {
        _D_ -> debug(prefix);
    } else if (argv == "Register") {
        _R0_ -> debug(prefix);
        _R1_ -> debug(prefix);
        _R2_ -> debug(prefix);
        _R3_ -> debug(prefix);
        _PC_ -> debug(prefix);
        _IP_ -> debug(prefix);
        _SP_ -> debug(prefix);
        _C_ -> debug(prefix);
        _D_ -> debug(prefix);
        _PSW_ -> debug(prefix);
        _MAR_ -> debug(prefix);
        _MDR_ -> debug(prefix);
    } else if (argv == "CPU") {
        _CPU_ -> debug(prefix);
    } else if (argv == "Memory") {
        unsigned long _addr = base::_str_bin(val);
        _memory_ -> debug(_addr + 0, prefix);
        _memory_ -> debug(_addr + 1, prefix);
        _memory_ -> debug(_addr + 2, prefix);
        _memory_ -> debug(_addr + 3, prefix);
        _memory_ -> debug(_addr + 4, prefix);
    } else {
        _error(argv + ": Invalid argv.");
    }
}

int main() {
    ComputerBase MyComputer;
    MyComputer.client();

    return 0;
}