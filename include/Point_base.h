//#pragma once   //��֤ͷ�ļ�ֻ������һ�Σ���ifdef��define��endif�������ơ�
#ifndef POINT_BASE_H_ //��ֹͷ�ļ��������εķ�������#pragma once�������ƣ����ǿ�ƽ̨���ܸ���
#define POINT_BASE_H_
#include <string>
#include <iostream>
class Point_base
{
	
public:
	Point_base(void);
	Point_base(int a,int b,std::string name);
	virtual ~Point_base(void);  //�����������������ģ�����������
	void SetAge1(const int& x){Age1_=x;}//��ʽ����//const����1������const�ͷ�const����2���������ڷ�&���͵Ĳ�����������ʱ�������൱�ڰ�ֵ����
	int GetAge1()const{return Age1_; }//const����ı��Ա����ֵ
	void SetName(std::string name){Name_=name; }
	virtual void ShowMessage(){std::cout<<"-----Name's "<<Name_<<"----Age1:"<<Age1_<<"----Age2:"<<Age2_<<"\n";}
	inline virtual void speak();//��ʽ����
	Point_base & Add(Point_base & add,const int & nn);//����ֵ����ΪPoint_base &��ζ�ŷ��صľ���ԭ����Point_base�������ǿ���
	Point_base & Add( Point_base & add,const int & nn,const int & nb);//��������ʱ���������Ƿ�Ϊ&
	Point_base & SetAge(const int& a,const int& b);
	const Point_base & operator+(const Point_base & add);
//	Point_base & operator=(const Point_base & rs); 
	Point_base & operator++();
	static  int pub_point_num_;//��̬���ݳ�Ա��ÿ���ࣨ���Ƕ���ֻ��һ���� ������Ϊ�����࣬������ĳ������� 
		//�����const���ͣ��ڴ˾Ϳ��Գ�ʼ����������ǣ���Ҫ�������ʼ���� 
	static const int Get_pri_point_num(){return pri_point_num_;} //��̬��Ա������������ҲΪ������ 
		//��̬��Ա����û��thisָ�룬��������Ϊconst���ͣ�����д�ģ�����ΪconstҲû�г�����
		//�����ڳ�Ա���ݱ����ڳ�Ա��������ͨ��thisָ����ʵģ���˾�̬��Ա�������ܷ����κηǾ�̬��Ա��������
	private:
		int Age1_;
		int Age2_; 
		int* Age_; // ָ�����ֻ��������ʼ�� 
		std::string Name_;
	//	int & Ager= Age1;  //���ñ�����������ʱ��ͳ�ʼ�� 
		static int pri_point_num_; //����private�ľ�̬���ݱ�����ֻ��ͨ�����Ա�������е��÷��ء� 
};
//int Point_base::pub_point_num=0;//��const�ľ�̬��Ա������������߶��岢��ʼ�� 
//int Point_base::pri_point_num=0;
#endif















