/*
 *  2023.11.27
 *  ros_pantilt.cpp
 *  ver.0.4
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <string>
#include <ics3/ics>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

////////namespace jsrc
////////{

#define SERVO_DEV "/dev/ttyUSB0"
#define DEFAULT_TOPIC "chatter0"


class PanTilt : public rclcpp::Node
{
private :
	float deg_;
	ics::ID id_;
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;

	void rot_servo(const std_msgs::msg::String::UniquePtr msg); /* call back */

public :
	explicit PanTilt(const rclcpp::NodeOptions &opt);
	~PanTilt();
};


vuid PanTilt::rot_servo(const std_msgs::msg::String::UniquePtr msg)
{
	if(1) RCLCPP_WARN(this->get_logger(), "No servo found!");
	else
	{
		id_ = s_.getID();
		deg_ = 0;
		s_.move(3, ics::Angle::newDegree(deg_));

		RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
	}
}


PanTilt::PanTilt(const rclcpp::NodeOptions &opt) : Node("PANTILT", opt)
{
	ics::ICS3 s_{SERVO_DEV, ics::Baudrate::RATE115200()};

	rclcpp::QoS qos(rclcpp::KeepLast(10));
	auto cb = std::bind(&PanTilt::rot_servo, this);
	sub_ = create_subscription<std_msgs::msg::String>(DEFAULT_TOPIC, qos, cb);
}

PanTilt::~PanTilt()
{
}

////////} /* namespace jsrc */
////////#include "rclcpp_components/register_node_macro.hpp"
////////RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::PanTilt)

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);
	PanTilt node;

	rclcpp::shutdown();
	return 0;
}
