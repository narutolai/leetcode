
要对结果取模

class Solution {
public:
    long long waysToStep(int n) {
        if(n==0) return 0;
      int mod = 1e9 + 7;
    int f1 = 0, f2 = 0, f3 = 0, f4 = 1;
    int i = 1;
    while (i != (n + 2))
    {
        if (i != 1)
            f4 = ((f1%mod + f2%mod)%mod + f3%mod)%mod;
        // f4 = (f1%mod + f2%mod +f3%mod)%mod;
        f1 = f2;
        f2 = f3;
        f3 = f4;
        i++;
    }
    return f4;
    }
};
