#include<gmock/gmock.h>
#include<gtest/gtest.h>
#include"AutoBrake.h"
//对IServiceBus进行模拟

/*

//期望
MockServiceBus naggy_mock;
::testing::NiceMock<MockServiceBus> nice_mock;
::testing::StrictMock<MockServiceBus> strick_mock;
//匹配器:模拟对象的方法接受参数时，我们对调用是否与期望匹配有较大的自由裁量权
//简单情况：使用字面量
//复杂情况下使用testing::_对象
using ::testing::_;

TEST(AutoBrakeTEST, PUblishIsCallD) {
	MockServiceBus bus;
	EXPECT_CALL(bus, publish(_));//nh
}


using ::testing::A;//tesing A适配器
TEST(AutoBrakeTest, PublishA) {
	MockServiceBus bus;
	EXPECT_CALL(bus, publish(A<BrakeCommand>()));//指定BrakeCommand来匹配这个期望
}

using ::testing::Field;
using ::testing::DoubleEq;

using ::testing::A;//tesing A适配器
TEST(AutoBrakeTest, PublishA) {
	MockServiceBus bus;
	EXPECT_CALL(bus, publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(1L)))).Times(1);//模拟将这个对象只调用1次
}
//基数：指定方法调用次数
TEST(AutoBrakeTest, PublishA) {
	MockServiceBus bus;
	EXPECT_CALL(bus, publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(1L))));
}
int main(int argc, char** argv) {
	::testing::GTEST_FLAG(throw_on_failure) = true;//某些与模拟相关的断言失败时抛出异常
	::testing::InitGoogleMock(&argc, argv);//使用命令行参数进行必要的定制
	//
}

*/
//模拟IService对象
struct MockServiceBus : IServiceBus {
	MOCK_METHOD(void, publish, (const BrakeCommand& cmd), (override));
	MOCK_METHOD(void, observe, (SpeedUpdateFunc cd), (override));
	MOCK_METHOD(void, observe, (CarDetectedFunc cd), (override));
	MOCK_METHOD(void, observe, (SpeedLimitDectedFunc cd),( override));
	//MOCK_METHOD()
};
using ::testing::_;
using ::testing::A;
using ::testing::Field;//
using ::testing::DoubleEq;//浮点数相等
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Invoke;

struct NiceAutoBrakeTest : ::testing::Test {
	NiceMock<MockServiceBus> bus;
	AutoBrake auto_brake{ bus };
};

struct StrickAutoBrakeTest : ::testing::Test {
	StrickAutoBrakeTest() {
		EXPECT_CALL(bus, observe(A<CarDetectedFunc>())).Times(1)
			.WillOnce(Invoke([this](const auto& x) {
			car_call = x;}));
		EXPECT_CALL(bus, observe(A<SpeedUpdateFunc>())).Times(1)
			.WillOnce(Invoke([this](const auto& x) {
			speed_update_call = x;
				}));;
		EXPECT_CALL(bus, observe(A<SpeedLimitDectedFunc>())).Times(1)
			.WillOnce(Invoke([this](const auto& x) {
			speed_limited_call = x;
				}));;
	}

	StrictMock<MockServiceBus> bus;
	SpeedUpdateFunc speed_update_call;
	CarDetectedFunc car_call;
	SpeedLimitDectedFunc speed_limited_call;
};

TEST_F(NiceAutoBrakeTest, AutoBrakeTest) {
	ASSERT_DOUBLE_EQ(0, auto_brake.get_speed_mps());
}
TEST_F(NiceAutoBrakeTest, InitialSensetivityIsFive) {
	ASSERT_DOUBLE_EQ(5, auto_brake.get_collision_threshold());
}
TEST_F(NiceAutoBrakeTest, InitialSensitivityThanone) {
	ASSERT_ANY_THROW(auto_brake.set_collision_threshold(0.5));
}
TEST_F(NiceAutoBrakeTest, SpeedLimitDectedIs39) {
	ASSERT_DOUBLE_EQ(39, auto_brake.get_speed());
}
TEST_F(StrickAutoBrakeTest, SpeedLimitedSet35) {
	AutoBrake auto_brake{ bus };
	speed_limited_call(SpeedLimitDected{ 35 });
	ASSERT_DOUBLE_EQ(35, auto_brake.get_speed());
}
TEST_F(StrickAutoBrakeTest, NoAlertWhennoImminent) {
	AutoBrake auto_brake{ bus };
	auto_brake.set_collision_threshold(2L);
	speed_update_call(SpeedUpdata{10L});
	car_call(CarDetected{ 1000L,50L });
	//speed_limited_call(SpeedLimitDected{ 35 });
	
}
TEST_F(StrickAutoBrakeTest, AlertWhennoImminent) {
	EXPECT_CALL(bus, publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(1.0L)))).Times(1);
	AutoBrake auto_brake{ bus };
	auto_brake.set_collision_threshold(10L);
	speed_update_call(SpeedUpdata{ 30L });
	car_call(CarDetected{ 30L,0L });
}
TEST_F(StrickAutoBrakeTest, AlertWhennoMoreSpeed) {
	EXPECT_CALL(bus, publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(0L)))).Times(1);
	AutoBrake auto_brake{ bus };
	//auto_brake.set_collision_threshold(10L);
	speed_limited_call(SpeedLimitDected{ 35 });
	speed_update_call(SpeedUpdata{ 30L });
	speed_limited_call(SpeedLimitDected{ 25 });
	//car_call(CarDetected{ 100L,0L });
}