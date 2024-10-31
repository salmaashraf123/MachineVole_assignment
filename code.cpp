#include <bits/stdc++.h>
using namespace std;
class Register {
    double value;
    public:
    Register()
    {
        value = 0;
    }
    void setRegister(double v)
    {
        value = v;
    }
    double getRegister()
    {
        return value;
    }
};
class Memory {
    vector<int>memo;
    public:
    Memory(int size):memo(size , 0){}
    double rd (int index) {
        return memo[index];
    }
    void wr (int index, double value) {
        memo[index] = value;
    }
};
int main()
{

}
