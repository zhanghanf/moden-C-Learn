//#define HM_NO_EXCEPTIONS 1
#include<hippomocks.h>
//#include"AutoBrake.h"
//#define CATCH_CONFIG_MAIN
#include<catch_amalgamated.hpp>
#include<iostream>
#include<stdexcept>
#include<exception>
#include<functional>

//#include<catch_amalgamated.hpp>
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

//添加服务总线接口的自动制动服务
using SpeedUpdateFunc = std::function<void(const SpeedUpdata&)>;
using CarDetectedFunc = std::function<void(const CarDetected&)>;
using PublishFunc = std::function<void(const BrakeCommand&)>;
struct IServiceBus {
    virtual void publish(const BrakeCommand& cmd) = 0;//纯虚函数，发布制动命令
    virtual ~IServiceBus() = default;//虚析构函数
    virtual void observe_speed(SpeedUpdateFunc) = 0;//观察速度更新
    virtual void observe_car(CarDetectedFunc) = 0;//观察前方车辆信息
};

class AutoBrake {
public:
    AutoBrake(IServiceBus& bus)//引用IServiceBus接口
        : collision_threshold_s{ 5.0L }, speed_mps_{ 0.0L }// 移除多余的逗号和花括号
    {
        /*
        */
        bus.observe_speed([this](const SpeedUpdata& updata) {
            speed_mps_ = updata.velocity_mps;
            });
        bus.observe_car([this, &bus](const CarDetected& cd) {//引用捕获bus才能使用bus的方法
            const auto relative_speed = cd.relative_speed_mps - speed_mps_;//计算相对速度
            if (relative_speed < 0) {//如果相对速度小于0，说明前方车辆在接近
                const double time_to_collision = cd.distance_m / -relative_speed;
                if (time_to_collision <= collision_threshold_s) {//如果碰撞时间小于等于阈值
                    bus.publish(BrakeCommand{ time_to_collision });//发布制动命令
                }
            }});
    }
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
};
//hippomock模拟对象测试


TEST_CASE("AutoBrake") {
    MockRepository mocks;
    mocks.autoExpect = false;
    auto* bus = mocks.Mock<IServiceBus>();//指定模拟对象
    CarDetectedFunc car_detected_call;
    SpeedUpdateFunc speed_call;
    //auto* bus = mocks.Mock<IServiceBus>();
    mocks.ExpectCall(bus, IServiceBus::observe_speed).Do([&](const auto& x) {
        speed_call = x;//设定期望
        });
    mocks.ExpectCall(bus, IServiceBus::observe_car).Do([&](const auto& x) {
        car_detected_call = x;//设定期望
        });
    AutoBrake auto_brake{ *bus };
    SECTION("save speed is 0") {
        REQUIRE(auto_brake.get_speed_mps() == Catch::Approx(0));
    }
    SECTION("my testA") {
        REQUIRE(auto_brake.get_speed_mps() == 0);
        CHECK(auto_brake.get_speed_mps() == 0);
    }
    SECTION("my TestB") {
        REQUIRE_THROWS(auto_brake.set_collision_threshold(0.5));
        REQUIRE(auto_brake.get_collision_threshold() == Catch::Approx(5L));
    }
    SECTION("My test3") {
        //bus.speed_update_callback(SpeedUpdata{ 100L });
        speed_call(SpeedUpdata{ 10L });
        REQUIRE(auto_brake.get_speed_mps() == Catch::Approx(10L));
    }
    SECTION("My Test4") {
        
        mocks.ExpectCall(bus, IServiceBus::publish)
            .Match([](const auto& cmd) {
            return cmd.time_to_collision_s == Catch::Approx(1); });
    }
    auto_brake.set_collision_threshold(10L);
    speed_call(SpeedUpdata{ 100L });
    car_detected_call(CarDetected{ 100L,0L });
}
    
