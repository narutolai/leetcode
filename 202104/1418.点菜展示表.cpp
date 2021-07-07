//我的机器上运行似乎没有问题 ，但是在网页上编译不过
class compare
{
public:
    bool operator()(const string & left, const string &right)
    {
        return stoi(left) < stoi(right);
    }
};
class Solution
{
public:
    //每当新来一项订单时
    map<string, int> food2index;
    map<string, int, compare> table2index;

    int get_order_of_food(string &food)
    {
        int i = 0;
        for (auto &item : food2index)
        {
            i++;
            if (item.first == food)
            {
                return i;
            }
        }
        return 0;
    }
    int get_order_of_table(string &table)
    {
        int i = 0;
        for (auto &item : table2index)
        {
            i++;
            if (item.first == table)
            {
                return i;
            }
        }
        return 0;
    }
    vector<vector<string>> displayTable(vector<vector<string>> &orders)
    {

        vector<string> temp;
        //第一行的食物名字
        temp.push_back("Table");
        vector<vector<string>> result;
        result.push_back(temp);

        int i = 1, j = 1;
        for (auto &item : orders)
        {
            string table = item[1];
            string food = item[2];
            //桌子食物都出现过 把那个值加1
            if (food2index.find(food) != food2index.end() && table2index.find(table) != table2index.end())
            {
                string oldvalue = result[get_order_of_table(table)][get_order_of_food(food)];
                int count = stoi(oldvalue) + 1;
                result[get_order_of_table(table)][get_order_of_food(food)] = to_string(count);

            } //桌子没出现过 表中加一张桌子
            else if (food2index.find(food) != food2index.end())
            {
                table2index[table] = i++;

                vector<string> line;
                line.push_back(table);
                //设定该行该行初值为0
                for (int k = 1; k < result[0].size(); k++)
                    line.push_back("0");

                int index = get_order_of_table(table);
                result.insert(result.begin() + index, line);

                result[index][get_order_of_food(food)] = "1";

            } //食物没出现过 表中加一种食物
            else if (table2index.find(table) != table2index.end())
            {

                food2index[food] = j++;
                //获取食物的字典序下标
                int index = get_order_of_food(food);
                //第一行插入食物名称
                result[0].insert(result[0].begin() + index, food);
                //其余的行插入初始值
                for (int k = 1; k < i; k++)
                    result[k].insert(result[k].begin() + index, "0");

                //设定值
                result[get_order_of_table(table)][index] = "1";
            }
            else //都没有出现过
            {
                //新增一列
                food2index[food] = j++;
                int index = get_order_of_food(food);
                result[0].insert(result[0].begin() + index, food);
                for (int k = 1; k < i; k++)
                    result[k].insert(result[k].begin() + index, "0");

                //新增一行
                table2index[table] = i++;

                vector<string> line;
                line.push_back(table);
                //设定该行初值为0
                for (int k = 1; k < result[0].size(); k++)
                    line.push_back("0");

                line[index] = "1";

                //获取line插入的位置
                int index2 = get_order_of_table(table);
                result.insert(result.begin() + index2, line);
            }
        }

        return result;
    }
};
int main()
{
    Solution so;
    vector<vector<string>> order = {
        {"David", "3", "Ceviche"},
        {"Corina", "10", "Beef Burrito"},
        {"David", "3", "Fried Chicken"},
        {"Carla", "5", "Water"},
        {"Carla", "5", "Ceviche"},
        {"Rous", "3", "Ceviche"}};
    so.displayTable(order);

    return 0;
}
