void quicksort(vector<int> &num, int left, int right)
{
    if (left >= right)
        return;
    int pivot = num[left];
    int i = left;
    int j = right;

    while (i < j)
    {
        while (i < j && num[j] >= pivot)
            j--;
        num[i] = num[j];

        while (i < j && num[i] <= pivot)
            i++; 
        num[j] = num[i];
    }
    num[i] = pivot; //枢纽最终位置
    quicksort(num, left, i - 1);
    quicksort(num, i + 1, right);
}
//是真的怀疑你行不行
void MergeSort(vector<int> &nums, vector<int> &temp ,int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    MergeSort(nums, temp, left, mid);
    MergeSort(nums, temp, mid + 1, right);
    int k,j,i;
    for (i = left,k = left, j = mid + 1; i <= mid && j <= right;)
    {
        if (nums[i] < nums[j])
        {
            temp[k++] = nums[i];
            i++;
        }
        else
        {
            temp[k++] = nums[j];
            j++;
        }
    }
    while (i <= mid)
        temp[k++] = nums[i++];
    while (j <= right)
        temp[k++] = nums[j++];

    for (int i = left; i <= right; i++)
    {
        nums[i] = temp[i];
    }
}


//把堆排序的内容也放到这里吧
class MyHeap
{
private:
public:
    void heap_sort(vector<int> &nums)
    {
        //首先建立大顶堆
        int size = nums.size();
        for (int i = nums.size() / 2; i >= 0; i--)
        {
            adjustheap(nums, i, size - 1);
        }
        //然后调整堆
        for (int j = nums.size() - 1; j > 0; j--)
        {
            swap(nums[0], nums[j]);
            adjustheap(nums, 0, j - 1);
        }
    }
    void adjustheap(vector<int> &nums, int st_index, int et_index)
    {
        int temp = nums[st_index];
        //注意是2*i+1因为下标是从0开始的
        for (int i = 2 * st_index + 1; i <= et_index; i = 2 * i + 1)
        {
            if (i + 1 <= et_index && nums[i + 1] > nums[i])
            {
                i++;
            }
            if (nums[i] > temp)
            {
                nums[st_index] = nums[i];
                st_index = i;
            }
        }
        nums[st_index] = temp;
    }

    MyHeap(){};
    ~MyHeap(){};
};
