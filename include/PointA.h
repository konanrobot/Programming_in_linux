#ifndef POINTA_H_ //��ֹͷ�ļ��������εķ�������#pragma once�������ƣ����ǿ�ƽ̨���ܸ���
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
