#实现pow()

class Solution {
public:                  
    double myPow(double x, int n) { // 2 9 2 256
      double res=1.0;
      int t=n;
      while(n)
      {
          if(n&1) //n为奇数时，先乘以一个x 9  4  2  1
            res*=x; //  2*256 512

          x*=x;        //  4  4  4   4     4的4次方
          n/=2;         //                16 的2次方
                                           //的 256  1次方
      }
    return t>0?res: 1.0/res;
    }
};
