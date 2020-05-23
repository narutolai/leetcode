void quicksort(vector<int>& num,int left,int right)
{        
    if(left>=right) return;                           l     r 
    int pivot=num[left];       5  1 6 9 8 4 10 
    int i=left;
    int j=right;

    while(i<j)
    {
        while(i<j&&num[j]>=pivot)j--;
        num[i]=num[j];
        
        while(i<j&&num[i]<=pivot) i++;
        num[j]=num[i];
   
    }
    num[i]=pivot;  //枢纽最终位置
    quicksort(num,left,i-1);
    quicksort(num,i+1,right);   
}

void mergesort(vector<int>&source,vcetor<int>&temp,int sta,int end)
{
    if(sta<end)
    {
        int mid=sta+(end-sta)/2;
        mergesort(source,temp,sta,mid);
        mergesort(source,temp,mid+1,end);

        for(int i=sta,j=mid+1;i<=mid&&j<=end;)
        {
            if(source[i]<source[j]) 
                temp[k++]=source[i++];
            else 
                temp[k++]=source[j++];
        }
        while(i<=mid) temp[k++]=source[i++];
        while(j<=end) temp[k++]=source[j++];

        for(int i=sta;i<=end;i++)
            source[i]=temp[i];
    }
}
