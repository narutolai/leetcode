#ifndef __MYSTRING__
#define __MYSTRING__
class String
{
public:
    String(const char* cstr=0);
    //拷贝构造
    String(const String& str);
    //拷贝赋值
    String operator =(const String& str);
    //析构函数
    ~String();
    char * get_c_str() const {return m_data;}
private:
    char *m_data;//C风格的字符串
};

inline String::Stirng(const char* cstr = 0)
{
	if(cstr){
    m_data = new char[strlen(cstr)+1];//还要放结束符的所以要加1
        strcpy(m_data,cstr);
    }
    else
    {
    m_data = new char[1];
        *m_data = '\0'; 
    }
}
//拷贝构造
inline String::String(const Stirng& str)
{
	m_data= new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
}
//拷贝赋值
inline String& String::operator=(const String& str){
	//检查自我赋值 是很重要的。不然就会自己杀自己。
    if(this==&str)
    	return *this;
    delete[] m_data;
    m_data = new char[strlen(str.m_data)+1];
    strcpy(m_data,str.m_data);
    return *this;
}
//字符串的重载<<
#include <iostream.h>
ostream& operator<<(ostream & os,const String &str)
{	
    //os流
    os <<str.get_c_str();
	return os;
}
inline String::~String()
{
	delete[] m_data;
}
#endif
String S4("hello"); //全局变量，
int main()
{
	String s1();
    String s2("hello"); //栈空间 作用域scope
    static String S3("WORLD");//程序结束才死亡
    
    String* p = new String("hello"); //堆空间
    //注意p是p m_data是m_data不要搞混了
    delete p;
}
