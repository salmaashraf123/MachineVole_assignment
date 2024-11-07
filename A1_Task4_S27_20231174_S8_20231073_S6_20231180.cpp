#include "A1_Task4_S27_20231174_S8_20231073_S6_20231180.h"
#include<cmath>
#include<bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

Register::Register() : reg(16, "00") {}

void Register::setRegister(int address, string value) {
    reg[address] = value;
}

string Register::getRegister(int address) {
    return reg[address];
}

void Register::printRegisters() {
    for (int i = 0; i < 16; i++) {
        cout << "Register " << i << ": " << reg[i] << endl;
    }
}

void Register::clear()
{
    fill(reg.begin(), reg.end(), "00");
}

Memory::Memory() : memo(256, "00") {}

string Memory::rd(int index) {
    return memo[index];
}

void Memory::wr(int index, string val) {
    memo[index] = val;
}

void Memory::printMemory() {
    for (int i = 0; i < 256; i++) {
        if (i % 16 == 0 && i != 0) {
            cout << endl;
        }
        cout << memo[i];
        if (i % 16 != 15) {
            cout << " , ";
        }
    }
    cout << endl;
}

void Memory::clear()
{
    fill(memo.begin(), memo.end(), "00");
}


void Cu::load(int idxreg, int intmem, Register &reg, Memory &Mem) {
    reg.setRegister(idxreg, Mem.rd(intmem));
}

void Cu::load(int idxreg, string val, Register &reg) {
    reg.setRegister(idxreg, val);
}

void Cu::store(int idxreg, int idxmem, Register &reg, Memory &Mem) {
    Mem.wr(idxmem, reg.getRegister(idxreg));
}

void Cu::move(int idxreg1, int idxreg2, Register &reg) {
    reg.setRegister(idxreg2, reg.getRegister(idxreg1));
}

void Cu::jump(int idxreg, int idxmem, Register &reg, int &pc)
{
    int reg_dec = stoi(reg.getRegister(idxreg), nullptr, 16);
    int reg2_dec = stoi(reg.getRegister(0), nullptr, 16);
    if (reg_dec == reg2_dec)
    {
        pc = idxmem;
    }
}

void Cu::store_3(int idxreg, Register &reg, Memory &Mem) {
    Mem.wr(0, reg.getRegister(idxreg));
    string hx = Mem.rd(0);
    int print = stoi(Mem.rd(0), nullptr, 16);
    cout << "ASCII -->"  << char(print) <<"," << "Hexa -->" <<hx<<   endl;
}

string Cu::binaryToHex(const string& bin) {
    stringstream hexx;
    hexx << hex << uppercase;
    for (size_t i = 0; i < bin.size(); i += 4) {
        string ss = bin.substr(i, 4);
        hexx << hex << stoi(ss, nullptr, 2);
    }
    return hexx.str();
}

string Cu::hexToBinary(const string& hexx) {
    string binary = "";
    for (char Digit : hexx) {
        int deci_Value;
        if (Digit >= '0' && Digit <= '9') {
            deci_Value = Digit - '0';
        } else if (Digit >= 'A' && Digit <= 'F') {
            deci_Value = Digit - 'A' + 10;
        } else if (Digit >= 'a' && Digit <= 'f') {
            deci_Value = Digit - 'a' + 10;
        }
        binary += bitset<4>(deci_Value).to_string();
    }
    return binary;
}

void Cu::rotate(int idxreg, int step, Register &reg) {
    string s = reg.getRegister(idxreg);
    string s_bin = hexToBinary(s);
    step = step % s_bin.size();
    while (step--) {
        s_bin = s_bin[s_bin.size() - 1] + s_bin.substr(0, s_bin.size() - 1);
    }
    string s_hexa = binaryToHex(s_bin);
    reg.setRegister(idxreg, s_hexa);
}

