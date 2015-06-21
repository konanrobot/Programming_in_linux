#include "PointA.h"
#include <iostream>

PointA::PointA(void)
//PointA(void)
{
}
PointA::PointA(const int &a,const int &b,const int &c,std::string name):Point_base(a,b,name)
//PointA(const int &a,const int &b,const int &c,std::string name):Point_base(a,b,name)
{
	Age3_=c;
	std::cout<<"调用了基类的构造函数完成了一部分，其他的自己完成(Age3)"<<"\n";
}
void PointA::speak()
//void speak()
{
	std::cout<<"I am PointA"<<"\n";
}
PointA::~PointA(void)
//~PointA(void)
{
}
