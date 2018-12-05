#include <iostream>
#include <string>

#include "bits.h"

using namespace std;

#ifndef __OPTIONS_H__
#define __OPTIONS_H__

/*global configure*/
#define GLOBAL_MAX_BITS_SIZE 64
#define DATA_BITS_SIZE 8            //数据位宽
#define CONTROL_BUS_BITS_WIDTH 13   //控制总线宽度
#define CPU_INSIDE_BUS_BITS_WIDTH DATA_BITS_SIZE   //CPU内总线位宽度

/*active bits configure*/
#define SELECTOR_A_INSTRUCTION_ACTIVE_BITS      0b1111000000000 //选择器A有效位
#define SELECTOR_B_INSTRUCTION_ACTIVE_BITS      0b0000111100000 //选择器B有效位
#define ALU_INSTRUCTION_ACTIVE_BITS             0b0000000011100 //ALU有效位
#define SHIFTOR_INSTRUCTION_ACTIVE_BITS         0b0000000000011 //移位器有效位

/*mirco instruction format*/
#define COMMON_REGISTER_0_INSTRUCTION_OFFSET 0 //2bit
#define COMMON_REGISTER_1_INSTRUCTION_OFFSET 2 //2bit
#define COMMON_REGISTER_2_INSTRUCTION_OFFSET 4 //2bit
#define COMMON_REGISTER_3_INSTRUCTION_OFFSET 6 //2bit
#define SELECTOR_A_INSTRUCTION_OFFSET 8 //4bit
#define SELECTOR_B_INSTRUCTION_OFFSET 12 //4bit
#define ALU_INSTRUCTION_OFFSET 16//3bit
#define SHIFTOR_INSTRUCTION_OFFSET 19//2bit
/*total 21bits*/

/*data width*/
#define BUS_BITS_SIZE DATA_BITS_SIZE
#define REGISTER_BITS_SIZE DATA_BITS_SIZE

/*instruction width*/
#define REGISTER_INSTRUCTION_BITS_SIZE 2
#define SELECTOR_INSTRUCTION_BITS_SIZE 4
#define ALU_INSTRUCTION_BITS_SIZE 3
#define SHIFTOR_INSTRUCTION_BITS_SIZE 2

#endif
