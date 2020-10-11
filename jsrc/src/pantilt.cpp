/*
 *  2020.10.4
 *  pantilt.cpp
 *  ver 0.1
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


//#include <iostream>
#include <cstdio>
#include <string>
#include <chrono>
#include <thread>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

//#include <stdexcept>
//#include <fstream>
#include <ics3/ics>

namespace jsrc
{

class pantilt : public rclcpp::Node
{
public :

	explicit pantilt(const rclcpp::NodeOptions & opt) : Node("pantilt", opt)
	{

		auto cb_rot_servo = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
//			ics::ICS3 s {"/dev/ttyUSB0", ics::Baudrate::RATE115200()};
//			auto d=50;
//			auto id=1;

			RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());

			std::printf("say printf %s\n", msg->data.c_str());
//			s.move(id, ics::Angle::newDegree(d));
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>("chatter0", qos, cb_rot_servo);
	}

private :
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::pantilt)
