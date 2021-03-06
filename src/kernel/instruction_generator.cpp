#include "instruction_generator.h"

namespace computer {
   InstructionGeneratorBase::InstructionGeneratorBase(base::RegisterBase* _r0_, base::RegisterBase* _r1_,
                                                    base::RegisterBase* _r2_, base::RegisterBase* _r3_,
                                                    base::RegisterBase* _ip_, base::RegisterBase* _pc_,
                                                    base::RegisterBase* _sp_, base::RegisterBase* _c_,
                                                    base::RegisterBase* _d_, base::MutilRegisterBase* _mar_,
                                                    base::MutilRegisterBase* _mdr_, base::RegisterBase* _psw_,
                                                    computer::CPU* _cpu_, base::MemoryBase* _mem_,
                                                    base::BusBase* _in_data_bus_, base::BusBase* _in_control_bus_,
                                                    base::BusBase* _out_data_bus_, base::BusBase* _out_control_bus_,
                                                    base::BusBase* _out_address_bus) {
        _inside_data_bus_ = _in_data_bus_;
        _inside_control_bus_ = _in_control_bus_;
        _outside_address_bus_ = _out_address_bus;
        _outside_data_bus_ = _out_data_bus_;
        _outside_control_bus_ = _out_control_bus_;

        _R0_ = _r0_; 
        _R1_ = _r1_;
        _R2_ = _r2_;
        _R3_ = _r3_;
        _IP_ = _ip_;
        _PC_ = _pc_;
        _SP_ = _sp_;
        _PSW_ = _psw_;
        _C_ = _c_;
        _D_ = _d_;
        _MAR_ = _mar_;
        _MDR_ = _mdr_;

        _CPU_ = _cpu_;

        _memory_ = _mem_;
    }

   InstructionGeneratorBase::~InstructionGeneratorBase() {
       delete _inside_control_bus_;
       delete _inside_data_bus_;
       delete _outside_address_bus_;
       delete _outside_control_bus_;
       delete _outside_data_bus_;
   }

   void InstructionGeneratorBase::_run_once() {
       (*_R0_)();
       (*_R1_)();
       (*_R2_)();
       (*_R3_)();
       (*_IP_)();
       (*_PC_)();
       (*_SP_)();
       (*_PSW_)();
       (*_C_)();
       (*_D_)();
       (*_MAR_)();
       (*_MDR_)();
       (*_CPU_)();
       (*_memory_)();
   }

