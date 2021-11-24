class Solution
{
public:
    //旋转数组中找最小值
    int minArray(vector<int> &numbers)
    {
        int left = 0, right = numbers.size() - 1;

        while (left < right)
        {
            int mid = (left + right) / 2;
            if (numbers[mid] < numbers[right])
                right = mid;
            else if (numbers[mid] > numbers[right])
                left = mid + 1;
            else
                right--;
        }
        return numbers[left];
    }
    void test()
    {
        vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8};
        int size = nums.size();
        for (int i = 0; i < nums.size(); i++)
        {
            cout << "nums[left]" << nums[(i + 1) % size] << "  nums[mid] : " << nums[(i + size / 2) % size] << "  nums[right]: " << nums[i] << endl;
        }
    }
};
