// Chapter10.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdexcept>
#include<exception>


//自动制动服务设计
//服务交互的POD类
struct SpeedUpdata {
    double velocity_mps;// 速度，单位米每秒
};
struct CarDetected {
    double distance_m;// 距离，单位米
    double relative_speed_mps;// 相对速度，单位米每秒
};
struct BrakeCommand {
    double time_to_collision_s;// 碰撞时间，单位秒
};
// 服务总线的发布方法类型定义
struct ServiceBus {
    void publish(const BrakeCommand& cmd) {
        std::cout << "BrakeCommand published: time_to_collision_s = " << cmd.time_to_collision_s << "s\n";// 示例输出
    }
};

//提供自动制动服务的框架类
template<typename T>
class AutoBrake {
  public:
      AutoBrake(const T& publish) 
        : collision_threshold_s{ 5.0L }, speed_mps_{ 0.0L }, publish{ publish } // 移除多余的逗号和花括号
      {}
    void observe(const SpeedUpdata& cd) {
        speed_mps_ = cd.velocity_mps;
    }// 观察到速度更新信息
    void observe(const CarDetected& cd) {
        const double relative_speed = cd.relative_speed_mps - speed_mps_;//计算相对速度
        if (relative_speed < 0) {//如果相对速度小于0，说明前方车辆在接近
            const double time_to_collision = cd.distance_m / -relative_speed;
            if (time_to_collision <= collision_threshold_s) {//如果碰撞时间小于等于阈值
                publish(BrakeCommand{ time_to_collision });//发布制动命令
            }
        }
    }// 观察到前方车辆信息
    void set_collision_threshold(double x) {
        if (x < 1.0L) throw std::exception{ "Collision less than 1" };
        collision_threshold_s = x;
    }
    double get_collision_threshold()const {
        return collision_threshold_s;
    }
    double get_speed_mps() const {//获取
        return speed_mps_;
    }
  private:
    double collision_threshold_s;//灵敏度
    double speed_mps_;//速度
    const T& publish;//保留服务总线publish方法的引用
    
};

//使用autoBrake服务的示例
//断言：单元测试的基础
// //assert_that函数
constexpr void assert_that(bool statement, const char* message) {
    if (!statement)throw std::runtime_error{ message };
}

//对初速度为0的需求编码单元测试
void initial_speed_zero() {
    AutoBrake auto_brake{ [](SpeedUpdata&) {} };
    assert_that(auto_brake.get_speed_mps() == 0.0L, "speed not eaual 0");
}
void initial_senstivity_five() {
    AutoBrake auto_brake{ [](const BrakeCommand&) {} };
    assert_that(auto_brake.get_collision_threshold() == 5L, "sensitivity is not 5");//判断碰撞阈值为5
}
//两次更新之间保存汽车速度的单元测试
void speed_remain_between_updates() {
    AutoBrake auto_brake{ [](const BrakeCommand&) {} };
    auto_brake.observe(SpeedUpdata{ 10L });
    assert_that(auto_brake.get_speed_mps() == 10L, "speed not remain between updates");
    auto_brake.observe(SpeedUpdata{ 20L });
    assert_that(auto_brake.get_speed_mps() == 20L, "speed not remain between updates");
}
//汽车制动事件单元测试
void auto_brake_event() {
    bool brake_applied = false;
    AutoBrake auto_brake{ [&brake_applied](const BrakeCommand&) {brake_applied = true; } };
    auto_brake.set_collision_threshold(2L);
    auto_brake.observe(SpeedUpdata{ 30L });//汽车以30米每秒的速度行驶
    auto_brake.observe(CarDetected{ 100L, -10L });//前方100米有一辆车，相对速度为-10米每秒
    assert_that(brake_applied, "brake not applied");
}
//灵敏度始终大于1
void senstivity_greater_than_1() {
    AutoBrake auto_brake{ [](const BrakeCommand&) {} };
    try {
        auto_brake.set_collision_threshold(0.5L);
    }
    catch (const std::exception&) {
        return;
    }
    assert_that(false, "no exception throw");
}
//测试工具：接受一个测试函数指针，并在try_catch中调用
void run_test(void(*unit_test)(), const char* name) {
    try {
        unit_test();
        printf("[+]Test %s success.\n", name);
    }
    catch (const std::exception& e) {
        printf("[-]Test failure in %s. %s.\n", name, e.what());
    }
}

int main()
{
    ServiceBus bus;//汽车服务总线
    AutoBrake auto_brake{ [&bus](const auto& cmd) {bus.publish(cmd); } };//自动制动服务，通过lambda表达式绑定服务总线的publish方法
    while (true) {
        auto_brake.observe(SpeedUpdata{ 10L });
        auto_brake.observe(CarDetected{ 250L,25L });
        break;
    }
    std::cout << "Hello World!\n";
    //assert_that(1+1>2, "helloworld!");//测试函数
    run_test(initial_speed_zero, "initial speed is 0");
    run_test(initial_senstivity_five, "initial senstivity is 5");
    run_test(senstivity_greater_than_1, "senstivity greater than 1");
    run_test(speed_remain_between_updates, "speed remain between updates");
    run_test(auto_brake_event, "auto brake event");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
