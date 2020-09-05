
//一个deom 基本实现了c++的抽象类、多态、函数重载、重写、运算符重载、继承、初始化构造函数
#include <iostream>
using namespace std;

//抽象类
class box
{
protected:
	int lenght;
	int width;
	int height;
public:
	//必须有一个虚函数 不能被实例化 但是提供方法
	virtual void get_multi()=0;
	//虚析构函数
	virtual ~box(){}
	void set_para(int x,int y,int z)
	{
		lenght=x;
		width=y;
		height=z;
	}
};


class sub_box: public box
{
public:
	int number;
	int x;
	//无参构造函数
	sub_box(){}
	sub_box(int x,int number):number(number),x(x){
		cout<<x<<number<<endl;
		cout<<"sub_box created"<<endl;
	}
	~sub_box(){
		cout<<"sub_box destroyed"<<endl;
	}
	// sub_box(int x,int y, int z,int number):lenght(x),width(y),height(z){
	// 	抽象类是没有构造函数的 不可能在子类中通过构造函数初始化。
	//	number=number;
	// }
	//函数重载
	void set_number(int x)
	{
		number=x;
		cout<<"set_number int:"<<x<<endl;
	}
	void set_number(double x)
	{
		number=x;
		cout<<"set_number double:"<<x<<endl;
	}
	//将基类中的函数设置为虚函数 实现子类晚绑定 实现抽象类中的get_multi方法 同时把其设定为虚函数 让其子类重载
	virtual void get_multi()
	{
		cout<<"volume is"<<(x*number)<<endl;
	}
	void get_x_num()
	{
		cout<<"x: "<<x<<"number: "<<number<<endl;
	}

};

//多态
class sub_1_box:public sub_box
{
public:
	int x1; //构造函数同时初始化
	sub_1_box(){}
	sub_1_box(int x,int number,int x1):sub_box(x,number),x1(x1)
	{
		cout<<"sub_1_box created"<<endl;
	}
	~sub_1_box(){cout<<"sub_1_box destroyed"<<endl;}
	
	void get_multi()
	{
		cout<<"sub1:"<<"x1: "<<x1<<"number: "<<number<<endl;
		cout<<"sub_1_box get_multi"<<x1*number*x<<endl;
	}
};

class sub_2_box:public sub_box
{
public:
	int x2;
	//无参构造函数 如果不设定这个无参构造函数 那么运算符重载里的sb2的创建是不允许的。
	sub_2_box(){}
	sub_2_box(int x,int number,int x2):sub_box(x,number),x2(x2)
	{
		cout<<"sub_1_box created"<<endl;
	};
	~sub_2_box(){cout<<"sub_2_box destroyed"<<endl;}
	void get_multi()
	{
		cout<<"sub2:"<<"x2: "<<x2<<"number: "<<number<<endl;
		cout<<"sub_2_box get_multi"<<x2*number*x<<endl;
	}
	//运算符重载  对象的引用 将两个对象相加 对应的变量也相加起来
	sub_2_box operator+(const sub_2_box& b)
	{
		sub_2_box sb2;
		sb2.x2=x2+b.x2;
		sb2.x=x+b.x;
		sb2.number=number+b.number;
		return sb2;
	}
};


//用一个类实现抽象类，然后以这个类作为基类去派生子类
int main(int argc, char const *argv[])
{
	
	sub_1_box sub1(1,2,3);
	sub1.get_multi();
	
	sub1.set_number(6.05);
	sub1.get_multi();
	//抽象类的方法
	sub_2_box sub2(3,4,5);
	sub2.get_multi();

	sub_2_box sub22(4,5,6);
	sub22.get_multi();


	sub_2_box sb22=sub2+sub22;
	sb22.get_multi();

	return 0;
}
