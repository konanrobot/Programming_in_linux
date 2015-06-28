/*I am in konanrobot github now! 2015-6-28*/
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
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <time.h>
using namespace boost;
using namespace std;
using namespace boost::signals2;
using boost::lexical_cast;
using namespace boost::timer;
using namespace boost::assign;
using namespace boost::uuids;
using namespace boost::uuids::detail;
enum family  { Jeanie, Debbie, Rick, John, Amanda, Margaret, Benjamin, N };  
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


/**
 * ---------------------- **********************-boost bind test------------------------------------------------------------------
 * @param rx [description] 要交换的数字x
 * @param ry [description] 要交换的数字y
 */
void swappp(int& rx, int& ry);
/**
 * [nine_arguments description] boost的bind可以绑定9个参数并可以指定顺序
 * @param i1 [description]
 * @param i2 [description]
 * @param i3 [description]
 * @param i4 [description]
 * @param i5 [description]
 * @param i6 [description]
 * @param i7 [description]
 * @param i8 [description]
 * @param i9 [description]
 */
void nine_arguments(int i1,int i2,int i3,int i4,int i5,int i6,int i7,int i8, int i9);
class status 
{
  std::string name_;
  bool ok_;
  public:
  status(const std::string& name):name_(name),ok_(true) {}

  void break_it() 
  {
    ok_=false;
  }

  bool is_broken() const 
  {
    return ok_;
  }

  void report() const
   {
    std::cout << name_ << " is " <<
      (ok_ ? "working nominally":"terribly broken") << '\n';
   }
};
/**
 * ---------------------- **********************-boost bind 动态的排序标准------------------------------------------------------------------
 */
class personal_info {
  std::string name_;
  std::string surname_;
  unsigned int age_;

public:
  personal_info(
    const std::string& n,
    const std::string& s,
    unsigned int age):name_(n),surname_(s),age_(age) {}

  std::string name() const {
    return name_;
  }

  std::string surname() const {
    return surname_;
  }

  unsigned int age() const {
    return age_;
  }
};
/**
 * 我们通过提供以下操作符来让这个类可以流输出(OutputStreamable)：
 */
std::ostream& operator<<(std::ostream& os,const personal_info& pi) 
{
  os << pi.name() << ' ' <<
    pi.surname() << ' ' << pi.age() << '\n';
  return os;
}
/**
 * 基于年龄(可以通过成员函数 age 取得)来进行排序------仿函数
 * 派生自 binary_function. 从 binary_function 派生可以提供使用适配器时所需的 typedef
 */
class personal_info_age_less_than :
  public std::binary_function<personal_info,personal_info,bool> 

{
  public:
  bool operator()(const personal_info& p1,const personal_info& p2) 
  {
    return p1.age()<p2.age();
  }
};
// 假设有一个 vector, vec, 含有类型为 personal_info 的元素，我们可以象这样来使用这个函数对象：
//std::sort(vec.begin(),vec.end(),personal_info_age_less_than());
//但是！！！我们会采用新的方法！！！！！

/**
 * 用来显示类的状态：构造，复制构造，赋值，析构
 */
class tracer {
public:
  tracer() {
    std::cout << "构造函数 tracer::tracer()\n";
  }

  tracer(const tracer& other) {
    std::cout << "复制构造函数 tracer::tracer(const tracer& other)\n";
  }

  tracer& operator=(const tracer& other) {
    std::cout <<
      "被赋值 tracer& tracer::operator=(const tracer& other)\n";
    return *this;
  }

  ~tracer() {
    std::cout << "析构函数 tracer::~tracer()\n";
  }

  void print(const std::string& s) const {
    std::cout << s << '\n';
  }
};
/**
 * -------------------------基类----------------------------------
 */
class base {
public:
  virtual void print() const {
    std::cout << "I am 基类.\n";
  }
  virtual ~base() {}
};
/**
 * -------------------------派生类----------------------------------
 */
class derived : public base {
public:
  void print() const {
    std::cout << "I am 派生类.\n";
  }
};
void print_string(const std::string& s);
void print(std::ostream* os,int i) 
{
  (*os) << i << '\n';
}
/**
 * 仿函数,有时候比bind更加直观
 */
class print_size {
  std::ostream& os_;  //这个类是有状态的，状态就在于那个保存的 std::ostream
  typedef std::map<std::string,std::vector<int> > map_type;
public:
  print_size(std::ostream& os):os_(os) {}

  void operator()(
    const map_type::value_type& x) const {
    os_ << x.second.size() << '\n';
  }
};
/**
 * print_size_no_status 无状态的，将ostream作为（）的一个参数,
 * 这个版本的 print_size_no_status 可以很好地用于 bind, 因为它增加了一个 result_type typedef. 
 * 这样用户在使用 bind 时就不需要显式声明函数对象的返回类型。
 */
