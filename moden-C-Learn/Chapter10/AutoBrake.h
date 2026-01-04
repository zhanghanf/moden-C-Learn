#pragma once
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
    virtual void observe(SpeedUpdateFunc) = 0;//观察速度更新
    virtual void observe(CarDetectedFunc) = 0;//观察前方车辆信息
};
//服务总线实现类
struct MockServiceBus : public IServiceBus {
    void publish(const BrakeCommand& cmd) override {
        commendpublished_count++;
        std::cout << "MockServiceBus: BrakeCommand published: time_to_collision_s = " << cmd.time_to_collision_s << "s\n";
        last_brake_command = cmd;
    }
    void observe(SpeedUpdateFunc func) override {
        speed_update_callback = func;
    }
    void observe(CarDetectedFunc func) override {
        car_detected_callback = func;
    }
    BrakeCommand last_brake_command{};//保存最后一个制动命令
    int commendpublished_count{};//发布命令的次数
    SpeedUpdateFunc speed_update_callback{};//速度更新回调函数
    CarDetectedFunc car_detected_callback{};//前方车辆检测回调函数
};

class AutoBrake {
public:
    AutoBrake(IServiceBus& bus)//引用IServiceBus接口
        : collision_threshold_s{ 5.0L }, speed_mps_{ 0.0L }// 移除多余的逗号和花括号
    {
        bus.observe([this](const SpeedUpdata& updata) {
            speed_mps_ = updata.velocity_mps;
            });
        bus.observe([this, &bus](const CarDetected& cd) {//引用捕获bus才能使用bus的方法
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
