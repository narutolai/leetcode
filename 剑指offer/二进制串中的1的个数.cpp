class Solution {
public:
    int hammingWeight(uint32_t n) {
      //输入一个二进制串？
      int co=0;
      while(n)
      {
          if(n%2)
            co++;
          n/=2;
      }
      return co;  
    }
};
