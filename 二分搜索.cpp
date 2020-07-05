1.二分搜索查找数 没有返回-1
int binarySearch(vector<int>& nums,int target)
{
 int left=0,right=nums.szie()-1;
 while(left<=right)
 {
 mid=(left+right)/2;
 if(a[mid]<target) left=mid+1;
 else if(a[mid]>target) right=mid-1;
 else return mid;
 }
 return -1;
}

查找左侧边界 查找2

1  2  2  3  4
L     M     R
LM R    
  LMR
R LM
最终可以返回 L 或 M 或 R+1

int leftbound(vector<int>& nums,int target)
{
 int left=0,right=nums.size()-1,mid=0;
 while(left<=right)
 {
  mid=(left+right)/2;
 if(a[mid]<target) left=mid+1;
 else right=mid-1;
 }
 return a[mid]==target?mid:-1;
}

查找数组的右侧边界
int rightbound(vector<int>& nums,int target)
{
 int left=0,right=nums.size()-1,mid=0;
 while(left<=right)
 {
  mid=(left+right)/2;
 if(a[mid]<=target) left=mid+1;
 else right=mid-1  ;
 }
 if(right<0)return -1;
 else return  a[right]==target?right:-1;
}
