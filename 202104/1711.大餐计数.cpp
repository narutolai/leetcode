未通过 不行了 哦

class Solution
{
public:
    vector<uint32_t> candidate;

    //两数之和的变种
    int countPairs(vector<int> &deliciousness)
    {
        for (int i = 0; i <32; i++)
            candidate.push_back(pow(2, i));

        int MOD = 7 + 1e9;
        int count = 0;

        map<int, int> help_map;
        //遍历所有的num
        for (auto num : deliciousness)
        {

            if (help_map.find(num) != help_map.end())
            {
                count += help_map[num];
                count %= MOD;
            }
           
            for (auto item : candidate)
            {
                if (item >= num)
                {   
                    if(help_map.find(item - num)==help_map.end());
                    help_map[item-num]++;
                }
            }
        }
        return count;
    }
};

//这个通过了 两数之和的变种
class Solution
{
public:
    set<uint32_t> candidate={1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152};

    //两数之和的变种
    int countPairs(vector<int> &deliciousness)
    {

        int MOD = 7 + 1e9;
        int count = 0;

        map<int, int> map_t;
        //遍历所有的num
         //遍历所有的num
        for (auto num : deliciousness)
        {
            for(auto item:candidate)
            {   
                if(item>=num&&map_t[item-num])
                {
                    count+=map_t[item-num];
                    count%=MOD;
                }
            }
            map_t[num]++;
        }
        return count;
    }
};
