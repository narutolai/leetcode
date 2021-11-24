// 开发一个坐标计算工具， A表示向左移动，D表示向右移动，W表示向上移动，S表示向下移动。从（0,0）点开始移动，
// 从输入字符串里面读取一些坐标，并将最终输入结果输出到输出文件里面。

// 输入：

// 合法坐标为A(或者D或者W或者S) + 数字（两位以内）

// 坐标之间以;分隔。

// 非法坐标点需要进行丢弃。如AA10;  A1A;  $%$;  YAD; 等。

// 下面是一个简单的例子 如：

// A10;S20;W10;D30;X;A1A;B10A11;;A10;

// 处理过程：

// 起点（0,0）

// +   A10   =  （-10,0）

// +   S20   =  (-10,-20)

// +   W10  =  (-10,-10)

// +   D30  =  (20,-10)

// +   x    =  无效

// +   A1A   =  无效

// +   B10A11   =  无效

// +  一个空 不影响

// +   A10  =  (10,-10)

// 结果 （10， -10）

// 注意请处理多组输入输出

// 输入描述:
// 一行字符串

// 输出描述:
// 最终坐标，以,分隔

// 示例1
// 输入
// 复制
// A10;S20;W10;D30;X;A1A;B10A11;;A10;
// 输出
// 复制
// 10,-10
#include <iostream>
#include <set>
using namespace std;
bool isin(char c)
{
  if (c == 'A' || c == 'W' || c == 'S' || c == 'D')
    return true;
  else
    return false;
}
int main()
{
  string s;
  while (cin >> s)
  {
    int x = 0, y = 0;
    for (int i = 0; i < s.size(); i++)
    {
      if (isin(s[i])) //如果第一个数在abcd中
      {
        if (i + 1 < s.size() && s[i + 1] >= '0' && s[i + 1] <= '9') //如果第二个数在在0-9
        {
          int pre = s[i + 1] - 48;                                    //char->int
          if (i + 2 < s.size() && s[i + 2] >= '0' && s[i + 2] <= '9') //如果第三个数也在0-9
          {
            if (i + 3 < s.size() && s[i + 3] == ';') //第4个是分号。
            {
              if ((s[i - 1] == ';' && i - 1 >= 0) || i - 1 < 0) //第一个的前一个也是分号
              {
                int sum = pre * 10 + s[i + 2] - 48; //再加上这个
                if (s[i] == 'A')
                  x -= sum;
                else if (s[i] == 'D')
                  x += sum;
                else if (s[i] == 'W')
                  y += sum;
                else
                  y -= sum;
                //     cout<<"meet char"<<s[i]<<" "<<"sum is "<<sum<<endl;
                //     cout<<x<<','<<y<<endl;
              }
              else
                continue;
            }
            else
              continue;
          }
          else if (i + 2 < s.size() && s[i + 2] == ';') //或者第三个数为分号
          {
            if ((s[i - 1] == ';' && i - 1 >= 0) || i - 1 < 0) //第一个的前一也是分号
            {
              if (s[i] == 'A')
                x -= pre;
              else if (s[i] == 'D')
                x += pre;
              else if (s[i] == 'W')
                y += pre;
              else
                y -= pre;
              // cout<<"meet char"<<s[i]<<" "<<"sum is "<<pre<<endl;
              // cout<<x<<','<<y<<endl;
            }
            else
              continue;
          }
          else
            continue;
        }
        else
          continue;
      }
      else
        continue;
    }
    cout << x << ',' << y << endl;
  }
  return 0;
}
