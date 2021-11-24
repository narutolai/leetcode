class Solution
{
public:
    int threeSumClosest(vector<int> nums, int target)
    {
        sort(nums.begin(), nums.end());
        int ans = nums[0] + nums[1] + nums[2];
        for (int i = 0; i < nums.size(); i++)
        {
            int start = i + 1, end = nums.length - 1;
            while (start < end)
            {
                int sum = nums[start] + nums[end] + nums[i];
                if (Math.abs(target - sum) < Math.abs(target - ans))
                    ans = sum;

                if (sum > target)
                    end--;
                else if (sum < target)
                    start++;
                else
                    return ans;
            }
        }
        return ans;
    }
}
