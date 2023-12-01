/*
 *  2023.12.2
 *  pantilt.cpp
 *  ver.0.4
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <string>
#include <ics3/ics>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#define SERVO_DEV "/dev/ttyUSB0"
#define DEFAULT_TOPIC "chatter0"

namespace jsrc
{

ics::ICS3 s_{SERVO_DEV, ics::Baudrate::RATE115200()};
//ics::ID id_ = s_.getID();

class PanTilt : public rclcpp::Node
{
public :
	explicit PanTilt(const rclcpp::NodeOptions &opt) : Node("PANTILT", opt)
	{
//		ics::ICS3 s_{SERVO_DEV, ics::Baudrate::RATE115200()};

		auto cb_rot_servo = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
			if(1) RCLCPP_WARN(this->get_logger(), "No servo found!");
			else
			{
//				id_ = s_.getID();
				
				deg_ = std::atof(msg->data.c_str());
				s_.move(3, ics::Angle::newDegree(deg_));

				RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
			}
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>(DEFAULT_TOPIC, qos, cb_rot_servo);
	}

private :
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
//	ics::ID id_;
	float deg_;
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::PanTilt)
