#include "selector.h"

#include "options.h"
#include "bits.h"

#ifndef __ALU_H__
#define __ALU_H__

/*alu.h*/
#define ALU_NOT_ENABLE          0b000   //ALU不执行指令
#define ALU_ARITHMETIC_ADD      0b001   //算术加法
#define ALU_LOGIC_AND           0b010   //逻辑与
#define ALU_LOGIC_OR            0b011   //逻辑或
#define ALU_LOGIC_NOT           0b100   //逻辑非
#define ALU_DIRECT_TRANSMISSION 0b101   //数据直传
#define ALU_CONTAIN_1           0b110   //保留
#define ALU_CONTAIN_2           0b111   //保留

//ALU机器计算部件
//执行逻辑运算和加法运算
//指令长3位
namespace base {
    class AluBase {
        public:
            //构造函数
            //输入：_in_A_ 输入总线A
            //      _in_B_ 输入总线B
            //      _out_A_ 输出总线A
            //      _out_B_ 输出总线B
            //      _control_ 控制总线
            //      _ins_active_bits_ 指令有效位
            //ALU与selector串联，数据经选择器连接到ALU，再连接到selector，因为selector由双输入，所以这里ALU双输出
            AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                    BusBase* _control_, unsigned long _ins_active_bits_);
            ~AluBase();

            //执行当前控制总线上的一条指令
            void operator()();
            //调试
            void debug(string prefix = "");
            //命名
            void named(string _name_);

        private:
            BusBase* _input_bus_A_;
            BusBase* _input_bus_B_;
            BusBase* _output_bus_A_;
            BusBase* _output_bus_B_;
            BusBase* _control_bus_;

            unsigned long _instruction_;
            unsigned long _instruction_active_bits_;
            string _alu_name_;

            //算术加法
            void _ARITHMETIC_ADD();
            //逻辑与
            void _LOGIC_AND();
            //逻辑或
            void _LOGIC_OR();
            //逻辑非
            void _LOGIC_NOT();
            //直传
            void _DIRECT_TRANSMISSION();
    };

    AluBase::AluBase(BusBase* _in_A_, BusBase* _in_B_, BusBase* _out_A_, BusBase* _out_B_, 
                                                BusBase* _control_, unsigned long _ins_active_bits_) {
        _input_bus_A_ = _in_A_;
        _input_bus_B_ = _in_B_;
        _output_bus_A_ = _out_A_;
        _output_bus_B_ = _out_B_;
        _control_bus_ = _control_;
        _instruction_active_bits_ = _ins_active_bits_;
    }

    AluBase::~AluBase() {}

    void AluBase::operator()() {
        _instruction_ = _extract_instruction(_control_bus_ -> read(), _instruction_active_bits_);

        switch(_instruction_) {
            case ALU_ARITHMETIC_ADD:
                _ARITHMETIC_ADD();
                break;
            case ALU_LOGIC_AND:
                _LOGIC_AND();
                break;
            case ALU_LOGIC_OR:
                _LOGIC_OR();
                break;
            case ALU_LOGIC_NOT:
                _LOGIC_NOT();
                break;
            case ALU_DIRECT_TRANSMISSION:
                _DIRECT_TRANSMISSION();
                break;
            case ALU_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void AluBase::named(string _name_) {
        _alu_name_ = _name_;
    }

    void AluBase::debug(string prefix) {
        string space(prefix.length(), ' '); 
        cout << prefix << "ALU(" << _alu_name_ << ") instruction: " << 
            _bin_str(_instruction_, _active_bits_size(_instruction_active_bits_)) << endl;
        cout << space << "ALU(" << _alu_name_ << ") input_bus_A: " << _input_bus_A_ -> name() << endl;
        cout << space << "ALU(" << _alu_name_ << ") input_bus_B: " << _input_bus_B_ -> name() << endl;
        cout << space << "ALU(" << _alu_name_ << ") output_bus_A: " << _output_bus_A_ -> name() << endl;
        cout << space << "ALU(" << _alu_name_ << ") output_bus_B: " << _output_bus_B_ -> name() << endl;
        cout << prefix << "ALU(" << _alu_name_ << ") control_bus: " << _control_bus_ -> name() << endl;
    }

    void AluBase::_ARITHMETIC_ADD() {
        _output_bus_A_ -> write(_input_bus_A_ -> read() + _input_bus_B_ -> read());
    }

    void AluBase::_LOGIC_AND() {
        _output_bus_A_ -> write(_input_bus_A_ -> read() & _input_bus_B_ -> read());
    }

    void AluBase::_LOGIC_OR() {
        _output_bus_A_ -> write(_input_bus_A_ -> read() | _input_bus_B_ -> read());
    }

    void AluBase::_LOGIC_NOT() {
        _output_bus_A_ -> write(~(_input_bus_A_ -> read()));
    }

    void AluBase::_DIRECT_TRANSMISSION() {
        _output_bus_A_ -> write(_input_bus_A_ -> read());
        _output_bus_B_ -> write(_input_bus_B_ -> read());
    }
}

#endif
