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
  //为什么可以保证退出循环的时候 是left == right 而不是left==right +1 呢
  while (left < right)
  {
    mid = (left + right) / 2;
    if (nums[mid] < target)//target一直大于mid
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
//遍历次数 2
//二分搜索 是找一个数 找到了一般在while循环里返回，搜索长度 不同
//搜索边界是while退出后才可能有答案。搜索长度 不同 因为while里根本就没有返回啊
//针对寻找左边界：
//如果一直是缩小右边范围，那么就是left=right = 0的时候退出循环
//如果是缩小左边界，那么就是left = mid +1 = right = size()的时候退出循环
//针对寻找右边界: