接雨水问题

1.动态规划
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int sum = 0;
        int i = 1;
        int n = height.size();
        vector<int> lefts(n, 0); //lefts[i]表示0-i-1的最大值
        vector<int> rights(n, 0);
        while (i < n)
        {

            lefts[i] = max(lefts[i-1], height[i - 1]);
            i++;
        }

        i = n - 2;
        while (i >= 0)
        {
            rights[i] = max(rights[i+1], height[i + 1]);
            i--;
        }
        int dis = 0;
        i=0;
        while (i < height.size())
        {
            dis = min(lefts[i], rights[i]) - height[i];
            sum += dis > 0 ? dis : 0;
            i++;
        }
        return sum;
    }
};

2.单调栈  存储的是下标哦 从栈底到栈顶要求递增，每一个元素都入栈，入栈之前检查下当前元素是否大于栈顶元素
如果大于栈顶元素，
横着计算面积
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int sum = 0;
        stack<int> stk;
        while (i < height.size())
        {
            //如果当前元素小于栈顶元素则入栈
            while (!stk.empty() && height[i] > height[stk.top()])
            {
                int top = stk.top();
                stk.pop();
                if (stk.empty())
                    break;
                int left = stk.top();
                sum += (i - left - 1) * (min(height[left], height[i]) - height[top]);
            }
            stk.push(i);
        }
        return sum;
    }
};






3.双指针
class Solution
{
public:
    int trap(vector<int> &height)
    {
        int sum = 0;
        
        int n = height.size();
        int i = 0,j=n-1;
        int left_max=0,right_max=0;
        while(i<j)
        {
            left_max=max(left_max,height[i]);
            right_max=max(right_max,height[j]);
            if(height[i]<height[j]) //如果height[i]<height[j] 那么left_max<right_max ,本来就是用左右两边的最小值去减去那个值
            {
                sum+= left_max-height[i];
                i++:
            }
            else
            {
                sum+= right_max-height[j];
                j--;
            }
            
        }
        return sum;
    }
};

