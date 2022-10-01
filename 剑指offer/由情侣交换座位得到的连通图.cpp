
class test3
{
private:
    int count;
    vector<int> father;

public:
    test3(int n);
    ~test3();
    int find(int x)
    {
        while (x!=father[x])
            x = father[x];
        return x;
    }
    void funion(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty)
            return;
        father[rootx] = rooty;
        count--;
    }
    int get_count() { return count; }//返回几个联通分量。
};

test3::test3(int n)
{
    count = n;
    for (int i = 0; i < n; i++)//每一个人的爹都是他自己
        father.push_back(i);
}

test3::~test3()
{
}

//最少要交换几次座位，让所有的情侣都坐在一起
int main()
{
    vector<int> row{6, 2, 1, 7, 4, 5, 3, 8, 0, 9};


    test3 te(5);
    int x=0,y=0;
    for (int i = 0; i < row.size(); i+=2)
    {
        x = row[i] / 2;
        y = row[i + 1] / 2;
        te.funion(x, y);
    }
    cout<<5-te.get_count()<<endl;
    
    return 0;
}
