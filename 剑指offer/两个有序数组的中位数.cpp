class Solution
{
public:
	double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
	{
		int i = nums1.size(), j = nums2.size();
		int size1 = nums1.size(), size2 = nums2.size();

		int midindex = size1 / 2; //计算中位数需要的下标

		int num1 = 0, num2 = 0;
		int count = 0;
		int MinNum = 0;
		//开始遍历数组
		while (i < size1 && j < size2)
		{
			count++;
			MinNum = (nums1[i] < nums2[j]) ? nums1[i++] : nums2[j++];
			if (count == midindex)
			{
				num1 = MinNum;
			}
			if (count == midindex + 1)
			{
				num2 = MinNum;
				break;
			}
		}
		while (i < size1 && num2 == 0)
		{
			count++;
			if (count == midindex)
			{
				num1 = nums1[i];
			}
			if (count == midindex + 1)
			{
				num2 = nums1[i++];
				break;
			}
		}
		while (j < size2 && num2 == 0)
		{
			count++;
			if (count == midindex)
			{
				num1 = nums2[j];
			}
			if (count == midindex + 1)
			{
				num2 = nums2[j++];
				break;
			}
		}

		if (count % 2) //总元素个数为奇数 中位数就是第k2个
		{
			return num2;
		}
		else
		{
			return (num1 + num2) / 2.0; //否是是 (k2+k1)/2
		}
	}
};
//遍历次数1
//找两个有序数组的中位数,从小到大排序