class print_size_no_status {
  typedef std::map<std::string,std::vector<int> > map_type;
public:
  typedef void result_type;
  result_type operator()(std::ostream& os,
    const map_type::value_type& x) const {
    os << x.second.size() << '\n';
  }
};
/*********************boost_timer测试，以下两个函数的却别在于C++11使用了std::move********************************/
vector<string> createVector_98();
vector<string> createVector_11();


/*********************boost_signal测试*******************/
/**
 * 门铃会响，作为触发器
 */
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
/**
 * nurse可能醒来开门，可能还在睡觉
 */
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
/**
 * baby可能会哭，可能还在睡觉
 */
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
/**
 * 客人会按门铃
 */
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



/*--------------------signal测试1.0--------------------------------------------*/
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


/*************-------------------------------------lexical_cast测试-----------------------------**********************/
int a3= lexical_cast<int>("123456");
double b3 = lexical_cast<double>("123.456");
std::cout << a3 << std::endl;
std::cout << b3 << std::endl;


/*-----------------------------------------------------------assign测试--------------------------------------------------------------*/
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
		//throw my_exception() << err_no(10);
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
assert(1==1); //在Debug下，这一个句会产生 Assertion `1==2' failed. Aborted (core dumped)
//而在Release下，这一句直接跳过。


/**---------------------------------------------------ref and bind--------------------------------------------------**/
int refx = 10;
boost::reference_wrapper<int> rw1(refx);  //°ü×°intÀàÐÍµÄÒýÓÃ
//ref rw1(refx);       //ÓëÉÏÃæÒ»Ÿä¹ŠÄÜÒ»Ñù£¬ÕâžöžüŒòµ¥
assert(refx == rw1);      //ÒþÊœ×ª»»ÎªintÒýÓÃ
(int &)rw1 = 100;     //ÏÔÊœ×ª»»ÎªintÒýÓÃ
assert(refx == 100);
boost::reference_wrapper<int> rw2(refx);  //¿œ±Ž¹¹Ôì
assert(rw2.get() == 100);
string ref_str;
boost::reference_wrapper<string> rw_str(ref_str);
*rw_str.get_pointer() = "test ref_wrapper"; //ÖžÕë²Ù×÷
cout << rw_str.get().size() << endl;//ÕâÀï²»ŽæÔÚÒ»žöÒªÇóstringÀàÐÍµÄÒþÊœ×ª»»£¬ËùÒÔÒªÓÃget()»ñµÃ±»°ü×°µÄÕæÕý¶ÔÏó£¬È»ºóµ÷ÓÃËüµÄ·œ·š


