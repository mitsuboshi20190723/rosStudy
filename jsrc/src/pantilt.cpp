/*
 *  2023.11.11
 *  pantilt.cpp
 *  ver.0.3
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <string>
#include <ics3/ics>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>


namespace jsrc
{

class PanTilt : public rclcpp::Node
{
public :
	explicit PanTilt(const rclcpp::NodeOptions &opt) : Node("PANTILT", opt)
	{

		auto cb_rot_servo = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
			ics::ICS3 s {"/dev/ttyUSB0", ics::Baudrate::RATE115200()};
			auto d=50;
			auto id=1;
			s.move(id, ics::Angle::newDegree(d));			

			RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>("chatter0", qos, cb_rot_servo);
	}

private :
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::PanTilt)
