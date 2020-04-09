给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

如果你最多只允许完成一笔交易（即买入和卖出一支股票一次），设计一个算法来计算你所能获取的最大利润。

注意：你不能在买入股票前卖出股票。

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //状态转移方程很重要
        int dp_i_0=0,dp_i_1=INT_MIN;
        
        for(int i=0;i<prices.size();i++){
            //当前的dp           上一个的dp
            dp_i_0=max(dp_i_0,dp_i_1+prices[i]);
            dp_i_1=max(dp_i_1,-prices[i]);
        }
        return dp_i_0;
    }
};
