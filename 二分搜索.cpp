int binarySearch(vector<int> &nums, int target)
{
  int left = 0, right = nums.size() - 1, mid = 0;
  while (left <= right)
  {
    mid = (left + right) / 2;
    if (nums[mid] < target)
      left = mid + 1;
    else if (nums[mid] > target)
      right = mid - 1;
    else
      return mid;
  }
  return -1;
}

//  2 3 4   5
int leftbound(vector<int> &nums, int target)
{
  int left = 0, right = nums.size(), mid = 0;
  while (left < right)
  {
    mid = (left + right) / 2;
    if (nums[mid] < target)
      left = mid + 1;
    else
      right = mid;
  }
  //target 比所有数都大
  if (left == nums.size())
    return -1;
  //target比所有的数都小或等于
  return nums[left] == target ? left : -1;
}
//区别就是等于的时候 是收缩左边界还是右边界
int rightbound(vector<int> &nums, int target)
{
  int left = 0, right = nums.size(), mid = 0;
  while (left < right)
  {
    mid = (left + right) / 2;
    if (nums[mid] <= target)
      left = mid + 1;
    else
      right = mid;
  }
  if (left == 0)
    return -1;
  return nums[left - 1] == target ? left - 1 : -1;
}
