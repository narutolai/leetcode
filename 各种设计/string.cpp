#include <iostream>
#include <string.h>
using namespace std;


//一个支持支持移动构造函数的带指针的类
class Mystring
{
public:
    Mystring(const char *cstr = 0)
    {
        cout << "default construct" << endl;
        if (cstr)
        {
            m_data = new char[strlen(cstr) + 1];
            strcpy(m_data, cstr);
        }
        else
        {
            m_data = new char[1];
            *m_data = '\0';
        }
    }
    // 拷贝构造赋值 深拷贝
    Mystring(const Mystring &rhs)
    {
        cout << "copy construct" << endl;
        m_data = new char[strlen(rhs.m_data) + 1];
        strcpy(m_data, rhs.m_data);
    }
    Mystring &operator=(const Mystring &rhs)//赋值返回自身的引用
    {
        cout << "default assignment" << endl;
        char *pOrig = m_data;
        m_data = new char[strlen(rhs.m_data) + 1];
        strcpy(m_data, rhs.m_data);
        delete[] pOrig;//注意是个数组 注意是个数组
        return *this;
    }

    //移动构造赋值
    Mystring(Mystring &&rhs)
    {
        cout << "move construct" << endl;
        this->m_data = rhs.m_data;
        rhs.m_data = nullptr;
    }
    Mystring &operator=(Mystring &&rhs)//赋值返回自身的引用,赋值返回自身的引用
    {
        cout << "move assignment" << endl;
        if (this != &rhs)
        {
            this->m_data = rhs.m_data;
            rhs.m_data = nullptr;
        }
        return *this;
    }

    ~Mystring()
    {
        cout << "deconstruct" << endl;
        delete[] m_data; //因为是new char[] 所以在delete的时候 也要加上 [] 这个样子的。
    }

    //注意这里不加const 下面重载会报错
    char *get_c_str() const { return m_data; }
    bool empty() { return m_data == nullptr; }

private:
    char *m_data;
};
// 为了让其支持cout 我们必须重载 << 这是个全局函数
ostream &operator<<(ostream &os, const Mystring &st)
{
    //这里重载的时候判断下 会有问题
    if (st.get_c_str() != nullptr)
        os << st.get_c_str();
    return os;
}
int main()
{
    {
        char p[] = "dasdsa1";   //pass
        Mystring str("dasdas"); //构造函数 new
        Mystring str1(str);     //拷贝构造 new
        Mystring str2 = str1;   //拷贝构造 new
        str2 = str1;            //拷贝赋值 new
        cout << str << endl;
        cout << str1 << endl;
        cout << str2 << endl;

        Mystring str3(std::move(str)); //移动构造 将其转换为右值
        Mystring str4;                 //构造函数 new
        str4 = std::move(str1);        //移动赋值

        cout << str.empty() << endl;  //str应该为空了 直接访问会出现未定义错误
        cout << str1.empty() << endl; //str1应该为空了 
        cout << str1<< endl;


        cout << str3 << endl;
        cout << str4 << endl;
    }
    cout << "normal exist" << endl;
    return 0;
}
//赋值返回自身的引用