/*-------------------------------bind---------------------------------------*/
//
int i1_=1,i2_=2,i3_=3,i4_=4,i5_=5,i6_=6,i7_=7,i8_=8,i9_=9;
cout<<"bind 9 arguments:"<<endl;
(boost::bind(&nine_arguments,_9,_2,_1,_6,_3,_8,_4,_5,_7))(i1_,i2_,i3_,i4_,i5_,i6_,i7_,i8_,i9_);
           /***************************第一种情况*******************************/
           //第一种方法
	std::vector<status> statuses;
	statuses.push_back(status("status 1"));
	statuses.push_back(status("status 2"));
	statuses.push_back(status("status 3"));
	statuses.push_back(status("status 4"));

	statuses[1].break_it();
	statuses[2].break_it();
	std::cout<<"    ********第1种情况:实值----"<<endl;
	std::cout<<"		for方法："<<endl;
           //冗长、低效的(由于要多次调用 statuses.end())，并且不象使用标准库算法 for_each 那样清楚地表明意图
	for (std::vector<status>::iterator it=statuses.begin();it!=statuses.end();++it)
	{
  	it->report();
	}
	/***************************第一种情况*******************************/
	//第二种方法
	//为了用 for_each 来替换这个循环，我们需要用一个适配器来对 vector 元素调用成员函数 report 。
	//这时，由于元素是以值的方式保存的，我们需要的是适配器 mem_fun_ref
	// 要注意的是boost::mem_fn, 它也被接纳进入Library Technical Report, 它也可以在这种没有参数的情况下使用。
	//  mem_fn 取代了 std::mem_fun 和 std::mem_fun_ref
	std::cout<<"		标准库std::mem_fun_ref方法："<<endl;
	std::for_each(statuses.begin(),statuses.end(),std::mem_fun_ref(&status::report));
	/***************************第一种情况*******************************/
	//第三种方法
	std::cout<<"		boost库bind方法："<<endl;
	//在绑定一个成员函数时，bind 表达式的第一个参数必须是成员函数所在类的实例
	std::for_each(statuses.begin(),statuses.end(),boost::bind(&status::report,_1));

	/***************************第2种情况-------指针--------*******************************/
	std::vector<status*> p_statuses;
	p_statuses.push_back(new status("status 1"));
	p_statuses.push_back(new status("status 2"));
	p_statuses.push_back(new status("status 3"));
	p_statuses.push_back(new status("status 4"));

	p_statuses[1]->break_it();
	p_statuses[2]->break_it();
	std::cout<<"    ********第2种情况:指针----"<<endl;
	//第一种方法
	//不能再用 mem_fun_ref. 我们需要的是适配器 mem_fun, 它被认为有点用词不当，但它的确正确完成了需要做的工作
	std::cout<<"		标准库std::mem_fun方法--------："<<endl;
	std::for_each(p_statuses.begin(),p_statuses.end(),std::mem_fun(&status::report));
	//第二种方法
	//使用 bind, 我们就无须关心我们处理的元素是指针了
	//(这一点已经在容器类型的声明中表明了，对于现代的库来说，这样的冗余信息是不需要的)
	std::cout<<"		boost库bind方法--------："<<endl;
	std::for_each(p_statuses.begin(),p_statuses.end(),boost::bind(&status::report,_1));

            /***************************第3种情况-------智能指针--------*******************************/
	std::vector<boost::shared_ptr<status> > s_statuses;
	s_statuses.push_back(boost::shared_ptr<status>(new status("status 1")));
	s_statuses.push_back(boost::shared_ptr<status>(new status("status 2")));
	s_statuses.push_back(boost::shared_ptr<status>(new status("status 3")));
	s_statuses.push_back(boost::shared_ptr<status>(new status("status 4")));
     	s_statuses[1]->break_it();
	s_statuses[2]->break_it();
	//现在，我们要用标准库中的哪个适配器呢？
	//mem_fun 和 mem_fun_ref 都不适用，因为智能指针没有一个名为 report 的成员函数
	//不得不采用我们正想要摆脱的循环，或者使用 Boost.Bind, 它不会抱怨任何事情
	std::cout<<"    ********第3种情况:智能指针"<<endl;
	std::for_each(s_statuses.begin(),s_statuses.end(),boost::bind(&status::report,_1));
	std::cout<<"结论：不管对于实值，指针还是智能指针，bind都能提供比较一致的方法。而标准库方法则不可"<<endl;
/*------------------------boost bind 动态的排序标准----------------------------*/
std::vector<personal_info> vec;
vec.push_back(personal_info("Little","John",30));
vec.push_back(personal_info("Friar", "Tuck",50));
vec.push_back(personal_info("Robin", "Hood",40));
//按 age 排序
//原型为：boost::bind<bool>(std::less<unsigned int>(),_1,_2);
//现在，我们有了一个接受两个参数的函数对象，两个参数的类型都是 unsigned int, 
//但我们还不能用它，因为容器中的元素的类型是 personal_info, 
//我们需要从这些元素中取出 age 并把它作为参数传递给 std::less. 我们可以再次使用 bind 来实现。
std::sort( vec.begin(), vec.end(), boost::bind(
    						std::less<unsigned int>(),
    						boost::bind(&personal_info::age,_1),
    						boost::bind(&personal_info::age,_2)
    					        )
            );

//这里，我们创建了另外两个绑定器。第一个用主绑定器的调用操作符的第一个参数(_1)来调用 personal_info::age 。
//                                              第二个用主绑定器的调用操作符的第二个参数(_2)来调用 personal_info::age 。
//因为 std::sort 传递两个 personal_info 对象给主绑定器的调用操作符，
//结果就是对来自被排序的 vector 的两个 personal_info 分别调用 personal_info::age 。
//最后，主绑定器传递两个新的、内层的绑定器的调用操作符所返回的 age 给 std::less. 这正是我们所需要的！
//调用这个函数对象的结果就是 std::less 的结果，
//这意味着我们有了一个有效的比较函数对象可以用来排序容器中的 personal_info 对象。


//按 last name 排序
std::sort( vec.begin(), vec.end(), boost::bind(
                                                                     std::less<std::string>(),
                                                                     boost::bind(&personal_info::surname,_1),
                                                                     boost::bind(&personal_info::surname,_2)
                                                                  )
            );
