/************************************************
*汇编指令汇编成机器指令
*使用instruction_generation.cpp中定义的指令集
*************************************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdio>

#include <unistd.h>

#include "getopt.h"

#include "instruction_generator.h"
#include "base/bits.h"

using namespace std;

map<string, unsigned long> _ins_type_map;
map<string, unsigned long> _register_map;
bool _fatal = false;

//十进制数字转换
bool isNumber(string _str) {
    int _size = _str.length();
    for (int i = 0; i < _size; ++i) {
        if (_str[i] < '0' || _str[i] > '9') {
            return false;
        }
    }
    return true;
}

//字符串转数字，溢出前返回
//最大64位
unsigned long _str_number_(string _str) {
    unsigned long _num;
    int _size = _str.length();
    for (int i = 0; i < _size; ++i) {
        unsigned long _tmp = _num * 10 + (_str[i] - '0');
        if ((_tmp / 10) == _num) {
            _num = _tmp;
        } else {
            break;
        }
    }
    return _num;
}

//数字转字符串
string _number_str(int _num) {
    string _str;
    int _div = 1;
    while (_num / (10 * _div)) _div *= 10;
    while (_div != 0) {
        _str += (_num / _div) + '0';
        _num %= _div;
        _div /= 10;
    }
    return _str;
}

//检测文件是否存在
bool isExist(const string& name) {
    return access(name.c_str(), F_OK) != -1;
}

//删除文件
bool removeFile(const string& name) {
    if (isExist(name)) {
        return remove(name.c_str()) == 0;
    } else {
        return true;
    }
}

//[xxx]
bool isMemoryAddress(string _str) {
    int _size = _str.length();
    for (int i = 1; i < _size - 1; ++i) {
        
    }
    return _str[0] == '[' && _str[_str.length() - 1] == ']';
}

void _error(string _err) {
    cout << "\033[41mError\033[0m: " << _err << endl;
}

void _warn(string _war) {
    cout << "\033[45mWarning\033[0m: " << _war << endl;
}

//初始化指令映射字典和寄存器映射字典
void _init() {
    _ins_type_map["NOP"]  = INSTRUCTION_NOP;
    _ins_type_map["MOV"]  = INSTRUCTION_MOV;
    _ins_type_map["ADD"]  = INSTRUCTION_ADD;
    _ins_type_map["ZERO"] = INSTRUCTION_ZERO;
    _ins_type_map["LSFT"] = INSTRUCTION_LSFT;
    _ins_type_map["RSFT"] = INSTRUCTION_RSFT;
    _ins_type_map["AND"]  = INSTRUCTION_AND;
    _ins_type_map["OR"]   = INSTRUCTION_OR;
    _ins_type_map["NOT"]  = INSTRUCTION_NOT;
    _ins_type_map["XOR"]  = INSTRUCTION_XOR;
    _ins_type_map["CMP"]  = INSTRUCTION_CMP;
    _ins_type_map["JMP"]  = INSTRUCTION_JMP;
    _ins_type_map["JMPZ"] = INSTRUCTION_JMPZ;
    _ins_type_map["JMPP"] = INSTRUCTION_JMPP;
    _ins_type_map["JMPN"] = INSTRUCTION_JMPN;

    _register_map["R0"]   = REGISTER_0;
    _register_map["R1"]   = REGISTER_1;
    _register_map["R2"]   = REGISTER_2;
    _register_map["R3"]   = REGISTER_3;
    _register_map["IP"]   = REGISTER_IP;
    _register_map["PC"]   = REGISTER_PC;
    _register_map["SP"]   = REGISTER_SP;
    _register_map["C"]    = REGISTER_C;
    _register_map["D"]    = REGISTER_D;
    _register_map["PSW"]  = REGISTER_PSW;
    _register_map["MAR"]  = REGISTER_MAR;
    _register_map["MDR"]  = REGISTER_MDR;
}

string asmcode(string asmins, int __line__) {
    stringstream code_sentence(asmins);
    string ins, op1, op2;
    code_sentence >> ins >> op1 >> op2;

    unsigned long _ins_type = 0;
    unsigned long _op1_type = 0;
    unsigned long _op2_type = 0;
    unsigned long _op1_value = 0;
    unsigned long _op2_value = 0;

    if (_ins_type_map.find(ins) != _ins_type_map.end()) {
        _ins_type = _ins_type_map[ins];
    } else {
        _error(string("Invalid instruction `") + ins + string("` in ") + _number_str(__line__) + string(" line."));
        _fatal = true;
        return "";
    }

    if (isNumber(op1)) {
        _op1_type = ADDRESS_NUMBER;
        _op1_value = atoi(op1.c_str());
    } else if (_register_map.find(op1) != _register_map.end()) {
        _op1_type = ADDRESS_REGISTER;
        _op1_value = _register_map[op1];
    } else if (isMemoryAddress(op1)) {
        _op1_type = ADDRESS_MEMORY;
        _op1_value = _str_number_(op1.substr(1, op1.length() - 2));
    } else {
        _error(string("Invalid operate of `") + op1 + string("` in ") + _number_str(__line__) + " line.");
        _fatal = true;
        return "";
    }
    
    if (isNumber(op2)) {
        _op2_type = ADDRESS_NUMBER;
        _op2_value = atoi(op2.c_str());
    } else if (_register_map.find(op2) != _register_map.end()) {
        _op2_type = ADDRESS_REGISTER;
        _op2_value = _register_map[op2];
    } else if (isMemoryAddress(op2)) {
        _op2_type = ADDRESS_MEMORY;
        _op2_value = _str_number_(op2.substr(1, op2.length() - 2));
    } else {
        _error(string("Invalid operate of `") + op2 + string("` in ") + _number_str(__line__) + " line.");
        _fatal = true;
        return "";
    }

    unsigned long _ins = (base::_generate_instruction(_ins_type, INSTRUCTION_TYPE) |
                        base::_generate_instruction(_op1_type, OPERATE_NUMBER_1_ADDRESS_METHOD) |
                        base::_generate_instruction(_op1_value, OPERATE_NUMBER_1) |
                        base::_generate_instruction(_op2_type, OPERATE_NUMBER_2_ADDRESS_METHOD) |
                        base::_generate_instruction(_op2_value, OPERATE_NUMBER_2));
    return base::_bin_str(_ins, INSTRUCTION_BITS_WIDTH);
}

void asmfile(string _src, string _obj) {
    if (!isExist(_src)) {
        _error("file not found.");
        return;
    }
    if (isExist(_obj)) {
        _warn("Out file overwrite.");
    }
    ifstream _in(_src.c_str());
    ofstream _out(_obj.c_str());
    string _ins;
    int __line__ = 0;
    while (getline(_in, _ins)) {
        __line__ += 1;
        string _code = asmcode(_ins, __line__);
        if (!_fatal) {
            _out << _code << endl;
        } else {
            _in.close();
            _out.close();
            removeFile(_obj);
            return;
        }
    }
    _in.close();
    _out.close();
    return;
}


int main(int argc, char** argv) {
    if (argc < 2) {
        cout << "No input" << endl;
        return 0;
    }
    _init();
    string input_file_path(argv[1]);
    string output_file_path(argv[2]);
    asmfile(input_file_path, output_file_path);

    return 0;
}