void Cu::Jmuped(string hex1, string hex2, int &pc, int xy) {
    string bin1 = hexToBinary(hex1);
    string bin2 = hexToBinary(hex2);
    if (bin1[0] == '1' && bin2[0] == '0') {
        return;
    } else if (bin1[0] == '0' && bin2[0] == '1') {
        pc = xy;
    } else {
        for (int i = 0; i < bin1.size(); i++) {
            if (bin1[i] > bin2[i]) {
                pc = xy;
                break;
            } else if (bin1[i] < bin2[i]) {
                break;
            }
        }
    }
}


string ALU::hexToBinary(const string& hexx) {
    string binary = "";
    for (char Digit : hexx) {
        int deci_Value;
        if (Digit >= '0' && Digit <= '9') {
            deci_Value = Digit - '0';
        } else if (Digit >= 'A' && Digit <= 'F') {
            deci_Value = Digit - 'A' + 10;
        } else if (Digit >= 'a' && Digit <= 'f') {
            deci_Value = Digit - 'a' + 10;
        }
        binary += bitset<4>(deci_Value).to_string();
    }
    return binary;
}

string ALU::binaryToHex(const string& bin) {
    stringstream hexx;
    hexx << hex << uppercase;
    for (size_t i = 0; i < bin.size(); i += 4) {
        string ss = bin.substr(i, 4);
        hexx << hex << stoi(ss, nullptr, 2);
    }
    return hexx.str();
}

string ALU::Two_complement(string hex1, string hex2) {
    string bin1 = hexToBinary(hex1);
    string bin2 = hexToBinary(hex2);
    int Length = max(bin1.length(), bin2.length());
    string b1 = string(Length - bin1.length(), '0') + bin1;
    string b2 = string(Length - bin2.length(), '0') + bin2;
    string result = "";
    int carry = 0;
    for (int i = Length - 1; i >= 0; --i) {
        int bit1 = b1[i] - '0';
        int bit2 = b2[i] - '0';
        int sum = bit1 + bit2 + carry;
        result = char((sum % 2) + '0') + result;
        carry = sum / 2;
    }
    if (carry == 1) {
        result = '1' + result;
    }
    if(result.size() > 8) {
        result = result.substr(result.size() -8);
    }
    result = binaryToHex(result);
    return result;
}

int ALU::binaryToInt(const string& binaryString) {
    int result = 0;
    int length = binaryString.length();
    for (int i = 0; i < length; i++) {
        if (binaryString[i] == '1') {
            result += pow(2, length - 1 - i);
        }
    }
    return result;
}

string ALU::intToBinary(int num) {
    if (num == 0) {
        return "0";
    }
    string binary = "";
    while (num > 0) {
        binary = to_string(num % 2) + binary;
        num /= 2;
    }
    return binary;
}

string ALU::Floating_point(string hex1, string hex2) {
    string bin1 = hexToBinary(hex1);
    string bin2 = hexToBinary(hex2);
    int sign1 = pow(-1, bin1[0]);
    int sign2 = pow(-1, bin2[0]);
    int exponent1 = binaryToInt(bin1.substr(1, 3));
    int exponent2 = binaryToInt(bin2.substr(1, 3));
    int mantissa1 = binaryToInt(bin1.substr(4, bin1.length()));
    int mantissa2 = binaryToInt(bin2.substr(4, bin2.length()));
    float float_Val1 = (mantissa1 / 16.0) * pow(2, exponent1 - 4) * (sign1);
    float float_Val2 = (mantissa2 / 16.0) * pow(2, exponent2 - 4) * (sign2);
    float res = float_Val1 + float_Val2;
    float num2 = abs(res) - abs(int(res));
    int num1 = abs(int(res));
    string res1 = "", res2 = "";
    string total = "";
    if (res < 0.0) {
        total += "1";
    } else {
        total += "0";
    }
    while (num1) {
        res1 += to_string((num1 % 2));
        num1 /= 2;
    }
    reverse(res1.begin(), res1.end());
    while (num2 != 0) {
        res2 += to_string(int(num2 * 2));
        num2 = (num2 * 2) - int(num2 * 2);
    }
    string Tot_exponent = intToBinary((res1.size()) + 4);
    if (res1 == "") {
        res1 = "0";
    }
    if(res2 == "") {
        res2 = "0";
    }
    string Tot_mantissa = res1 + res2 ;
    total += Tot_exponent + Tot_mantissa;
    string total1 = total.substr(0, 4);
    string total2 = total.substr(4);
    if (total2.size() > 4) {
        total2 = total2.substr(total2.size() - 4, 4);
    }
    string Final_res = binaryToHex(total1) + binaryToHex(total2);
    return Final_res;
}

