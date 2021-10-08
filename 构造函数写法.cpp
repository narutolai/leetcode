#include <vector>
#include <map>
#include <string>
#include <memory>
#include <string.h>
#include <iostream>
using namespace std;

//带有C风格的字符串 就是char*
class Bitmap
{
public:
    //直接用C风格字符串构造
    Bitmap(const char *cstr = 0)
    {
        if (m_data)
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
    //拷贝构造
    Bitmap(const Bitmap &rhs)
    {
        //申请空间
        m_data = new char[strlen(rhs.m_data) + 1];
        //填充内容
        strcpy(m_data, rhs.m_data);
    }
    //拷贝赋值
    Bitmap &operator=(const Bitmap &rhs)
    {
        char *pOri = m_data;
        m_data = new char[strlen(rhs.m_data) + 1];
        //在申请成功之后再删除原来的堆内存
        delete pOri;
        strcpy(m_data, rhs.m_data);
        return *this;
    }

    char *get_c_str() const { return m_data; }
    //析构函数 注意c风格的字符串是这样来delete的
    ~Bitmap()
    {
        delete[] m_data;
    }

private:
    char *m_data;
};

//重载<<这样可以输出了
ostream &operator<<(ostream &os, const Bitmap &str)
{
    //os流
    os << str.get_c_str();
    return os;
}

//普通的对象指针 在通过new申请的时候 直接构造
class Widget
{
public:
    Widget();
    Widget(const Widget &rhs);
    Widget &operator=(const Widget &rhs);
    ~Widget();

private:
    Bitmap *bp;
};

inline Widget::Widget()
{
    cout << "construct" << endl;
    bp = nullptr;
}

inline Widget::Widget(const Widget &rhs)
{
    cout << "copy construct" << endl;
    bp = new Bitmap(*rhs.bp);
}

inline Widget &Widget::operator=(const Widget &rhs)
{
    cout << "copy assignment " << endl;
    Bitmap *pOrig = bp;
    bp = new Bitmap(*rhs.bp);
    delete pOrig; //我们将pb的删除放到申请内存成功后面来做这个地方来做
    return *this;
}

inline Widget::~Widget()
{
    if (bp != nullptr)
    {
        delete bp;
    }
    bp = nullptr;
    cout << "deconstruct" << endl;
}

int main()
{
    // //unique_ptr
    // unique_ptr<Widget> sp1 = make_unique<Widget>();
    // unique_ptr<Widget> sp2 = move(sp1);

    //shared_ptr 加入了引用计数
    {
        shared_ptr<Widget> sp1(new Widget());
        cout << "use count:" << sp1.use_count() << endl; //1

        shared_ptr<Widget> sp2(sp1);
        cout << "use count:" << sp1.use_count() << endl; //2

        sp2.reset();
        cout << "use count:" << sp1.use_count() << endl; //1

        {
            shared_ptr<Widget> sp3 = sp1;
            cout << "use count:" << sp1.use_count() << endl; //2
        }
        cout << "use count:" << sp1.use_count() << endl; //1
       // shared_ptr<Widget> sp3 = make_shared<Widget>();
       //出作用域之前会调用其析构函数
    }
    cout<<"hello world"<<endl;
    return 0;
}


//关于拷贝构造函数中不需要删除原指针所指的内存空间。
class test
{
private:
  int *a;

public:
  test(int a_)
  {
    a = new int(a_);
    cout << "construct" << endl;
  }
  test(const test &rhs)
  {
    cout<<"copy construct "<<endl;
    a = new int(*rhs.a);
  }
  ~test()
  {
    delete a;
    cout<<"deconstruct"<<endl;
  }
  void show()
  {
    cout << *a << endl;
  }
  //重载括号
  test& operator()(const test &rhs)
  {
    return *this;
  }
};


int main()
{

  test te1(1);
  te1.show();
  test te2(2);
  te2.show();
  test te3(te1);
  te3.show();
  //这种调用法和48行是不一样的
  te3(te1); //这种方式是要重载了()才可以

  return 0;
}
