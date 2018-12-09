#ifndef __OPTIONS_H__
#define __OPTIONS_H__
#include <iostream>
#include <string>

using namespace std;

#define DATA_BITS_WIDTH                 (unsigned long)32   //数据宽度
#define INSIDE_CONTROL_BITS_WIDTH       (unsigned long)39 //内控制总线宽度
#define OUTSIDE_ADDRESS_BITS_WIDTH      (unsigned long)12 //外地址总线宽度
#define OUTSIDE_DATA_BITS_WIDTH         (unsigned long)32 //外数据总线宽度
#define OUTSIZE_CONTROL_BITS_WIDTH      (unsigned long)2 //外控制总线宽度
#define MEMORY_UNIT_BITS_SIZE           (unsigned long)32    //存储单元大小
#define INSTRUCTION_BITS_WIDTH          (unsigned long)32   //指令长度

//内控制总线指令有效位定义
#define SHIFTOR_ACTIVE_BITS             (unsigned long)0b110000000000000000000000000000000000000
#define ALU_ACTIVE_BITS                 (unsigned long)0b001110000000000000000000000000000000000
#define SELECTOR_A_ACTIVE_BITS          (unsigned long)0b000001111000000000000000000000000000000
#define SELECTOR_B_ACTIVE_BITS          (unsigned long)0b000000000111100000000000000000000000000
#define REGISTER_0_ACTIVE_BITS          (unsigned long)0b000000000000011000000000000000000000000
#define REGISTER_1_ACTIVE_BITS          (unsigned long)0b000000000000000110000000000000000000000
#define REGISTER_2_ACTIVE_BITS          (unsigned long)0b000000000000000001100000000000000000000
#define REGISTER_3_ACTIVE_BITS          (unsigned long)0b000000000000000000011000000000000000000
#define REGISTER_IP_ACTIVE_BITS         (unsigned long)0b000000000000000000000110000000000000000
#define REGISTER_PC_ACTIVE_BITS         (unsigned long)0b000000000000000000000001100000000000000
#define REGISTER_SP_ACTIVE_BITS         (unsigned long)0b000000000000000000000000011000000000000
#define REGISTER_PSW_ACTIVE_BITS        (unsigned long)0b000000000000000000000000000110000000000
#define REGISTER_C_ACTIVE_BITS          (unsigned long)0b000000000000000000000000000001100000000
#define REGISTER_D_ACTIVE_BITS          (unsigned long)0b000000000000000000000000000000011000000
#define REGISTER_MAR_ACTIVE_BITS        (unsigned long)0b000000000000000000000000000000000111000
#define REGISTER_MDR_ACTIVE_BITS        (unsigned long)0b000000000000000000000000000000000000111

//外控制总线指令有效位定义
#define MEMORY_ACTIVE_BITS              (unsigned long)0b11

//指令集
#define INSTRUCTION_NOP                 (unsigned long)0b0000
#define INSTRUCTION_MOV                 (unsigned long)0b0001
#define INSTRUCTION_ADD                 (unsigned long)0b0010
#define INSTRUCTION_ZERO                (unsigned long)0b0011
#define INSTRUCTION_LSFT                (unsigned long)0b0100
#define INSTRUCTION_RSFT                (unsigned long)0b0101
#define INSTRUCTION_AND                 (unsigned long)0b0110
#define INSTRUCTION_OR                  (unsigned long)0b0111
#define INSTRUCTION_NOT                 (unsigned long)0b1000
#define INSTRUCTION_XOR                 (unsigned long)0b1001
#define INSTRUCTION_CMP                 (unsigned long)0b1010
#define INSTRUCTION_JMP                 (unsigned long)0b1011
#define INSTRUCTION_JMPP                (unsigned long)0b1100
#define INSTRUCTION_JMPN                (unsigned long)0b1101
#define INSTRUCTION_JMPZ                (unsigned long)0b1110
#define INSTRUCTION_CONTAIN             (unsigned long)0b1111

//寻址方式
#define ADDRESS_REGISTER                (unsigned long)0b00
#define ADDRESS_NUMBER                  (unsigned long)0b01
#define ADDRESS_MEMORY                  (unsigned long)0b10
#define ADDRESS_CONTAIN                 (unsigned long)0b11

//指令有效位
#define INSTRUCTION_TYPE                    (unsigned long)0b11110000000000000000000000000000
#define OPERATE_NUMBER_1_ADDRESS_METHOD     (unsigned long)0b00001100000000000000000000000000
#define OPERATE_NUMBER_1                    (unsigned long)0b00000011111111111100000000000000
#define OPERATE_NUMBER_2_ADDRESS_METHOD     (unsigned long)0b00000000000000000011000000000000
#define OPERATE_NUMBER_2                    (unsigned long)0b00000000000000000000111111111111

//寄存器编号
#define REGISTER_0      (unsigned long)0b000000000000
#define REGISTER_1      (unsigned long)0b000000000001
#define REGISTER_2      (unsigned long)0b000000000010
#define REGISTER_3      (unsigned long)0b000000000011
#define REGISTER_IP     (unsigned long)0b000000000100
#define REGISTER_PC     (unsigned long)0b000000000101
#define REGISTER_SP     (unsigned long)0b000000000110
#define REGISTER_C      (unsigned long)0b000000000111
#define REGISTER_D      (unsigned long)0b000000001000
#define REGISTER_MAR    (unsigned long)0b000000001001
#define REGISTER_MDR    (unsigned long)0b000000001010
#define REGISTER_PSW    (unsigned long)0b000000001011

//PSW有效位
#define PSW_POSITIVE        (unsigned long)0b0000000000000001
#define PSW_NAGITIVE        (unsigned long)0b0000000000000010
#define PSW_ZERO            (unsigned long)0b0000000000000100
#define PSW_ODD             (unsigned long)0b0000000000001000
#define PSW_EVEN            (unsigned long)0b0000000000010000
#define PSW_OVERFLOW        (unsigned long)0b0000000000100000


#endif