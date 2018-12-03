#include "cpu.h"
#include "base/bus.h"
#include "base/register.h"
#include "base/distributor.h"

#include "base/options.h"

class ComputerBase {
    public:
        ComputerBase();
        ~ComputerBase();

        virtual void run();
        virtual void step_run();
        virtual void mirco_step_run();
        virtual void debug();

    private:
        compute::CPU* _cpu_;
        
        base::RegisterBase* _R0_;
        base::RegisterBase* _R1_;
        base::RegisterBase* _R2_;
        base::RegisterBase* _R3_;
        base::RegisterBase* _IP_;
        base::RegisterBase* _PC_;
        base::RegisterBase* _SP_;
        base::RegisterBase* _C_;
        base::RegisterBase* _D_;
        base::RegisterBase* _MAR_;
        base::RegisterBase* _MDR_;
        base::RegisterBase* _PSW_;

        base::BusBase* _inside_cpu_out_bus_;
        base::BusBase* _inside_cpu_in_bus_A_;
        base::BusBase* _inside_cpu_in_bus_B_;
        base::BusBase* _inside_control_bus_;

        base::BusBase* _outside_address_bus_;
        base::BusBase* _outside_data_bus_;
        base::BusBase* _outside_control_;
};
