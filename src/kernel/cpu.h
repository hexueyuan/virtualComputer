#include "base/options.h"
#include "base/bus.h"

#include "base/selector.h"
#include "base/alu.h"
#include "base/shiftor.h"

//CPU主类
//CPU部件由两个选择器、ALU部件和移位器组成
//八个输入端口和一个输出端口，接受一条控制总线
namespace compute {
    class CPU {
        public:
            //构造函数
            //输入：
            //  R0 ~ R3 四个通用寄存器
            //  IP 指令寄存器
            //  PC 程序计数器
            //  C、D 数据暂存器
            //  MAR 地址寄存器
            //  MDR 数据寄存器
            //  PSW 程序状态字寄存器
            //  SP  堆栈指针
            //  _out_ 输出
            //  _control_ 指令控制总线
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

            //执行一次当前控制总线上的指令
            void operator()();
            //CPU命名
            void named(string _name);
            //调试
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

    CPU::CPU(base::BusBase* _in_R0_, base::BusBase* _in_R1_, base::BusBase* _in_R2_, base::BusBase* _in_R3_,
                base::BusBase* _in_IP_, base::BusBase* _in_PC_, base::BusBase* _in_C_, base::BusBase* _in_D_,
                base::BusBase* _in_MAR_, base::BusBase* _in_MDR_, base::BusBase* _in_PSW_, base::BusBase* _in_SP_,
                base::BusBase* _out_, base::BusBase* _control_,
                unsigned long _selector_A_active_bits,
                unsigned long _selector_B_active_bits,
                unsigned long _alu_active_bits,
                unsigned long _shiftor_active_bits,
                unsigned long _data_bits_width) {
        //定义CPU内总线
        _selector_A_out_bus_ = new base::BusBase(_data_bits_width);
        _selector_A_out_bus_ -> named("CPU_inside_selector_A_out_bus");
        _selector_B_out_bus_ = new base::BusBase(_data_bits_width);
        _selector_B_out_bus_ -> named("CPU_inside_selector_A_out_bus");
        _alu_out_bus_A_ = new base::BusBase(_data_bits_width);
        _alu_out_bus_A_ -> named("CPU_inside_ALU_out_bus_A");
        _alu_out_bus_B_ = new base::BusBase(_data_bits_width);
        _alu_out_bus_B_ -> named("CPU_insode_ALU_out_bus_B");
        
        //创建选择器
        //与cpu共用控制总线
        _selector_A_ = new base::SelectorBase(_in_R0_, _in_R1_, _in_R2_, _in_R3_,
                                            _in_IP_, _in_PC_, _in_C_, _in_SP_, 
                                            _selector_A_out_bus_, _control_,
                                            _selector_A_active_bits);
        _selector_B_ = new base::SelectorBase(_in_R0_, _in_R1_, _in_R2_, _in_R3_,
                                            _in_MAR_, _in_MDR_, _in_D_, _in_PSW_,
                                            _selector_B_out_bus_, _control_,
                                            _selector_B_active_bits);
        _selector_A_ -> named("CPU_inside_selector_A");
        _selector_B_ -> named("CPU_inside_selector_B");
        
        //创建ALU
        //与CPU共用控制总线
        _alu_ = new base::AluBase(_selector_A_out_bus_, _selector_B_out_bus_, _alu_out_bus_A_, _alu_out_bus_B_, 
                                _control_, _alu_active_bits);
        _alu_ -> named("CPU_inside_ALU");
        
        //创建移位器
        //与CPU共用控制总线
        _shiftor_ = new base::ShiftorBase(_alu_out_bus_A_, _alu_out_bus_B_, _out_, _control_, _shiftor_active_bits);
        _shiftor_ -> named("CPU_inside_shiftor");
    }

    CPU::~CPU() {
        delete _shiftor_;
        delete _alu_;
        delete _selector_A_;
        delete _selector_B_;
        delete _alu_out_bus_A_;
        delete _alu_out_bus_B_;
        delete _selector_A_out_bus_;
        delete _selector_B_out_bus_;
    }

    void CPU::operator()() {
        (*_selector_A_)();
        (*_selector_B_)();
        (*_alu_)();
        (*_shiftor_)();
    }

    void CPU::debug(string prefix) {
        _selector_A_ -> debug(prefix + "----");
        _selector_B_ -> debug(prefix + "----");
        _selector_A_out_bus_ -> debug(prefix + "----");
        _selector_B_out_bus_ -> debug(prefix + "----");
        _alu_ -> debug(prefix + "----");
        _alu_out_bus_A_ -> debug(prefix + "----");
        _alu_out_bus_B_ -> debug(prefix + "----");
        _shiftor_ -> debug(prefix + "----");
    }

    void CPU::named(string _name) {
        _name_ = _name;
    }
}
