#include <stack>
#include <string>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <list>
#include <windows.h>
#include <numeric>

using namespace std;

class GAME
{
public:
    std::vector<vector<char>> vector;
    GAME(int m_, int n_, int k) : m(m_), n(n_)
    {
        std::vector<char> temp;
        for (int i = 0; i < n; i++)
            temp.push_back('#');
        for (int i = 0; i < k; i++)
            vector.push_back(temp);

        std::vector<char> temp1;
        for (int i = 0; i < n; i++)
            temp1.push_back(' ');
        for (int i = k; i < m; i++)
            vector.push_back(temp1);

        vector[m - 1][n / 2] = '#';
        old_x = m - 1;
        old_y = n / 2;
        oold_x = m;
        oold_y = n / 2 - 1;
    }
    ~GAME()
    {
    }

private:
    int m;
    int n;
  //需要用这几个坐标判断 遇到边界怎么反弹
    int oold_x;
    int oold_y;
    int old_x;
    int old_y;
    int index = 0;
    bool flag = false;
  //坐标变换方向
    int way[4][2] = {{-1, 1}, {1, -1}, {1, 1}, {-1, -1}};

    int getindex() { return 0; };
    void change()
    {

        vector[old_x][old_y] = ' ';
        int new_x = 0;
        int new_y = 0;

        //遇到边界 和遇到 字符的处理
        if (old_x == m - 1)
        {
            if (old_x == oold_x - 1 && old_y == oold_y + 1)
            {
                index = 0;
            }
            else if (old_x == oold_x + 1 && old_y == oold_y - 1)
            {
                index = 3;
            }
            else if (old_x == oold_x + 1 && old_y == oold_y + 1)
            {
                index = 0;
            }
        }
        else if (old_x == 0)
        {
            if (old_x == oold_x - 1 && old_y == oold_y - 1)
            {
                index = 1;
            }
            else if (old_x == oold_x - 1 && old_y == oold_y + 1)
            {
                index = 2;
            }
        }
        else if (old_y == 0)
        {
            if (old_x == oold_x + 1 && old_y == oold_y - 1)
            {
                index = 2;
            }
            else if (old_x == oold_x - 1 && old_y == oold_y - 1)
            {
                index = 0;
            }
        }
        else if (old_y == n - 1)
        {
            if (old_x == oold_x - 1 && old_y == oold_y + 1)
            {
                index = 3;
            }
            else if (old_x == oold_x + 1 && old_y == oold_y + 1)
            {
                index = 1;
            }
        }


        new_x = old_x + way[index][0];
        new_y = old_y + way[index][1];
      
        vector[new_x][new_y] = '#';
        
        oold_x = old_x;
        oold_y = old_y;
        old_x = new_x;
        old_y = new_y;
    }

    void showFrame()
    {
        int m = vector.size();
        int n = vector[0].size();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << vector[i][j];
            }
            cout << endl;
        }
    }

public:
    void mainLoop()
    {
        while (1)
        {
            Sleep(150);
            change();
            showFrame();
        }
    }
};

int main()
{
    GAME gm(20, 30, 5);
    gm.mainLoop();
    return 0;
}
