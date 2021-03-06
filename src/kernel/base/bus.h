#ifndef __BUS_H__
#define __BUS_H__

#include <string>
using std::string;

#include "bits.h"

//总线类，用于连接两个部件，部件之间不能直接通讯，必须通过总线，其中总线采用被动
//传输数据，一方主动写入，另一方如果没有读取该数据则数据不会被使用，另外，总线传
//输的数据在下个周期才能被使用，即，当数据需要从逻辑部件A传输到逻辑部件B需要消耗
//一个周期
namespace base {
    class BusBase {
        public:
            //构造函数，传入总线宽度,实际值
            BusBase(unsigned long _width_);
            ~BusBase();

            //一端写入
            void in(unsigned long _data_);
            //一端读取
            unsigned long out();

            //调试函数，输出当前总线环境数据
            void debug(string prefix = "");
            //总线命名函数，可以定义总线名称，用于调试定位
            void named(string _name_);
            //返回总线宽度
            unsigned long width();
            //返回总线名称
            string name();

        private:
            //总线数据
            unsigned long  _bus_data_;
            //总线宽度
            unsigned long _bus_width_;

            string _bus_name_;
    };
}

#endif
