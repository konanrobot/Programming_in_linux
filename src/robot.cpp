#include <stdio.h>
#include <vector>
#include <list>
#include <iostream>
#include "Point_base.h"
#include "PointA.h"
#include <boost/config.hpp>  
#include <string>  
#include <boost/graph/adjacency_list.hpp>  
#include <boost/tuple/tuple.hpp>  
//#include <boost/timer.hpp>
//#include <boost/progress.hpp>
#include <boost/timer/timer.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include <boost/random.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/noncopyable.hpp>//其实是私有化的=操作符
#include <boost/utility.hpp>//包含数个小工具的实现
#include <boost/assign.hpp>
#include <boost/exception/all.hpp>//异常测试
#include <boost/uuid/uuid.hpp>  //用于表示和生成uuid
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/sha1.hpp>
using namespace boost;
using namespace std;
using namespace boost::signals2;
using boost::lexical_cast;
using namespace boost::timer;
using namespace boost::assign;
using namespace boost::uuids;
using namespace boost::uuids::detail;
enum family  
{ Jeanie, Debbie, Rick, John, Amanda, Margaret, Benjamin, N };  
class shared
{
private:
	boost::shared_ptr<int> p;
public:
	shared(boost::shared_ptr<int> p_):p(p_){}
	void print()
	{
		std::cout<<"count"<<p.use_count()<<"v="<<*p<<endl;
	}
};
template<int N>
struct slots
{
	int operator()(int x)
	{
		cout << "slot" << N << " called" << endl;
		return x *N;
	}
};
template<int N>
bool operator==(const slots<N>&, const slots<N>&)
{
	return true;
}
int Point_base::pub_point_num_=0; //非常量的类静态成员变量要在类的外边初始化
int Point_base::pri_point_num_=0;
const int Size=10;
int cook[Size]={1,2,3,4,5,6,7,8,9,10};
void show_point_num();
int sum_arr(const int *arr,int n);//数组累加和，传递的是指针，const类型参数，非const类型也可以用，反之不可以
/*-------------------------交换函数------------------------------------------------------------*/
template<typename T>
void swapp(T& x,T& y);//定义一个函数，包括函数原型，函数体，函数调用 
template <> void swapp<Point_base>(Point_base &p1,Point_base &p2); //针对Point_base的具现化！！
/*---------------------------最大最小函数-------------------------------------------------------*/ 
int  max(int& x,int & y);
int  min(int& x,int & y);
void showPiont_age1(Point_base & dd);
void slots1();
void slots2();
typedef int (*VPF) (int &x,int &y);
void Print(VPF,int &x,int &y);
void print_func(boost::shared_ptr<int> p);
/*********************boost_timer测试，以下两个函数的却别在于C++11使用了std::move********************************/
vector<string> createVector_98();
vector<string> createVector_11();
/*********************boost_signal测试*******************/
class ring :boost::noncopyable//这样的话ring就不可复制了！！！
{
public:
	typedef signal<void()> signal_t;
	typedef signal_t::slot_type slot_t;
	connection connect(const slot_t& s)
	{
		return alarm.connect(s);
	}
	void press()
	{
		cout << "Ring alarm..." << endl;
		alarm();
	}
private:
	signal_t alarm;
};
typedef variate_generator<rand48, uniform_smallint<>> bool_rand;
bool_rand g_rand(rand48(time(0)), uniform_smallint<>(0, 100));
extern char const nurse1[] = "Mary";
extern char const nurse2[] = "Kate";
template<char const *name>
class nurse
{
private:
	bool_rand &rand;
public:
	nurse() :rand(g_rand){}
	void action()
	{
		cout << "Nurse " << name;
		if (rand() > 30)
		{
			cout << " wakeup and open the door." << endl;
		}
		else
		{
			cout << " is sleeping..." << endl;
		}
	}
};
extern char const baby1[] = "Tom";
extern char const baby2[] = "Jack";
template<char const *name>
class baby
{
private:
	bool_rand &rand;
public:
	baby() :rand(g_rand){}
	void action()
	{
		cout << "Baby " << name;
		if (rand() > 50)
		{
			cout << " wakeup and crying loudly..." << endl;
		}
		else
		{
			cout << " is sleeping sweetly..." << endl;
		}
	}
};
class guest
{
public:
	void press(ring &r)
	{
		cout << "A guest press the ring." << endl;
		r.press();
	}
};
class demo_class
{
public:
	typedef signal<void()> signal_t;
	boost::shared_ptr<signal_t> sig;
	int x;
	demo_class() :sig(new signal_t), x(10){}
};
void print_sig()
{
	cout << "hello signal" << endl;
}
/*----------------------------------------------------------------------------------------------------------------*/
/*--------------------------------main函数------------------------------------------------------------------------*/ 
/*----------------------------------------------------------------------------------------------------------------*/
int main(){
std::cout<<"数组累加和"<<sum_arr(cook,Size)<<"\n";
int a =99;
int b =100;
int& c=b;//引用在定义时就要初始化
Point_base P1; //调用自己的构造函数1
P1.speak();
P1.SetAge(4,8);
P1.SetName("P1");
Point_base P2(1,2,"P2");//调用自己的构造函数 2
P2=P1;
P2.ShowMessage();
P1.Add(P2,10);
P1.Add(P2,10,10);//函数重载
P2.SetAge(a,c);
P2=P1;
++P2;   //重载++运算符
PointA Pa1(11,22,33,"Pa");
Pa1.ShowMessage();
Pa1.speak();  //派生类自己的虚函数
Pa1.SetAge(6,a);//派生类调用基类函数//SetAge参数类型为const int &，
Pa1.SetName("Pa1");
showPiont_age1(Pa1);//showPiont_age1的参数是Point_base,但是如果参数是派生类也是可以用的！！！！！
Point_base* pP=&Pa1;
pP->speak();  //还是PointA
show_point_num();//
swapp(a,b);
swapp(P1,P2);
/*---------------------------type (*VPF) (int &x,int &y),把VPF当作函数参数传入Print函数，处理数据--------------------*/
VPF pp;
pp=max;
int hh=3,jj=33;
std::cout<<"type (*VPF) (int &x,int &y),把VPF(这里为max)当作非类成员函数(Print)参数传入Print函数，处理数据,得到:\n" ;
Print(pp,hh,jj);
/*------------------------------函数指针数组——————————————————————————————---------*/ 
const int Maxarray=2;
 int (*pFunArray[Maxarray]) (int &,int &); //函数指针数组定义 
 pFunArray[0]=max;
 pFunArray[1]=min;
 int aa1=8,bb1=9;
 std::cout<<"非类成员函数指针数组的使用："; 
 pFunArray[0](aa1,bb1); 

/*-----------------非类成员函数指针----------------------------*/
int (* pFun)(int &,int &);//函数指针的声明 ，表示输入参数为 (int &,int &) ,输出参数为int。注意两个参数都要加上
bool fQuit=false;
int choice;
int x1=4,x2=5;
while(fQuit==false)
	{
	std::cout<<"非类成员函数指针的使用：\n(0)quit\n(1)max\n(2)min\n";
	std::cin>>choice;
	switch (choice)
		{
		case 1:pFun=max;break;     //函数名(不带括号！！！！)就是 指针——地址。 
		case 2:pFun=min;break;
		default: fQuit=true;break;
		}
	if (fQuit)
	 break;
	 pFun(x1,x2);
	}
/*--------------------boost_timer测试--------------------------------*/
std::cout <<"boost_timer_测试"<< std::endl; 
        //timer t;
	//cout<<"max"<<t.elapsed_max()/3600<<"h"<<"\n";
	//std::cout<<"min"<<t.elapsed_min()<<"s"<<"\n";
	//std::cout<<"min"<<t.elapsed()<<"s"<<"\n";   //计时功能
	//progress_timer tt; //测量多个时间，{}控制范围
	//progress_display pd(100); //显示进度条，100是基数
	//vector<string> v(100);
    const int TEST_TIMES = 100;

    vector<string> result;

    boost::timer::cpu_timer timer;

    timer.start();
    for (int i = 0; i < TEST_TIMES; ++i)
    {
        result = createVector_98();
    }
    cout << "no move" << timer.format(6) << endl;

    timer.start(); //start是归0，重新开始，而resume是继续上次的时间继续走 don't call resume()
    
    for (int i = 0; i < TEST_TIMES; ++i)
    {
        result = createVector_11();
    }
    cout << "use move" << timer.format(6) << endl;
/*********************boost_graph测试******************************/

    const char *name[] = { "Jeanie", "Debbie", "Rick", "John", "Amanda",  
        "Margaret", "Benjamin" };  
  
    adjacency_list <> g(N);  
    add_edge(Jeanie, Debbie, g);  
    add_edge(Jeanie, Rick, g);  
    add_edge(Jeanie, John, g);  
    add_edge(Debbie, Amanda, g);  
    add_edge(Rick, Margaret, g);  
    add_edge(John, Benjamin, g);  
  
    graph_traits < adjacency_list <> >::vertex_iterator i, end;  
    graph_traits < adjacency_list <> >::adjacency_iterator ai, a_end;  
    property_map < adjacency_list <>, vertex_index_t >::type  
        index_map = get(vertex_index, g);  
  
    for (boost::tie(i, end) = vertices(g); i != end; ++i) 
	{  
        std::cout << name[get(index_map, *i)];  
        boost::tie(ai, a_end) = adjacent_vertices(*i, g);  
        if (ai == a_end)  
            std::cout << " has no children";  
        else  
            std::cout << " is the parent of ";  
        for (; ai != a_end; ++ai) 
		{  
            std::cout << name[get(index_map, *ai)];  
            if (boost::next(ai) != a_end)  
                std::cout << ", ";  
        }  
        std::cout << std::endl;
    }  
	 std::cout <<"boost_test_end"<< std::endl; 

/*--------------------shared_ptr测试1.1--------------------------------*/
boost::shared_ptr<int> sp(new int(10));
assert(sp.unique());
boost::shared_ptr<int> sp2=sp;
assert(sp==sp2 && sp.use_count()==2);
*sp2=100;
assert(*sp=100);
sp.reset();
assert(!sp);
/*--------------------shared_ptr测试1.2--------------------------------*/
boost::shared_ptr<int> spp(new int(100));
shared s1(spp),s2(spp);
s1.print();
s2.print();
*spp=111;
std::cout<<"print_func函数内部拷贝了一个shared_ptr对象，因此引用次数加1，但是退出该函数时该对象自动析构，引用计数会又返回到3！";
print_func(spp);
s1.print();
/*--------------------shared_ptr测试1.3--------------------------------*/
//用了boost::make_shared，就不用new了！！！
boost::shared_ptr<string> sp_=boost::make_shared<string>("make_shared");
boost::shared_ptr<vector<int>> sp1_=boost::make_shared<vector<int>>(10,2);//应用于标准容器的第一个用法
assert(sp1_->size()==10);
/*--------------------shared_ptr测试1.4--------------------------------*/
//应用于标准容器的第二个用法
typedef vector<boost::shared_ptr<int>> vs;  //应用于标准容器的第二个用法
vs v1(10);
int i1=0;
for (vs::iterator pos=v1.begin();pos!=v1.end();++pos)
{
	(*pos)=boost::make_shared<int>(++i1);//使用工厂函数赋值
	std::cout<<*(*pos)<<", ";
}
std::cout<<endl;
boost::shared_ptr<int> p_=v1[9];
*p_=112;
std::cout<<*v1[9]<<endl;
/*--------------------shared_ptr测试1.5--------------------------------*/
//桥接模式,pimpl或者handle/body
//



/*--------------------signal测试1.0--------------------------------*/

signal<void()> sig;
sig.connect(&slots1);
sig.connect(&slots2, at_front);
sig();
signal<int(int)> sig1;
assert(sig1.num_slots() == 0);
connection c1 = sig1.connect(0,slots<10>());
connection c2 = sig1.connect(0, slots<20>());
connection c3 = sig1.connect(1, slots<50>());
cout << *sig1(2) << endl;
sig1.disconnect(0);
assert(sig1.num_slots() == 1);
sig1.disconnect(slots<50>());
assert(sig1.num_slots() == 0);
connection c4 = sig1.connect(1, slots<100>());
assert(c4.connected());
{
	scoped_connection sc = sig1.connect(1, slots<200>());
	assert(sig1.num_slots() == 2);
}
assert(sig1.num_slots() == 1);
cout << "一个例子：" << endl;
ring r;
nurse<nurse1> n1;
nurse<nurse2> n2;
baby<baby1> b1;
baby<baby2> b2;
guest gg;
r.connect(bind(&nurse<nurse1>::action, n1));
r.connect(bind(&nurse<nurse2>::action, n2));
r.connect(bind(&baby<baby1>::action, b1));
r.connect(bind(&baby<baby2>::action, b2));
gg.press(r);

demo_class obj;
assert(obj.sig.use_count() == 1);
demo_class obj1(obj);   //这样的话就可以复制
assert(obj.sig.use_count() == 2);
obj.sig->connect(&print_sig);
(*obj1.sig)();
/*************lexical_cast测试**********************/
  	int a3= lexical_cast<int>("123456");
 	double b3 = lexical_cast<double>("123.456");
 	std::cout << a3 << std::endl;
	std::cout << b3 << std::endl;
	/*-------------------------assign测试-------------------------------------*/
	/*------------------以下除了assert中的=外，其他的都是assign中重载的+=和=号*/
	vector<int> v_assign;
	v_assign += 1, 2, 3, 4, 5, 6 * 6;
	push_back(v_assign)(100)(101);
	assert(v_assign.size() == 8);
	set<string> s_assign;
	s_assign += "cpp", "python", "c#";
	insert(s_assign)("ruby")("R");
	assert(s_assign.size() == 5);
	map<int, string> m1_assign;
	m1_assign += make_pair(1, "one"), make_pair(2, "two");
	insert(m1_assign)(3, "three")(4, "four");
	assert(m1_assign.size() == 4);
	/*-------------------------异常测试-------------------------------------*/
	struct my_exception :  //一个异常类
		virtual std::exception, virtual boost::exception
	{};
	typedef boost::error_info<struct tag_err_no, int> err_no;//两种异常信息，用int和string分别存储错误码和错误信息
	typedef boost::error_info<struct tag_err_str, int> err_str;
	try
	{

		try
		{
			//抛出异常，存储错误码10
			//			throw my_exception() << err_no(10);
		}
		catch (my_exception &e)
		{
			cout << *get_error_info<err_no>(e) << endl; //可以获得异常内部保存的信息值的指针
			cout << e.what() << endl;
			//e << err_str("other info");   //向异常追加信息why cannot be used?
			throw;                        //再次抛出异常
		}
	}
	catch (my_exception &e)
	{
		cout << *get_error_info<err_str>(e) << endl;//获取异常信息
	}
	/*--------------------------------UUID测试---------------------------------------*/
	//uuid可以看做一个容量固定为16、元素类型为unsigned char的容器
	uuid u;
	assert(uuid::static_size() == 16);
	assert(u.size() == 16);

	vector<unsigned char> vc(16, 7);
	std::copy(vc.begin(), vc.end(), u.begin());//使用标准复制算法
	assert(u.data[0] == u.data[1] && u.data[15] == 7); //数组方式访问

	cout << "uuid : " << u << endl;
	std::fill_n(u.data + 10, 6, 8);//标准算法fill_n直接操作数组
	cout << "uuid :" << u << endl;
	//四种生成器:
	//1 Nil 无效的UUID（全0值）
	uuid u1 = nil_generator()();//第一个()与nil_generator结合，调用nil_generator的构造函数，生成一个临时对象，然后第二个()是nil_generator对象的operator()操作符，就像一个函数调用，生成一个nil uuid对象
	cout << "无效的UUID： " << u1 << endl;
	assert(u1.is_nil());
	uuid u2 = nil_uuid();
	assert(u2.is_nil());

	//2 字符串生成器 1.没有连字符的全十六进制数字。   2.使用连字符的，只能在第5、7、9、11字节前使用连字符
	string_generator sgen;
	uuid uuid11 = sgen("0123456789abcdef0123456789abcdef");
	cout << "字符串生成器:  " << uuid11 << endl;
	uuid uuid12 = sgen("01234567-89ab-cdef-0123-456789abcdef");
	cout << uuid12 << endl;
	uuid uuid13 = sgen(L"{01234567-89ab-cdef-0123-456789abcdef}");
	cout << uuid13 << endl;

	//3 名字生成器 先指定一个基准UUID，使用字符串名字派生出基于这个ＵＵＩＤ的一系列ＵＵＩＤ．
	uuid www_xxx_com = string_generator()("0123456789abcdef0123456789abcdef");//生成一个组织的UUID
	name_generator ngen(www_xxx_com);
	uuid nu1 = ngen("mario");   //为名字mario生成UUID
	assert(!nu1.is_nil() && nu1.version() == uuid::version_name_based_sha1);//version是sha1算法
	uuid nu2 = ngen("link");   //为名字link生成UUID
	cout << "名字生成器:   " << nu2 << endl;

	//4 随即生成器
	random_generator rgen;
	uuid gu = rgen();
	assert(gu.version() == uuid::version_random_number_based);
	cout << "随即生成器：  " << gu << endl;
	string str = to_string(gu);
	cout << "uuid转string:    " << str << endl;

	/*-----------------------------SHA1摘要算法-------------------------------*/
	//将任意长度的文本压缩成一个只有20字节（160位）的独一无二的摘要
	sha1 sha;                                         //sha1对象
	char *szMsg = "a short message！";
	//以下三种以不同的方式将数据喂给sha1对象，当输入所有数据后用get_digest获得计算出来的摘要值
	sha.process_byte(0x10);                           //用于摘要的信息
	sha.process_bytes(szMsg, strlen(szMsg));          //处理一个字节
	sha.process_block(szMsg, szMsg + strlen(szMsg));  //处理多个字节
	unsigned int digest[5];         //摘要的返回值
	sha.get_digest(digest);        //获得摘要
	for (int i = 0; i < 5; ++i)
	{
		cout << hex << digest[i];  //16进制输出
	}
	cout << endl;
        assert(1==2); //在Debug下，这一个句会产生 Assertion `1==2' failed. Aborted (core dumped)
                      //而在Release下，这一句直接跳过。
/*************C++11特性*****************************/
auto i11=10;
cout<<"I am C++11特性, auto i11=10:--"<<i11<<endl;
return 0;
}      
//模板
template<typename T>
void swapp(T& rx,T& ry)
{//引用作为参量的函数
	int tmp;
	std::cout<<"运用模板的swap程序：\n""交换前----x:"<<rx<<",y:"<<ry<<"\n";
	tmp=rx;
	rx=ry;
	ry=tmp;
	std::cout<<"交换后----x:"<<rx<<",y:"<<ry<<"\n";
}
//模板特化
template <> void swapp<Point_base>(Point_base &p1,Point_base &p2)
{
	std::cout<<"运用模板具现化Point_base的交换，只交换Age1：\n交换之前--"<<"P1_Age1:"<<p1.GetAge1()<<"   P2_Age1:"<<p2.GetAge1()<<"\n";
	int a1;
	a1=p1.GetAge1();
	p1.SetAge1(p2.GetAge1());
	p2.SetAge1(a1);
	std::cout<<"交换之后--"<<"P1_Age1:"<<p1.GetAge1()<<"   P2_Age1:"<<p2.GetAge1()<<"\n";
}
//求最大值
int max(int& x,int & y)
{
	if (x>y)
	{ 
	   std::cout<<"最大值为："<<x<<"\n"; 
	   return x;
	 } 
     	else
     	 { 
  	   std::cout<<"最大值为："<<y<<"\n"; 
    	   return y;}
             }