string ALU::and_gate(string s1, string s2) {
    s1 = hexToBinary(s1);
    s2 = hexToBinary(s2);
    string result = "";
    for (int i = max(s1.length(), s2.length()) - 1; i >= 0; i--) {
        if (s1[i] == '0' || s2[i] == '0') {
            result += "0";
        } else {
            result += "1";
        }
    }
    reverse(result.begin(), result.end());
    return binaryToHex(result);
}

string ALU::OR_gate(string s1, string s2) {
    s1 = hexToBinary(s1);
    s2 = hexToBinary(s2);
    cout << s1 << endl;
    cout << s2 << endl;
    string result = "";
    for (int i = max(s1.length(), s2.length()) - 1; i >= 0; i--) {
        if (s1[i] == '1' || s2[i] == '1') {
            result += "1";
        } else {
            result += "0";
        }
    }
    reverse(result.begin(), result.end());
    return binaryToHex(result);
}

string ALU::XOR_gate(string s1, string s2) {
    s1 = hexToBinary(s1);
    s2 = hexToBinary(s2);
    string result = "";
    for (int i = max(s1.length(), s2.length()) - 1; i >= 0; i--) {
        result += to_string(int(s1[i]) ^ int(s2[i]));
    }
    reverse(result.begin(), result.end());
    return binaryToHex(result);
}


cpu::cpu() : pc(10), IR("") {}

void cpu::fetch(Memory &Mem) {
    IR = Mem.rd(pc) + Mem.rd(pc + 1);
    pc += 2;
}

vector<int> cpu::decode() {
    if (IR.length() < 4) {
        cout << "Error: Instruction too short: " << IR << endl;
        return {};
    }

    char opCode = IR[0];
    int r = stoi(IR.substr(1, 1), nullptr, 16);
    int x = stoi(IR.substr(2, 1), nullptr, 16);
    int y = stoi(IR.substr(3, 1), nullptr, 16);
    int xy = stoi(IR.substr(2, 2), nullptr, 16);
    int R = stoi(IR.substr(2, 1), nullptr, 16);
    int S = stoi(IR.substr(3, 1), nullptr, 16);
    return { opCode, r, x, y, xy, R, S };
}

void cpu::execute(Memory &Mem) {
    vector<int> decoded = decode();
    if (decoded.empty()) return;

    char opCode = decoded[0];
    int r = decoded[1];
    int x = decoded[2];
    int y = decoded[3];
    int xy = decoded[4];
    int R = decoded[5];
    int S = decoded[6];

    string add, add2, string_or, string_and, string_xor;

    switch (opCode) {
        case '1':
            cu.load(r, xy, register_, Mem);
            break;
        case '2':
            cu.load(r, IR.substr(2, 2), register_);
            break;
        case '3':
            if (xy == 0) {
                cu.store_3(r, register_, Mem);
            } else {
                cu.store(r, xy, register_, Mem);
            }
            break;
        case '4':
            cu.move(R, S, register_);
            break;
        case '5':
            add = alu.Two_complement(register_.getRegister(x), register_.getRegister(y));
            register_.setRegister(r, add);
            break;
        case '6':
            add2 = alu.Floating_point(register_.getRegister(x), register_.getRegister(y));
            register_.setRegister(r, add2);
            break;
        case '7':
            string_or = alu.OR_gate(register_.getRegister(x), register_.getRegister(y));
            register_.setRegister(r, string_or);
            break;
        case '8':
            string_and = alu.and_gate(register_.getRegister(x), register_.getRegister(y));
            register_.setRegister(r, string_and);
            break;
        case '9':
            string_xor = alu.XOR_gate(register_.getRegister(x), register_.getRegister(y));
            register_.setRegister(r, string_xor);
            break;
        case 'A':
            cu.rotate(r, S, register_);
            break;
        case 'B':
            cu.jump(r, xy, register_, pc);
            break;
        case 'D':
            cu.Jmuped(register_.getRegister(r), register_.getRegister(0), pc, xy);
            break;
        default:
            cout << "Unknown operation code: " << opCode << endl;
    }
}
void cpu::clear()
{
    pc=10;
    IR="";
}

