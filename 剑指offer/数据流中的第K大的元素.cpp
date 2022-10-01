
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
        int parentIndex = st_index;
        int compareNum = nums[parentIndex];
        //注意是2*i+1因为下标是从0开始的
        for (int sonIndex = 2 * parentIndex + 1; sonIndex <= et_index; sonIndex = 2 * sonIndex + 1)
        {
            if (sonIndex + 1 <= et_index && nums[sonIndex + 1] > nums[sonIndex])
            {
                sonIndex++;
            }
            if (nums[sonIndex] > compareNum)//两个子节点一个父节点 求这三个点中的最小值/最大值.
            {
                nums[parentIndex] = nums[sonIndex];
                parentIndex = sonIndex;
            }
        }
        nums[parentIndex] = compareNum;
    }

    MyHeap(){};
    ~MyHeap(){};
};

class KthLargest
{
    int k;
    vector<int> nums;

public:
    void adjustheap(int st_index, int et_index)
    {
        int temp = nums[st_index];
        for (int i = 2 * st_index + 1; i <= et_index; i = 2 * i + 1)
        {
            if (i + 1 <= et_index && nums[i + 1] < nums[i])
            {
                i++;
            }
            if (nums[i] < temp)//小顶堆  如果父节点值大于儿子节点的值 则替换。
            {
                nums[st_index] = nums[i];//子节点替换父节点,父节点走到子节点位置处
                st_index = i;
            }
        }
        nums[st_index] = temp;
    }

    KthLargest(int k, vector<int> &numsout) : k(k)
    {

        for (int i = 0; i < k; i++)
            nums.push_back(-10000);

        for (int j = 0; j < numsout.size(); j++)
        {
            add(numsout[j]);
        }
    }
    int add(int val)
    {
        if (val > nums[0])
        {
            nums[0] = val;
            adjustheap(0, k - 1);
        }
        return nums[0];
    }
};
//数据流中第K大的数 ,直接弄一个元素大小为K的小顶堆
//那么堆顶元素就是里面最小的或者说第K大的元素
//如果下一个元素 比堆顶元素小,那么不用比较，如果比堆顶元素大那就要替换下
//当堆顶元素被替换后 要重新调整堆,堆顶元素就是数据流中的第K大的数
//但是要先push 3个很小的数
//遍历次数 2
// 比如数据流是 9 8 6 .....接着7来了...