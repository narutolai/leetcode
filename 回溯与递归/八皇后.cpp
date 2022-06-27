#include<iostream>
#include <vector>
using namespace std;

class Solution
{
    private:
        vector<vector<int>> m_board{vector<vector<int>>(8,vector<int>(8,0))};
        int m_Count;
public:
        Solution():m_Count(0){}
        void Printstatus()
        {
            for (int i = 0; i < 8; i++)
            {
                for(int j = 0 ;j < 8; j++ )
                {
                    cout<<m_board[i][j]<<" ";
                }
                cout <<endl;
            }
            cout<<"======================\n\n\n";
        }

        void backtrace(int row)
        {
            if (row == 8)
            {
                Printstatus();
                m_Count++;
                return ;
            }
            for (int i = 0 ; i < 8; i++)
            {
                m_board[row][i] = 1;
                if(CheckConditon(row,i))
                {
                    backtrace(row+1);
                }
                m_board[row][i] = 0;
            }
        }
        bool CheckConditon(int row, int column)
        {
            //检查同列
            int sum = 0;
            int i  =row,j=column;
            for (int i = 0; i <= row; i++)
                sum+=m_board[i][column];
            if (sum > 1)
                         return false;
            //检擦对角线
            sum = 0;
            while(i>=0 && j>=0)
            {
                sum +=m_board[i--][j--];
            }
            i =row;
            j = column;
            while (i >= 0 && j <8)
            {
                sum+= m_board[i--][j++];
            }
            if (sum > 2)
                return false;
            return true;

        }
        int GetCount()
        {
            return m_Count;
        }
};
