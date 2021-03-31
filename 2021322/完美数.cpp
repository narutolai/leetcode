一个数的正因子之和等于它自己，称之为完美数。 

class Solution {
public:
    bool checkPerfectNumber(int num) {
        int sum=0;
        for(int i=1;i*i<num;i++)
        {
            if(num%i==0) 
            {
                sum+=i;
            if(num/i!=i)//这里除以1之后等于num本身也加上去了，所以最后的结果要减去一个num
                sum+=num/i;
            }
        }
        
        return sum==num*2;
    }
};

