//日期和时间
//stdlib和boost有许多处理日期和时间的功能，这里是一些常见的用法示例。
#include<boost/date_time/gregorian/gregorian.hpp>
//使用gregorian命名空间,它包含处理公历日期的类和函数
#include<catch_amalgamated.hpp>
//1.创建日期对象
void createDateExample() {
	using namespace boost::gregorian;
	date d1(2024, 6, 15); //使用年、月、日创建日期
	//使用非成员函数根据系统的时区设置和UTC日获取当前日期
	auto d = boost::gregorian::day_clock::local_day();
	auto u = boost::gregorian::day_clock::universal_day();
	std::cout << "Local day: " << to_simple_string(d) << std::endl;
	std::cout << "Universal day: " << to_simple_string(u) << std::endl;
	date d2 = from_string("2024-12-35"); //从字符串创建日期
	date d3 = day_clock::local_day(); //获取当前本地日期
	std::cout << "Date 1: " << to_simple_string(d1) << std::endl;
	std::cout << "Date 2: " << to_simple_string(d2) << std::endl;
	std::cout << "Current Date: " << to_simple_string(d3) << std::endl;
}
TEST_CASE("test date gregorian") {
	using namespace boost::gregorian;
	//测试创建日期对象
	REQUIRE_THROWS_AS(createDateExample(), std::exception);
	//使用date构造函数针对错误日期抛出异常
	REQUIRE_THROWS_AS(date(2024, 2, 30), std::exception);//2月30日不存在
	

}
//2.访问日期
void accessDateExample() {
	using namespace boost::gregorian;
	date d(2024, 6, 15);
	int year = d.year(); //获取年份
	int month = d.month(); //获取月份
	int day = d.day(); //获取日
	std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;
	//获取星期几
	int weekday = d.day_of_week(); //0=Sunday, 1=Monday, ..., 6=Saturday
	std::cout << "Weekday: " << weekday << std::endl;
}

//3.日期算术
void dateArithmeticExample() {
	using namespace boost::gregorian;
	date d1(2024, 6, 15);
	date_duration dd(10); //表示10天的持续时间
	date d2 = d1 + dd; //日期加上持续时间
	date d3 = d1 - dd; //日期减去持续时间
	std::cout << "Original Date: " << to_simple_string(d1) << std::endl;
	std::cout << "Date after adding 10 days: " << to_simple_string(d2) << std::endl;
	std::cout << "Date after subtracting 10 days: " << to_simple_string(d3) << std::endl;
}
TEST_CASE("test date access and arithmetic") {
	using namespace boost::gregorian;
	//测试访问日期
	date d(2024, 6, 15);
	REQUIRE(d.year() == 2024);
	REQUIRE(d.month() == 6);
	REQUIRE(d.day() == 15);
	REQUIRE(d.day_of_week() == 6); //2024-06-15是星期六
	//测试日期算术
	date_duration dd(10);
	date d2 = d + dd;
	date d3 = d - dd;
	REQUIRE(d2 == date(2024, 6, 25));
	REQUIRE(d3 == date(2024, 6, 5));
}

//日期区间
TEST_CASE("test date period") {
	using namespace boost::gregorian;
	date start_date(2024, 6, 1);
	date end_date(2024, 6, 30);
	date_period dp(start_date, end_date); //创建日期区间
	REQUIRE(dp.length().days() == 29); //区间长度为29天
	date d(2024, 6, 15);
	REQUIRE(dp.contains(d)); //检查日期是否在区间内
}

//其他dateTime编程
//时间编程：允许使用微秒级别的时间点和持续时间。
#include<boost/chrono/chrono.hpp>
//chrono库提供了高精度的时间点和持续时间处理功能
//1.时钟：挂钟

