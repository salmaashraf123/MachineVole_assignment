#ifndef PROGRAMMING_A1_TASK4_S27_20231174_S8_20231073_S6_20231180_H
#define PROGRAMMING_A1_TASK4_S27_20231174_S8_20231073_S6_20231180_H

#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Register {
private:
    vector<string> reg;
public:
    Register();
    void setRegister(int address, string value);
    string getRegister(int address);
    void printRegisters();
    void clear();
};

class Memory {
private:
    vector<string> memo;
public:
    Memory();
    string rd(int index);
    void wr(int index, string val);
    void printMemory();
    void clear();
};

class Cu {
public:
    void load(int idxreg, int intmem, Register &reg, Memory &Mem);
    void load(int idxreg, string val, Register &reg);
    void store(int idxreg, int idxmem, Register &reg, Memory &Mem);
    void move(int idxreg1, int idxreg2, Register &reg);
    void jump(int idxreg, int idxmem, Register &reg, int &pc);
    void store_3(int idxreg, Register &reg, Memory &Mem);
    string binaryToHex(const string& bin);
    string hexToBinary(const string& hexx);
    void rotate(int idxreg, int step, Register &reg);
    void Jmuped(string hex1, string hex2, int &pc, int xy);
};

class ALU {
public:
    string hexToBinary(const string& hexx);
    string binaryToHex(const string& bin);
    string Two_complement(string hex1, string hex2);
    int binaryToInt(const string& binaryString);
    string intToBinary(int num);
    string Floating_point(string hex1, string hex2);
    string and_gate(string s1, string s2);
    string OR_gate(string s1, string s2);
    string XOR_gate(string s1, string s2);
};

class cpu {
public:
    int pc;
    string IR;
    Register register_;
    Cu cu;
    ALU alu;
    cpu();
    void fetch(Memory &Mem);
    vector<int> decode();
    void execute(Memory &Mem);
    void clear ();
};

class mainUI {
private:
    Memory memory;
    Register register2;
public:
    string filename;
    char choice;
    void menu();
    void loadfile(cpu &processor);
    char choiceInput();
    void runStepByStep(cpu &processor);
    void runWhole(cpu &processor);
    void run(cpu &processor);
};


class A1_Task4_S27_20231174_S8_20231073_S6_20231180 {
public:
    mainUI mainUI;
    cpu processor;
    Memory memory;
    Register reg;
};


#endif //PROGRAMMING_A1_TASK4_S27_20231174_S8_20231073_S6_20231180_H
