#include "cpu.h"
#include "base/bus.h"
#include "base/register.h"
#include "instruction_generator.h"

#include "base/options.h"

//微型计算机
class ComputerBase {
    public:
        ComputerBase();
        ~ComputerBase();

        //读取代码文件，编译代码
        void run();

        //执行单条汇编代码
        void step_run();
        //执行单条微指令
        void mirco_step_run();
        //输出当前的寄存器等数据
        void debug();

    private:
        compute::InstructionGeneratorBase* _instruction_generator_;
};