    void InstructionGeneratorBase::_register_write_to_inside_bus(unsigned long _reg) {
        unsigned long _ins;
        switch (_reg) {
            case REGISTER_0:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_0_ACTIVE_BITS);
                break;
            case REGISTER_1:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_1_ACTIVE_BITS);
                break;
            case REGISTER_2:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_2_ACTIVE_BITS);
                break;
            case REGISTER_3:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_3_ACTIVE_BITS);
                break;
            case REGISTER_IP:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_IP_ACTIVE_BITS);
                break;
            case REGISTER_PC:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_PC_ACTIVE_BITS);
                break;
            case REGISTER_SP:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_SP_ACTIVE_BITS);
                break;
            case REGISTER_C:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_C_ACTIVE_BITS);
                break;
            case REGISTER_D:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_D_ACTIVE_BITS);
                break;
            case REGISTER_PSW:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_WRITE, REGISTER_PSW_ACTIVE_BITS);
                break;
            case REGISTER_MAR:
                _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_WRITE_A, REGISTER_MAR_ACTIVE_BITS);
                break;
            case REGISTER_MDR:
                _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_WRITE_A, REGISTER_MDR_ACTIVE_BITS);
                break;
            default:
                _ins = _inside_ins_nop_;
        }
        _inside_control_bus_ -> in(_ins);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();
   }

   void InstructionGeneratorBase::_register_read_from_inside_bus(unsigned long _reg) {
        unsigned long _ins;
        switch (_reg) {
            case REGISTER_0:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_0_ACTIVE_BITS);
                break;
            case REGISTER_1:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_1_ACTIVE_BITS);
                break;
            case REGISTER_2:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_2_ACTIVE_BITS);
                break;
            case REGISTER_3:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_3_ACTIVE_BITS);
                break;
            case REGISTER_IP:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_IP_ACTIVE_BITS);
                break;
            case REGISTER_PC:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_PC_ACTIVE_BITS);
                break;
            case REGISTER_SP:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_SP_ACTIVE_BITS);
                break;
            case REGISTER_C:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_C_ACTIVE_BITS);
                break;
            case REGISTER_D:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_D_ACTIVE_BITS);
                break;
            case REGISTER_PSW:
                _ins = _inside_ins_nop_ | base::_generate_instruction(REGISTER_READ, REGISTER_PSW_ACTIVE_BITS);
                break;
            case REGISTER_MAR:
                _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_READ_A, REGISTER_MAR_ACTIVE_BITS);
                break;
            case REGISTER_MDR:
                _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_READ_A, REGISTER_MDR_ACTIVE_BITS);
                break;
            default:
                _ins = _inside_ins_nop_;
        }
            _inside_control_bus_ -> in(_ins);
            _outside_control_bus_ -> in(_outside_ins_nop_);
            _run_once();
   }

    void InstructionGeneratorBase::_memory_write_to_outside_bus() {
        unsigned long _ins = _outside_ins_nop_ | base::_generate_instruction(MEMORY_READ, MEMORY_ACTIVE_BITS);
        _inside_control_bus_ -> in(_inside_ins_nop_);
        _outside_control_bus_ -> in(_ins);
        _run_once();
    }

    void InstructionGeneratorBase::_memory_read_from_outside_bus() {
        unsigned long _ins = _outside_ins_nop_ | base::_generate_instruction(MEMORY_WRITE, MEMORY_ACTIVE_BITS);
        _inside_control_bus_ -> in(_inside_ins_nop_);
        _outside_control_bus_ -> in(_ins);
        _run_once();
    }

    void InstructionGeneratorBase::_mov_inside_bus_to_outside_address_bus() {
        //inside_bus to MAR
        _register_read_from_inside_bus(REGISTER_MAR);

        //MAR to outside_bus
        unsigned long _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_WRITE_B, REGISTER_MAR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();
    }
    
    void InstructionGeneratorBase::_mov_inside_bus_to_outside_data_bus() {
        //inside_bus to MDR
        _register_read_from_inside_bus(REGISTER_MDR);

        //MDR to outside_bus
        unsigned long _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_WRITE_B, REGISTER_MDR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();
    }

    void InstructionGeneratorBase::_mov_outside_bus_to_inside_bus() {
        //outside data bus -> MDR
        unsigned long _ins = _inside_ins_nop_ | base::_generate_instruction(MUTIL_REGISTER_READ_B, REGISTER_MDR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //MDR -> inside data bus
        _register_write_to_inside_bus(REGISTER_MDR);
    }

    void InstructionGeneratorBase::_load_instruction() {
        //load [PC] -> inside data bus
        _register_write_to_inside_bus(REGISTER_PC);
        _mov_inside_bus_to_outside_address_bus();
        _memory_write_to_outside_bus();
        _mov_outside_bus_to_inside_bus();
        //inside data bus -> IP
        _register_read_from_inside_bus(REGISTER_IP);
        //PC += 1
        _register_write_to_inside_bus(REGISTER_PC);
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _run_once();
        _inside_data_bus_ -> in(1);
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _run_once();
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_ARITHMETIC_ADD, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _run_once();
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _run_once();
        _register_read_from_inside_bus(REGISTER_PC);
    }

    void InstructionGeneratorBase::operator()() {
        //[PC++] -> IP
        _load_instruction();
        //IP -> mirco instruction
        _register_write_to_inside_bus(REGISTER_IP);
        unsigned long _ins = _inside_data_bus_ -> out();
        unsigned long _instruction_type = base::_extract_instruction(_ins, INSTRUCTION_TYPE);

        //instruction set
        switch (_instruction_type) {
            case INSTRUCTION_MOV:
                _MOV(_ins);
                break;
            case INSTRUCTION_ADD:
                _ADD(_ins);
                break;
            case INSTRUCTION_ZERO:
                _ZERO(_ins);
                break;
            case INSTRUCTION_LSFT:
                _LSFT(_ins);
                break;
            case INSTRUCTION_RSFT:
                _RSFT(_ins);
                break;
            case INSTRUCTION_AND:
                _AND(_ins);
                break;
            case INSTRUCTION_OR:
                _OR(_ins);
                break;
            case INSTRUCTION_NOT:
                _NOT(_ins);
                break;
            case INSTRUCTION_XOR:
                _XOR(_ins);
                break;
            case INSTRUCTION_CMP:
                _CMP(_ins);
                break;
            case INSTRUCTION_JMP:
                _JMP(_ins);
                break;
            case INSTRUCTION_JMPZ:
                _JMPZ(_ins);
                break;
            case INSTRUCTION_JMPP:
                _JMPP(_ins);
                break;
            case INSTRUCTION_JMPN:
                _JMPN(_ins);
                break;
            default:
                _NOP(_ins);
                break;
        }
    }

    void InstructionGeneratorBase::_NOP(unsigned long _ins) {
        return;
    }

    void InstructionGeneratorBase::_MOV(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> op2
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //DATA_BUS -> REG
            _register_read_from_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //inside data bus -> outside data bus
            _mov_inside_bus_to_outside_data_bus();
            _outside_address_bus_ -> in(_op_2_);
            _memory_read_from_outside_bus();
        }
    }

    void InstructionGeneratorBase::_ADD(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //op2 -> inside data bus
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_2_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector B
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //alu run add
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_ARITHMETIC_ADD, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor direct transform to inside data bus
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);
    }
    
    void InstructionGeneratorBase::_AND(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //op2 -> inside data bus
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_2_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector B
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //alu run and
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_LOGIC_AND, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor direct transform to inside data bus
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);
    }

    void InstructionGeneratorBase::_OR(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //op2 -> inside data bus
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_2_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector B
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //alu run or
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_LOGIC_OR, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor direct transform to inside data bus
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);

    }

    void InstructionGeneratorBase::_NOT(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        //unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        //unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        ////op2 -> inside data bus
        //if (_op_2_addr_type == ADDRESS_REGISTER) {
        //    //REG -> DATA_BUS
        //    _register_write_to_inside_bus(_op_2_);
        //} else if (_op_2_addr_type == ADDRESS_NUMBER) {
        //    //NUMBER -> DATA_BUS
        //    _inside_data_bus_ -> write(_op_2_);
        //} else if (_op_2_addr_type == ADDRESS_MEMORY) {
        //    //write address to outside address bus
        //    _outside_address_bus_ -> write(_op_2_);
        //    //memory -> outside data bus
        //    _memory_write_to_outside_bus();
        //    //outside data bus -> inside data bus
        //    _mov_outside_bus_to_inside_bus();
        //}

        ////inside data bus -> selector B
        //unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        //_inside_control_bus_ -> write(_ins_2);
        //_outside_control_bus_ -> write(_outside_ins_nop_);
        //_run_once();

        //alu run add
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_LOGIC_NOT, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor direct transform to inside data bus
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);
    }

    void InstructionGeneratorBase::_XOR(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //op2 -> inside data bus
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_2_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector B
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //alu run xor
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_LOGIC_XOR, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor direct transform to inside data bus
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);
    }

    void InstructionGeneratorBase::_ZERO(unsigned long _ins) {
        //先实现功能，后实现细节
        //计算PSW
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        
        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }
        //写psw
        if (_inside_data_bus_ -> out() == 0) {
            _inside_data_bus_ -> in(0 | PSW_ZERO);
        } else {
            _inside_data_bus_ -> in(0);
        }
        _register_read_from_inside_bus(REGISTER_PSW);
    }

    void InstructionGeneratorBase::_LSFT(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //op2 -> inside data bus
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_2_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector B
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //alu direct transform
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_DIRECT_TRANSMISSION, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor left shift
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_LEFT_SHIFT, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);
    }

    void InstructionGeneratorBase::_RSFT(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        unsigned long _op_2_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_2_ADDRESS_METHOD);
        unsigned long _op_2_ = base::_extract_instruction(_ins, OPERATE_NUMBER_2);

        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //op2 -> inside data bus
        if (_op_2_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_2_);
        } else if (_op_2_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_2_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector B
        unsigned long _ins_2 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_B_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_2);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //alu direct transform
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_DIRECT_TRANSMISSION, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor right shift
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_RIGHT_SHIFT, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside data bus -> register C
        _register_read_from_inside_bus(REGISTER_C);
    }

    void InstructionGeneratorBase::_CMP(unsigned long _ins) {
    }

    void InstructionGeneratorBase::_JMP(unsigned long _ins) {
        unsigned long _op_1_addr_type = base::_extract_instruction(_ins, OPERATE_NUMBER_1_ADDRESS_METHOD);
        unsigned long _op_1_ = base::_extract_instruction(_ins, OPERATE_NUMBER_1);
        
        //op1 -> inside data bus
        if (_op_1_addr_type == ADDRESS_REGISTER) {
            //REG -> DATA_BUS
            _register_write_to_inside_bus(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_NUMBER) {
            //NUMBER -> DATA_BUS
            _inside_data_bus_ -> in(_op_1_);
        } else if (_op_1_addr_type == ADDRESS_MEMORY) {
            //write address to outside address bus
            _outside_address_bus_ -> in(_op_1_);
            //memory -> outside data bus
            _memory_write_to_outside_bus();
            //outside data bus -> inside data bus
            _mov_outside_bus_to_inside_bus();
        }

        //inside data bus -> selector A
        unsigned long _ins_1 = _inside_ins_nop_ | base::_generate_instruction(SELECTOR_ROUTE_0, SELECTOR_A_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_1);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();
        
        //alu direct transform
        unsigned long _ins_3 = _inside_ins_nop_ | base::_generate_instruction(ALU_DIRECT_TRANSMISSION, ALU_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_3);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //shiftor direct transform
        unsigned long _ins_4 = _inside_ins_nop_ | base::_generate_instruction(SHIFTOR_DIRECT_TRANSMISSION, SHIFTOR_ACTIVE_BITS);
        _inside_control_bus_ -> in(_ins_4);
        _outside_control_bus_ -> in(_outside_ins_nop_);
        _run_once();

        //inside bus -> PC
        _register_read_from_inside_bus(REGISTER_PC);
    }

    void InstructionGeneratorBase::_JMPZ(unsigned long _ins) {
        _register_write_to_inside_bus(REGISTER_PSW);
        if (_inside_data_bus_ -> out() & PSW_ZERO) {
            _JMP(_ins);
        }
    }

    void InstructionGeneratorBase::_JMPN(unsigned long _ins) {
        _register_write_to_inside_bus(REGISTER_PSW);
        if (_inside_data_bus_ -> out() & PSW_NAGITIVE) {
            _JMP(_ins);
        }
    }

    void InstructionGeneratorBase::_JMPP(unsigned long _ins) {
        _register_write_to_inside_bus(REGISTER_PSW);
        if (_inside_data_bus_ -> out() & PSW_POSITIVE) {
            _JMP(_ins);
        }
    }

    void InstructionGeneratorBase::debug() {
        //_inside_control_bus_ -> debug("+---");
        //_inside_data_bus_ -> debug("+---");
        //_outside_address_bus_ -> debug("+---");
        //_outside_control_bus_ -> debug("+---");
        //_outside_data_bus_ -> debug("+---");

        //_CPU_ -> debug("+---");
        _R0_ -> debug("+---");
        _R1_ -> debug("+---");
        _R2_ -> debug("+---");
        _R3_ -> debug("+---");
        //_IP_ -> debug("+---");
        //_PC_ -> debug("+---");
        //_SP_ -> debug("+---");
        _C_ -> debug("+---");
        _D_ -> debug("+---");
        //_MAR_ -> debug("+---");
        //_MDR_ -> debug("+---");
        //_PSW_ -> debug("+---");
        //_memory_ -> debug(0, "+---");
    }
}