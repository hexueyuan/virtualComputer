#include "base/bus.h"
#include "base/options.h"

#define MEMORY_INSTRUCTION_BITS_SIZE 2
#define MEMORY_READ 0b10
#define MEMORY_WRITE 0b11
#define MEMORY_NOT_ENABLE 0b00
#define MEMORY_CONTAIN 0b01

//存储器主类
//可以被继承并生成各种存储设备
//指令长度2位
namespace compute {
    class MemoryBase {
        public:
            //构造函数
            //输入：_input_ 数据输入总线
            //      _output_ 数据输出总线
            //      _control_ 控制总线
            //      _addr_ 地址选择总线
            //      _unit_bsize 存储单元字长 由于使用unsigned long来mock的，所以最大支持64位, 也就是8bytes
            //      _addr_bits_width 地址宽度 存储器空间 = 存储单元字长 * 存储单元数量 = 存储单元字长 * (2 ^ 地址宽度)
            //      _mem_active_bits 有效指令位
            MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                        base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits);
            ~MemoryBase();

            //执行一次当前控制总线上的指令
            void operator()();

            //命名
            void named(string _name);
            //调试
            void debug(string prefix = "");

        private:
            base::BusBase* _input_data_bus_;
            base::BusBase* _output_data_bus_;
            base::BusBase* _address_bus_;
            base::BusBase* _control_bus_;
            unsigned long _instruction_;
            unsigned long _memory_active_bits_;

            unsigned long _memory_unit_bits_size_;
            unsigned long _memory_addr_bits_width_;
            unsigned long* _memory_;

            string _name_;

            void _write();
            void _read();
    };

    MemoryBase::MemoryBase(base::BusBase* _input_, base::BusBase* _output_, base::BusBase* _control_, 
                            base::BusBase* _addr_, unsigned long _unit_bsize, unsigned long _addr_bits_width, unsigned long _mem_active_bits) {
        _input_data_bus_ = _input_;
        _output_data_bus_ = _output_;
        _control_bus_ = _control_;
        _address_bus_ = _addr_;
        _memory_unit_bits_size_ = _unit_bsize;
        _memory_addr_bits_width_ = _addr_bits_width;
        _memory_ = new unsigned long[(unsigned long)1 << _addr_bits_width];
        _memory_active_bits_ = _mem_active_bits;
    }

    MemoryBase::~MemoryBase() {}

    void MemoryBase::_write() {
        if (_address_bus_ -> read() < ((unsigned long)1 << _memory_addr_bits_width_)) {
            _memory_[_address_bus_ -> read()] = (_input_data_bus_ -> read()) & (((unsigned long)1 << _memory_unit_bits_size_) - 1);
        }
    }

    void MemoryBase::_read() {
        if (_address_bus_ -> read() < ((unsigned long)1 << _memory_addr_bits_width_)) {
            _output_data_bus_ -> write(_memory_[_address_bus_ -> read()]);
        }
    }

    void MemoryBase::operator()() {
        _instruction_ = base::_extract_instruction(_control_bus_ -> read(), _memory_active_bits_);

        switch (_instruction_) {
            case MEMORY_READ:
                _read();
                break;
            case MEMORY_WRITE:
                _write();
                break;
            case MEMORY_NOT_ENABLE:
                break;
            default:
                break;
        }
    }

    void MemoryBase::named(string _name) {
        _name_ = _name;
    }

    void MemoryBase::debug(string prefix) {
        string space(prefix.length(), ' ');

        cout << "Memory: " << _name_ << endl;
        for (unsigned long i = 0; i < (1 << _memory_addr_bits_width_); ++i) {
            cout << space << base::_bin_str(i, _memory_addr_bits_width_) << ": " << base::_bin_str(_memory_[i], _memory_unit_bits_size_) << endl;
        }
        cout << space << "Memory(" << _name_ << ") data in bus: " << _input_data_bus_ -> name() << endl;
        cout << space << "Memory(" << _name_ << ") data out bus: " << _output_data_bus_ -> name() << endl;
        cout << prefix << "Memory(" << _name_ << ") control bus: " << _control_bus_ -> name() << endl;
    }
}
