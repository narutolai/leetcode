0  1
1  1 1
2  1 2 1
3  1 3 3 1
4  1 4 6 4 1

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        vector<int> result(rowIndex+1,0);
        result[0]=1;
        int i=0;
        while(i<rowIndex)
        {   
            for(int j=i+1;j>0;j--)
            {
                result[j]+=result[j-1];
            }
            i++;
        }
        return result;
    }   
};
