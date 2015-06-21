#include "Point_base.h"
#include <iostream>
#include <string>

Point_base::Point_base():Age1_(0),Age2_(0){//构造函数，初始化参数列表 
pub_point_num_++;//pub统计有多少个Point 对象
pri_point_num_++;//pri统计有多少个Point 对象
std::cout<<"通过静态成员函数，得知目前存在的Point对象有"<<pub_point_num_<<"个\n"; 
std::cout<<"无参数构造函数-----Age1:"<<Age1_<<"   Age2:"<<Age2_<<"\n";
}
Point_base::Point_base(int a,int b,std::string name):Age1_(a),Age2_(b),Name_(name){//构造函数，初始化参数列表 ,参数名不能和成员变量相同，成员变量后一般加_下注
pub_point_num_++;//pub统计有多少个Point 对象
pri_point_num_++;//pri统计有多少个Point 对象
std::cout<<"通过静态成员函数，得知目前存在的Point对象有"<<pub_point_num_<<"个\n"; 
std::cout<<"两参数构造函数-----Age1:"<<Age1_<<"   Age2:"<<Age2_<<"\n";
}
 Point_base & Point_base::Add( Point_base & add,const int & nn){//函数重载！！
	 int bb=this->Age1_+add.GetAge1()+nn;
	int  c=0;
	this->SetAge(bb,c);
	std::cout<<"加一个数之后："<<this->GetAge1()<<"\n";
	return *this;
} 
  Point_base & Point_base::Add( Point_base & add,const int & nn,const int & nb){//函数重载！！
	  int bb=this->Age1_+add.GetAge1()+nn+nb;
	int  c=0;
	this->SetAge(bb,c);
	std::cout<<"加两个数之后："<<this->GetAge1()<<"\n";
	return add;
} 
 Point_base& Point_base::SetAge(const int& a,const  int& b){ 
Age1_=a;
Age2_=b;
std::cout<<"Age1:"<<this->Age1_<<"   Age2:"<<this->Age2_<<"\n";
return *this;      
}

const Point_base& Point_base::operator+(const Point_base & add){ //重载加法运算符 ,只加Age1
    std::cout<<this->GetAge1()<<"：操作数顺序,如果为1，表示a+b中a是this。\n";
	this->Age1_=this->Age1_+add.Age1_;       //本体的this指针，指向自己
	std::cout<<"Age1:"<<this->Age1_<<"   Age2:"<<this->Age2_<<"\n";
	return *this;      
}
Point_base & Point_base::operator++(){//重载++运算符 
	++Age1_;
	++Age2_;
	std::cout<<"重载++运算符：Point成员自加1.\n"<<"Age1:"<<Age1_<<"\nAge2:"<<Age2_<<"\n";
	return *this;
}
/*Point_base & Point_base::operator=(const Point_base & rs)
{
	if (this==&rs)
	{      //在复制中不能自己赋给自己 
		return *this;
	}
	//再进行其他的赋值 
//	return rs;
}*/
void Point_base::speak()
{
std::cout<<"I am Piont_base"<<"\n";
}
Point_base::~Point_base(void)
{
}
