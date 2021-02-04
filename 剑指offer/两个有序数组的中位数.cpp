class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
      
    vector<int>::const_iterator iter1=nums1.begin(),iter2=nums2.begin();

	int k1=0,k2=0;
	int count=nums2.size()+nums1.size();
	if(count%2)
	{
		k1=count/2+1;
	}
	else
	{
		k1=count/2;
		k2=count/2+1;
	}

	int number=0,pivot1=0,pivot2=0;
	//开始遍历数组
	while (iter1!=nums1.end()&&iter2!=nums2.end())
	{
		if(*iter1<=*iter2)
		{
			number++;//每比较一个数，总个数就加1
			if(number==k1)//然后把这个数记录下来就行了
			{
				pivot1=*iter1;
			}
			if(number==k2)
			{
				pivot2=*iter1;
				break;
			}
			iter1++;
		}
		else 
		{
			number++;
			if(number==k1)
			{
				pivot1=*iter2;
			}
			if(number==k2)
			{
				pivot2=*iter2;
				break;
			}
			iter2++;
		}
	}
	while (iter1!=nums1.end())
	{
			number++;
			if(number==k1)
			{
				pivot1=*iter1;
			}
			if(number==k2)
			{
				pivot2=*iter1;
				break;
			}
			iter1++;
	}
	while (iter2!=nums2.end())
	{
			number++;
			if(number==k1)
			{
				pivot1=*iter2;
			}
			if(number==k2)
			{
				pivot2=*iter2;
				break;
			}
			iter2++;
	}
	
	if(count%2)
	{
		return pivot1;
	}
	else
	{
		return(pivot1+pivot2)/2.0;
	}
   
    }
};
