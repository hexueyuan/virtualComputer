#include "options.h"
#include "bus.h"

//双路分支器
//解决一些多接口多模块问题，在总线上增加集成器，使总线数据可以被拷贝到另一个总线上
//实现信号分支

//                             | ---> (data)
// (data)--------->|distributor|
//                             | ---> (data)
//

#ifndef __DISTRIBUTOR_H__
#define __DISTRIBUTOR_H__

namespace base {
    //双路分支
    class Distributor {
        public:
            Distributor(BusBase* _in_, BusBase* _out_A_, BusBase* _out_B_);
            ~Distributor();

            void operator()();
            void debug();

        private:
            BusBase* _input_;
            BusBase* _output_A_;
            BusBase* _output_B_;
    };

    Distributor::Distributor(BusBase* _in_, BusBase* _out_A_, BusBase* _out_B_) {
        _input_ = _in_;
        _output_A_ = _out_A_;
        _output_B_ = _out_B_;
    }

    Distributor::~Distributor() {}

    void Distributor::operator()() {
        _output_A_ -> _write(_input_ -> _read());
        _output_B_ -> _write(_input_ -> _read());
    }

    void Distributor::debug() {
        cout << "Distributor input bus: " << bitset<sizeof(unsigned long) * 8>(_input_ -> _read()) << endl;
        cout << "Distributor output bus A: " << bitset<sizeof(unsigned long) * 8>(_output_A_ -> _read()) << endl;
        cout << "Distributor output bus B: " << bitset<sizeof(unsigned long) * 8>(_output_B_ -> _read()) << endl;
    }
}

#endif