//在前面的例子中，为什么创建了两个相同的绑定器，而不是创建一个绑定器对象然后使用两次？
//答案是，因为我们不知道 bind 所创建的绑定器的精确类型(它是由实现定义的)，我们没有方法为它声明一个变量。
//还有，这个类型通常都非常复杂，因为它的署名特征包括了函数 bind 中所有的类型信息(自动推断的)。
//但是，可以用另外一个工具来保存得到的函数对象，例如来自 Boost.Function 的工具
/*------------------------boost bind a<x<y----------------------------*/

std::vector<int> ints;

ints.push_back(7);
ints.push_back(4);
ints.push_back(12);
ints.push_back(10);

int count=std::count_if( ints.begin(), ints.end(), boost::bind(
   								std::logical_and<bool>(),   //逻辑与(std::logical_and)
    								boost::bind(std::greater<int>(),_1,5),  //大于(std::greater)
    								boost::bind(std::less_equal<int>(),_1,10)   //小于等于(std::less_equal)
    							         )
                                  );

std::cout <<"大于5且小于等于10的数有 " <<count <<" 个"<< '\n';

std::vector<int>::iterator int_it=std::find_if( ints.begin(), ints.end(), boost::bind(
										      std::logical_and<bool>(),
    										      boost::bind(std::greater<int>(),_1,5),
    										      boost::bind(std::less_equal<int>(),_1,10)
    										     )
                                                                 );

if (int_it!=ints.end()) 
{
  std::cout << *int_it << '\n';
}
//
//
std::list<double> values;
values.push_back(10.0);
values.push_back(100.0);
values.push_back(1000.0);
//提供了用一个参数调用两个函数的方法，把最里面的函数返回的结果传递给第一个函数
//把值增加10%，然后再减少10%
std::transform( values.begin(), values.end(), values.begin(),
  		boost::bind(
           			      std::multiplies<double>(),0.90,                                       //在外边的后被调用
    			      boost::bind<double>(
      						     std::multiplies<double>(),_1,1.10  //在里面的先被调用
      						    )
    			      )
  		);
std::copy( values.begin(), values.end(), std::ostream_iterator<double>(std::cout," "));
//显示bind函数的内部运行：

std::cout<<endl<<"显示bind函数的内部运行(没有采用ref/cref)：------"<<endl;
tracer t;
boost::bind(&tracer::print,t,_1)(std::string("I'm called on a copy of t\n"));
//如果我们使用的对象的拷贝动作代价昂贵，我们也许就不能这样用 bind 了。但是，拷贝还是有优点的。
//它意味着 bind 表达式以及由它所得到的绑定器不依赖于原始对象(在这里是 t)的生存期，这通常正是想要的
//
//要避免复制，我们必须告诉 bind 我们想传递引用而不是它所假定的传值。
//我们要用 boost::ref 和 boost::cref (分别用于引用和 const 引用)来做到这一点
std::cout<<"采用ref/cref的bind：-----"<<endl;
tracer ref_t;
//有了ref/cref，少了很多复制，但同时也意味着绑定器现在要依赖于 tracer 实例ref_t的生存期了
boost::bind(&tracer::print,boost::ref(ref_t),_1) (std::string("I'm called directly on ref_t\n"));

//还有一种避免复制的方法；就是通过指针来传递参数而不是通过值来传递。\
//std::cout<<"采用指针作为第二参数的的bind,也少了很多复制：-----"<<endl;
tracer Point_t;
boost::bind(&tracer::print,&Point_t,_1)(
std::string("I'm called directly on Point_t\n"));


//可以象使用非虚拟函数一样使用虚拟函数，即把它绑定到最先声明该成员函数为虚拟的基类的那个虚拟函数上。
//这个绑定器就可以用于所有的派生类。如果你绑定到其它派生类，你就限制了可以使用这个绑定器的类
std::cout<<"也可绑定虚拟函数（基类和派生类不同的函数）：------"<<endl;
derived derived_d;
base base_b;
boost::bind(&base::print,_1)(base_b);
boost::bind(&base::print,_1)(derived_d);


//绑定到成员变量,这里绑定map的值（也就是map的second）
std::cout<<"绑定到成员变量:-----"<<endl;
typedef std::map<int,std::string> my_map;
my_map my_map1;
my_map1[0]="Boost";
my_map1[1]="Bind";
std::for_each( my_map1.begin(), my_map1.end(), 
	          boost::bind(&print_string, boost::bind(&std::map<int,std::string>::value_type::second,_1))
	        );
//以下的代码为了说明不要滥用bind，有时用仿函数更加易读：
std::map<std::string,std::vector<int> > m;
m["Strange?"].push_back(1);
m["Strange?"].push_back(2);
m["Strange?"].push_back(3);
m["Weird?"].push_back(4);
m["Weird?"].push_back(5);

