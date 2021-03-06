有个马戏团正在设计叠罗汉的表演节目，一个人要站在另一人的肩膀上。出于实际和美观的考虑，在上面的人要比下面的人矮一点且轻一点。
已知马戏团每个人的身高和体重，请编写代码计算叠罗汉最多能叠几个人。

示例：

输入：height = [65,70,56,75,60,68] weight = [100,150,90,190,95,110]
输出：6
解释：从上往下数，叠罗汉最多能叠 6 层：(56,90), (60,95), (65,100), (68,110), (70,150), (75,190)

我觉得这是二维的最长上升子序列。不对 这是信封嵌套问题。
class Solution {
public:
//二维最长上升子序列
static bool comp(vector<int>&a, vector<int>&b)
{
    if(a[0]==b[0]) return a[1]>b[1];
    else return a[0]<b[0];
}
    int bestSeqAtIndex(vector<int>& height, vector<int>& weight) {
        int m=height.size();
        vector<vector<int>> item(m,vector<int>(2,0));
        for(int i=0;i<m;i++)
        item[i]={height[i],weight[i]};
        sort(item.begin(),item.end(),comp);
        vector<int> top(m);
        int piles=0;
        
        for(int i=0;i<m;i++)
        {
            int cur=item[i][1]; //当前牌值
            int left=0,right=piles;
            //这是在数组中查找一个元素的左侧边界的写法
            while(left<right)
            {
                int mid=(left+right)/2;
                if(top[mid]>cur) right=mid;
                else if(top[mid]<cur) left=mid+1;
                else right=mid;
            }
            //如果没有新起一堆牌
            if(left==piles)piles++;
            top[left]=cur;
        }
        //别这么找 会超时真的。用二分法找把
      /*  for(int i=1;i<m;i++)
        for(int j=0;j<i;j++)
        if(item[i][1]>item[j][1])
        {dp[i]=max(dp[i],dp[j]+1);
        max_=max(dp[i],max_);
        }
        return max_;
        */
     return piles;   
    }
};
