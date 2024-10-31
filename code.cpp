#include <bits/stdc++.h>
using namespace std;
class Register {
    vector<int>reg;
    int size2;
    public:
    Register() : reg(16 , 0)
    {
        size2 = 16;
    }
    void setRegister(int address , int value)
    {
        reg[address] = value;
    }
    int getRegister(int address)
    {
        return reg[address];
    }
};
class Memory {
    vector<string>memo;
    int size1;
    public:
    Memory():memo(256 , 0) {
        size1 = 256;
    }
    string rd (int index) {
        return memo[index];
    }
    void wr (int index, string val) {
        memo[index] = val;
    }
};
int main()
{

}
