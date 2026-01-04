#include"AutoBrake.h"
#define BOOST_TEST_MODULE AutoBrakeTest
#include<boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE(InitialCarSpeedIsZero) {
	MockServiceBus bus;
	AutoBrake auto_brake(bus);
	BOOST_TEST(auto_brake.get_speed_mps() == 0L);
}
struct MyFIX {};
//适用于任何自定义类结构
//在宏的主体内实现单元测试的方法
BOOST_FIXTURE_TEST_CASE(MTest1, MyFIX) {//测试名称，测试装置类

}
BOOST_FIXTURE_TEST_CASE(Mytest2, MyFIX) {//测试名称，测试装置类

}
struct AutoBrakeTest {
	MockServiceBus bus;
	AutoBrake auto_brake{ bus };
};
BOOST_FIXTURE_TEST_CASE(InitialCollition, AutoBrakeTest) {
	BOOST_TEST(auto_brake.get_collision_threshold() == 5L);
}
BOOST_FIXTURE_TEST_CASE(SensitivityGreaterThanOne, AutoBrakeTest) {
	BOOST_REQUIRE_THROW(auto_brake.set_collision_threshold(0.5L),std::exception);//适用于参数无效异常
}
BOOST_FIXTURE_TEST_CASE(SpeedSaved, AutoBrakeTest) {
	bus.speed_update_callback(SpeedUpdata{ 5L });
	BOOST_TEST(auto_brake.get_speed_mps() == 5L);
	bus.speed_update_callback(SpeedUpdata{ 10L });
	BOOST_TEST(auto_brake.get_speed_mps() == 10L);
}
BOOST_FIXTURE_TEST_CASE(NOAlertWhenNotImminent, AutoBrakeTest) {
	bus.speed_update_callback(SpeedUpdata{ 10L });
	bus.car_detected_callback(CarDetected{ 100L,10L });
	BOOST_TEST(bus.commendpublished_count == 0L);
}
BOOST_FIXTURE_TEST_CASE(AlertWhenNotImminent, AutoBrakeTest) {
	auto_brake.set_collision_threshold(10L);
	bus.speed_update_callback(SpeedUpdata{ 10L });
	bus.car_detected_callback(CarDetected{ 100L,-10L });
	BOOST_TEST(bus.commendpublished_count == 1L);
}