void mainUI::menu() {
        cout<<endl << "1. Run step by step" << endl;
        cout << "2. Run whole" << endl;
        cout << "0. Exit" << endl;
    }

void mainUI::loadfile(cpu &processor) {
    cout << "Enter a valid file name: ";
    cin >> filename;
    ifstream fileinstruction(filename);
    if (fileinstruction.is_open()) {
        string instruction;
        int address = 10;
        bool hasC000 = false;

        while (fileinstruction >> instruction) {
            if (instruction.length() != 4) {
                cout << "Error: Instruction must be exactly 4 characters. Skipping." << endl;
                continue;
            }


            bool valid = true;
            for (char ch : instruction) {
                if (!((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F'))) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cout << "Error: Instruction contains invalid characters: " << instruction << ". Skipping." << endl;
                continue;
            }


            memory.wr(address++, instruction.substr(0, 2)); // First part of the instruction
            memory.wr(address++, instruction.substr(2, 2)); // Second part of the instruction


            if (instruction == "C000") {
                hasC000 = true;
            }
        }
        fileinstruction.close();
        cout << "Instructions loaded into memory." << endl;


        if (!hasC000) {
            memory.wr(address++, "C0"); // First part of "C000"
            memory.wr(address++, "00"); // Second part of "C000"
            cout << "Added termination instruction C000 to memory." << endl;
        }
    } else {
        cout << "File not found. Please try again." << endl;
        loadfile(processor);

    }
}
char mainUI::choiceInput() {
    cout << "Choose an option: ";
    cin >> choice;
    return choice;
}

void mainUI::runStepByStep(cpu &processor) {
    while (true) {
        processor.fetch(memory);
        cout << "PC: " << processor.pc << endl;
        cout << "Instruction Register (IR): " << processor.IR << endl;
        processor.execute(memory);
        memory.printMemory();
        cout << endl;
        processor.register_.printRegisters();

        if (processor.IR == "C000") {
            cout << "Reached termination instruction C000. Stopping execution." << endl;
            break;
        }

        cout << "Press Enter to execute the next instruction.";
        cin.ignore();
        cin.get();
    }
}

void mainUI::runWhole(cpu &processor) {
    while (true) {
        processor.fetch(memory);
        if (processor.IR == "C000") {
            cout << endl << "Reached termination instruction C000. Stopping execution." << endl;
            break;
        }
        processor.execute(memory);
    }

    memory.printMemory();
    processor.register_.printRegisters();
}

void mainUI::run(cpu &processor) {
        while (true) {
            menu();
            choiceInput();
            if (choice == '1') {
                loadfile(processor);
                runStepByStep(processor);
                register2.clear();
                memory.clear();
                processor.clear();

            } else if (choice == '2') {
                loadfile(processor);
                runWhole(processor);
                register2.clear();
                memory.clear();
                processor.clear();
            } else if (choice == '0') {
                cout << "Exiting program." << endl;
                break;
            } else {
                cout << "Invalid choice. Please try again." << endl;
            }
        }
    }





