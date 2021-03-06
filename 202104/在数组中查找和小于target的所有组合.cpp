

class Solution {
public:
    int purchasePlans(vector<int>& nums, int target) {
        
        sort(nums.begin(),nums.end());
        int mod=1e9+7;
        int l=0,r=nums.size()-1;
        int res=0;
        while(l<=r)
        {
            if(nums[l]+nums[r]>target)
            {
                r--;
            }
            else
            {
                res+=r-l;
                res%=mod;
                l++;
            }
        }
        return res;
    }
};