TEST_CASE("test clock example") {
	using namespace boost::chrono;
	system_clock::time_point now = system_clock::now();//system_clock表示系统挂钟
	std::time_t now_c = system_clock::to_time_t(now);
	REQUIRE(now_c > 0); //当前时间戳应大于0
}
#include<boost/thread.hpp>
//2.时间点和持续时间
TEST_CASE("test time point and duration") {
	using namespace boost::chrono;
	system_clock::time_point start = system_clock::now();
	//模拟一些工作
	boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	system_clock::time_point end = system_clock::now();
	duration<double> elapsed = end - start; //计算持续时间
	REQUIRE(elapsed.count() >= 0.1); //持续时间应至少为0.1秒,count()返回持续时间的数值
}
//steady_clock表示单调时钟:单调时钟表示的是一个不会被系统时间调整影响的时钟，适合测量时间间隔。
TEST_CASE("test steady clock") {
	using namespace boost::chrono;
	steady_clock::time_point start = steady_clock::now();
	//模拟一些工作
	boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	steady_clock::time_point end = steady_clock::now();
	duration<double> elapsed = end - start; //计算持续时间
	REQUIRE(elapsed.count() >= 0.1); //持续时间应至少为0.1秒,count()返回持续时间的数值
}
//high_resolution_clock表示高分辨率时钟:高分辨率时钟提供了最高精度的时间测量，适合需要精确时间点的场景。
TEST_CASE("test high resolution clock") {
	using namespace boost::chrono;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	//模拟一些工作
	boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
	high_resolution_clock::time_point end = high_resolution_clock::now();
	duration<double> elapsed = end - start; //计算持续时间
	REQUIRE(elapsed.count() >= 0.1); //持续时间应至少为0.1秒,count()返回持续时间的数值
	//也可以使用time_since_epoch()获取自纪元以来的持续时间
}


//时间点表示某个具体的时间点，而持续时间表示两个时间点之间的时间间隔。通过结合使用时间点和持续时间，可以实现复杂的时间计算和测量。
TEST_CASE("test time point and duration arithmetic") {
	using namespace boost::chrono;
	system_clock::time_point t1 = system_clock::now();
	duration<int> d1(5); //5秒的持续时间
	system_clock::time_point t2 = t1 + d1; //时间点加上持续时间
	duration<double> elapsed = t2 - t1; //计算持续时间
	REQUIRE(elapsed.count() == 5.0); //持续时间应为5秒
}

//创建持续时间的辅助函数
TEST_CASE("std::chrono suppots several units of measurement") {
	using namespace std::literals::chrono_literals;
	auto one_s = std::chrono::seconds(1);//表示一分钟
	auto thousands_ms = 1000ms;//等价字面量 还有h m s ms us ns可以使用
	auto billion_na = std::chrono::duration_cast<std::chrono::seconds>(1000000000ns);
	REQUIRE(one_s == thousands_ms);
}

//4.等待
//与sleep for使用
#include<thread>
#include<chrono>
TEST_CASE(" used to sleep") {
	using namespace std::literals::chrono_literals;
	auto start = std::chrono::system_clock::now();
	std::this_thread::sleep_for(100ms);
	auto end = std::chrono::system_clock::now();
	REQUIRE(end - start >= 100ms);
}

//5.测量时间：boost库Timer 包含auto——cpu_timer类，这是RALL对象
using std::chrono::nanoseconds;
struct Stopwatch {
	Stopwatch(nanoseconds& result) :result{result} ,
		start{std::chrono::high_resolution_clock::now()}{ }
	~Stopwatch() {
		result = std::chrono::high_resolution_clock::now() - start;//通过依赖注入获取对象生命周期时间
	}
	nanoseconds& result;
	const std::chrono::time_point<std::chrono::high_resolution_clock> start;
};
void fun(Stopwatch s) {//将对象生命周期交给函数
	int n = 1000000000;
	for (int i = 0; i < n; i++) {
		i = i * i;
	}
}
//使用实例
TEST_CASE("test Stopwatch类") {
	nanoseconds temp;
	using namespace std::literals::chrono_literals;
	Stopwatch s{ temp };
	 fun(std::move(s));
	std::cout << temp;
	REQUIRE(temp <= 100ns);
}

