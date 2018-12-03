#include "base/options.h"
#include "base/bus.h"

#include "base/selector.h"
#include "base/alu.h"
#include "base/shiftor.h"

namespace compute {
    class CPU {
        public:
            CPU(base::BusBase* _in_R0_, base::BusBase* _in_R1_, base::BusBase* _in_R2_, base::BusBase* _in_R3_,
                    base::BusBase* _in_IP_, base::BusBase* _in_PC_, base::BusBase* _in_C_, base::BusBase* _in_D_,
                    base::BusBase* _in_MAR_, base::BusBase* _in_MDR_, base::BusBase* _in_PSW_, base::BusBase* _in_SP_,
                    base::BusBase* _out_, base::BusBase* _control_);
            ~CPU();

            void operator()();
            void _named();
            void debug();

        private:
            base::SelectorBase* _selector_A_;
            base::SelectorBase* _selector_B_;
            base::AluBase* _alu_;
            base::ShiftorBase* _shiftor_;
            base::BusBase* _selector_A_out_bus_;
            base::BusBase* _selector_B_out_bus_;
            base::BusBase* _alu_out_bus_A_;
            base::BusBase* _alu_out_bus_B_;
    };

#define BUS_RO 0b000
#define BUS_R1 0b001
#define BUS_R2 0b010
#define BUS_R3 0b011

#define BUS_IP 0b100
#define BUS_MAR 0b100

#define BUS_PC 0b101
#define BUS_MDR 0b101

#define BUS_C 0b110
#define BUS_D 0b110

#define BUS_SP 0b111
#define BUS_PSW 0b111
    CPU::CPU(base::BusBase* _in_R0_, base::BusBase* _in_R1_, base::BusBase* _in_R2_, base::BusBase* _in_R3_,
                base::BusBase* _in_IP_, base::BusBase* _in_PC_, base::BusBase* _in_C_, base::BusBase* _in_D_,
                base::BusBase* _in_MAR_, base::BusBase* _in_MDR_, base::BusBase* _in_PSW_, base::BusBase* _in_SP_,
                base::BusBase* _out_, base::BusBase* _control_) {
        _selector_A_out_bus_ = new base::BusBase;
        _selector_B_out_bus_ = new base::BusBase;
        _alu_out_bus_A_ = new base::BusBase;
        _alu_out_bus_B_ = new base::BusBase;
        _selector_A_ = new base::SelectorBase(_in_R0_, _in_R1_, _in_R2_, _in_R3_,
                                            _in_IP_, _in_PC_, _in_C_, _in_SP_, 
                                            _selector_A_out_bus_, _control_,
                                            SELECTOR_A_INSTRUCTION_OFFSET);
        _selector_B_ = new base::SelectorBase(_in_R0_, _in_R1_, _in_R2_, _in_R3_,
                                            _in_MAR_, _in_MDR_, _in_D_, _in_PSW_,
                                            _selector_B_out_bus_, _control_,
                                            SELECTOR_B_INSTRUCTION_OFFSET);
        _alu_ = new base::AluBase(_selector_A_out_bus_, _selector_B_out_bus_, _alu_out_bus_A_, _alu_out_bus_B_, 
                                _control_, ALU_INSTRUCTION_OFFSET);
        _shiftor_ = new base::ShiftorBase(_alu_out_bus_A_, _alu_out_bus_B_, _out_, _control_, SHIFTOR_INSTRUCTION_OFFSET);
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

    void CPU::debug() {
        _selector_A_ -> debug();
        _selector_B_ -> debug();
        _selector_A_out_bus_ -> debug();
        _selector_B_out_bus_ -> debug();
        _alu_ -> debug();
        _alu_out_bus_A_ -> debug();
        _alu_out_bus_B_ -> debug();
        _shiftor_ -> debug();
    }

    void CPU::_named() {
        _shiftor_ -> _named("");
        _alu_ -> _named("");
        _selector_A_ -> _named("A");
        _selector_B_ -> _named("B");
        _alu_out_bus_A_ -> _named("ALU_out_bus_A");
        _alu_out_bus_B_ -> _named("ALU_out_bus_B");
        _selector_A_out_bus_ -> _named("selector_out_bus_A");
        _selector_B_out_bus_ -> _named("selector_out_bus_B");
    }
}
