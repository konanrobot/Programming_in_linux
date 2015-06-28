#ifndef POINTA_H_ //防止头文件被编译多次的方法，与#pragma once功能类似，但是跨平台性能更好
#define POINTA_H_
//#pragma once
#include "Point_base.h"
class PointA :
	public Point_base
{
public:
	PointA(void);
	PointA(const int &a,const int &b,const int &c,std::string name);
	~PointA(void);
	//virtual void ShowMessage(){std::cout<<"-----Name's "<<Name_<<"----Age1:"<<Age1_<<"----Age2:"<<Age2_<<"----Age3:"<<Age3_<<"\n";}
	virtual void speak();
        void xy(const int x,const int y);
private:
	int Age3_;
	//int & Age33=Age3;
};
#endif
