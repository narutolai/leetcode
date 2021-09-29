请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。
路径可以从矩阵中的任意一格开始，每一步可以在矩阵中向左、右、上、下移动一格。
如果一条路径经过了矩阵的某一格，那么该路径不能再次进入该格子。
例如，在下面的3×4的矩阵中包含一条字符串“bfce”的路径（路径中的字母用加粗标出）。

[["a","b","c","e"],
["s","f","c","s"],
["a","d","e","e"]]

但矩阵中不包含字符串“abfb”的路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入这个格子。


示例 1：

输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
示例 2：

输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false

class Solution {
public:
    vector<vector<char>> board_;
    vector<vector<bool>> visit_;
    int row,col;
bool dfs(int x,int y,string word,int index)
    {   
        if(x<0||y<0||x>row-1||y>col-1||visit_[x][y]||board_[x][y]!=word[index])  return false;
        if(index==word.size()-1)        return true;     
        visit_[x][y]=true;
        bool res=dfs(x+1,y,word,index+1)||dfs(x,y+1,word,index+1)||dfs(x-1,y,word,index+1)||dfs(x,y-1,word,index+1);       
        visit_[x][y]=false;  
        //其实也可以不用visit数组，可以直接把访问过的board[x][y] 变成另一个数字，回去时再改回去。
        //因为你探索的路径可能不行 但是以其他方式探索的路径到这个点或许是可以的。
        return res;
    }
    bool exist(vector<vector<char>>& board, string word) {
        row=board.size();
        col=board[0].size();
        board_=board;
        vector<vector<bool>> visit(row,vector<bool>(col,false));
        visit_=visit;
        for(int i=0;i<row;i++)
           for(int j=0;j<col;j++)
               if(board[i][j]==word[0])   
                if(dfs(i,j,word,0)) 
                    return true;
         return false;
    }
};