std::for_each(m.begin(),m.end(), boost::bind(&print,&std::cout,
      					           boost::bind(&std::vector<int>::size,
       							      boost::bind(
          									&std::map<std::string,std::vector<int> >::value_type::second,_1)
       							      )
      					           )
                   );
//以上太复杂，以下用仿函数更加直观
cout<<"我是仿函数！！！更加直观------"<<endl;
std::for_each(m.begin(),m.end(),print_size(std::cout));
/**************************************************************************/
typedef std::map<std::string,std::vector<int> > map_type;
  map_type m_s_i;
  m_s_i["Strange?"].push_back(1);
  m_s_i["Strange?"].push_back(2);
  m_s_i["Strange?"].push_back(3);
  m_s_i["Weird?"].push_back(4);
  m_s_i["Weird?"].push_back(5);

  std::for_each( m_s_i.begin(), m_s_i.end(),boost::bind(
  	                                                                      print_size_no_status(),boost::ref(std::cout),_1
  	                                                                    )
                     );	

int xbind = 2, ybind = 4;
bind(swappp, xbind, ybind)();
bind(swappp, _2, _1)(xbind, ybind);
PointA Pa, &ra = Pa;
PointA *Pp = &Pa;
//为什么linux下不可以，windows下可以呢？
//类
bind(&PointA::xy, Pa, _1, 20)(10); //³ÉÔ±º¯ÊýÇ°ÒªŒÓ&£¬±íÃ÷ÊÇ³ÉÔ±º¯ÊýÖžÕë¡£
//类引用
bind(&PointA::xy, ra, _2, _1)(20,10);
//类指针
bind(&PointA::xy, Pp, _1, _2)(10,20);


/*-------------------------------------bind+ref-------------------------------------------------------------*/
std::cout << "bind_ref测试"<< endl;
//这里没有输出？？？？？/
bind(&PointA::xy, Pp, boost::cref(xbind), boost::cref(ybind));

time_t t_C = time(0);
char tmp[64];
strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A 本年第%j天 %z",localtime(&t_C) );
puts( tmp ); //puts()函数用来向标准输出设备(屏幕)写字符串并换行
/*
size_t strftime(char *strDest, size_t maxsize, const char *format, const struct tm *timeptr);
根据格式字符串生成字符串。
struct tm *localtime(const time_t *timer);
取得当地时间，localtime获取的结果由结构tm返回
返回的字符串可以依下列的格式而定：
%a 星期几的缩写。Eg:Tue
%A 星期几的全名。 Eg: Tuesday
%b 月份名称的缩写。
%B 月份名称的全名。
%c 本地端日期时间较佳表示字符串。
%d 用数字表示本月的第几天 (范围为 00 至 31)。日期
%H 用 24 小时制数字表示小时数 (范围为 00 至 23)。
%I 用 12 小时制数字表示小时数 (范围为 01 至 12)。
%j 以数字表示当年度的第几天 (范围为 001 至 366)。
%m 月份的数字 (范围由 1 至 12)。
%M 分钟。
%p 以 ''AM'' 或 ''PM'' 表示本地端时间。
%S 秒数。
%U 数字表示为本年度的第几周，第一个星期由第一个周日开始。
%W 数字表示为本年度的第几周，第一个星期由第一个周一开始。
%w 用数字表示本周的第几天 ( 0 为周日)。
%x 不含时间的日期表示法。
%X 不含日期的时间表示法。 Eg: 15:26:30
%y 二位数字表示年份 (范围由 00 至 99)。
%Y 完整的年份数字表示，即四位数。 Eg:2008
%Z(%z) 时区或名称缩写。Eg:中国标准时间
%% % 字符。 
 */
/**************---------------C++11特性---------------*****************************/
auto i11=10;
cout<<"I am C++11特性, auto i11=10:--"<<i11<<endl;
return 0;//
}      


//模板
template<typename T>
void swapp(T& rx,T& ry)
{//引用作为参量的函数
	T tmp;
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


void swappp(int& rx, int& ry){//ref and bind
	std::cout <<"交换之前----x:" << rx << ",y:" << ry << "\n";
	int tmp = rx;
	rx = ry;
	ry = tmp;
	std::cout << "交换之后----x:" << rx << ",y:" << ry << "\n";
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


void nine_arguments(int i1,int i2,int i3,int i4,int i5,int i6,int i7,int i8, int i9) 
{
  std::cout << i1 << i2 << i3 << i4 << i5
    << i6 << i7 << i8 << i9 << '\n';
}
void print_string(const std::string& s) {
  std::cout << s << '\n';
}
