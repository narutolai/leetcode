s=""
s="            "
s=",,,    ,,,, hello world ,,,"

class Solution {
public:
    int countSegments(string s) {
        int count=0;
        while(!s.empty()&&s.back()==' ')
        {
             s.pop_back();
        }
     if(s.size()==0) return 0; //空字符串
     for(int i=0;i<s.size();i++)
     {
         if(s[i]!=' ')
        {
            for(int j=i;j<s.size();)
            {
                if (s[j] == ' ')
                    {
                        count++;
                        while(s[j]==' ')j++;
                    }
                    else
                    {
                        j++;
                    }
            }
            break;
        }
     }
    return count+1;
    }
};
