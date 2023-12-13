/*
 *  2023.12.12
 *  ros_pantilt.cpp
 *  ver.0.7
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
#define DEFAULT_TOPIC "testctl"


class PanTilt : public rclcpp::Node
{
private :
	float deg_;
	ics::ID id_{3};
	ics::ICS3 s_{SERVO_DEV, ics::Baudrate::RATE115200()};
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;

	void rot_servo(const std_msgs::msg::String::UniquePtr msg); /* call back */

public :
////////explicit PanTilt(const rclcpp::NodeOptions &opt);
	explicit PanTilt(const std::string &topic_name);
	~PanTilt();
};


void PanTilt::rot_servo(const std_msgs::msg::String::UniquePtr msg)
{
	if(id_ != 3) RCLCPP_WARN(this->get_logger(), "No servo found!");
	else
	{
		deg_ = std::atof(msg->data.c_str());
		s_.move(id_, ics::Angle::newDegree(deg_));

		RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
	}
}


////////PanTilt::PanTilt(const rclcpp::NodeOptions &opt) : Node("PANTILT", opt)
PanTilt::PanTilt(const std::string &topic_name) : Node("PANTILT")
{
//	using std::placeholders::_1;
//	ics::ICS3 s_{SERVO_DEV, ics::Baudrate::RATE115200()};

//	id_ = s_.getID();

	rclcpp::QoS qos(rclcpp::KeepLast(10));
	auto cb = std::bind(&PanTilt::rot_servo, this, std::placeholders::_1);
	sub_ = create_subscription<std_msgs::msg::String>(topic_name, qos, cb);
////////sub_ = create_subscription<std_msgs::msg::String>(DEFAULT_TOPIC, qos, cb);
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

	auto node = std::make_shared<PanTilt>(DEFAULT_TOPIC);
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}