//求最小值
int min(int& x,int & y)
{
	if (x<y){
	   std::cout<<"最小值为："<<x<<"\n"; 
	   return x;} 
    	 else{ 
   	  std::cout<<"最小值为："<<y<<"\n"; 
    	 return y;}
}
void Print(VPF pFunc,int &x,int &y)
{
 	pFunc(x,y);
}
void show_point_num()
{
	std::cout<<"通过非Point的成员函数也可以访问Point的public静态数据成员(Point对象个数):"<<Point_base::pub_point_num_<<"\n"; 
	std::cout<<"通过静态成员函数(只能)访问Point的静态数据成员（Point对象个数）:"<<Point_base::Get_pri_point_num()<<"\n";
}	
/**
 * [showPiont_age1 description]
 * @param dd [description]
 */
void showPiont_age1(Point_base & dd)
{
	std::cout<<dd.GetAge1()<<"以基类为参数的函数也可以用子类作为参数\n";
}
int sum_arr(const int *arr,int n) //也可以用int arr[],这里传递的是数组的指针，
{
	int total=0;
	for (int i=0;i<n;i++ )
		total=total+arr[i];
	return total;
}
void print_func(boost::shared_ptr<int> p)
{
	std::cout<<"count"<<p.use_count()<<"v="<<*p<<endl;
}
void slots1()
{
	cout << "slots1 called" << endl;
}
void slots2()
{
	cout << "slots2 called" << endl;
}
vector<string> createVector_98()
{
    vector<string> vec;
    for (int i = 0; i < 100; ++i){
            vec.emplace_back("helloworld");
    }
    return vec;
}

vector<string> createVector_11()
{
    vector<string> vec;
    for (int i = 0; i < 100; ++i){
        vec.emplace_back("helloworld");
    }
    return std::move(vec); //C++11的std::move
}