
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
    int get_count() { return count; }
};

test3::test3(int n)
{
    count = n;
    for (int i = 0; i < n; i++)
        father.push_back(i);
}

test3::~test3()
{
}

int find(vector<int> &fa, int x)
{
    while (x != fa[x])
        x = fa[x];
    return x;
}

void funio(vector<int> &fa, int x, int y,int &count)
{
    int rootx = find(fa, x);
    int rooty = find(fa, y);
    if (rootx == rooty)
        return;
    fa[rootx] = fa[rooty];
    count--;
}

int main()
{
    vector<int> row{6, 2, 1, 7, 4, 5, 3, 8, 0, 9};

    // vector<int> fa{0, 1, 2, 3, 4};
    // int x = 0, y = 0;
    // int count=fa.size();
    // for (int i = 0; i < row.size(); i+=2)
    // {
    //     x = row[i] / 2;
    //     y = row[i + 1] / 2;
    //     funio(fa, x, y,count);
    // }
    // cout<<fa.size()-count<<endl;

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
