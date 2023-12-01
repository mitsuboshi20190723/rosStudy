/*
 *  2023.12.2
 *  servoctl.cpp
 *  ver.0.3
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <string>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "rclcpp_components/register_node_macro.hpp"

#define DEFAULT_TOPIC "chatter0"

namespace jsrc
{

class Sctl : public rclcpp::Node
{
private :
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr sub_;

	void p2s(const geometry_msgs::msg::Point::UniquePtr pnt);

public :
	explicit Sctl(const rclcpp::NodeOptions &opt);
	~Sctl();
};


void Sctl::p2s(const geometry_msgs::msg::Point::UniquePtr pnt)
{
	double deg;
	auto msg = std::make_unique<std_msgs::msg::String>();

	deg = pnt->x * 150;
	if(std::abs(deg) > 130) deg *= 130/std::abs(deg);

	msg->data = std::to_string(deg);
	pub_->publish(std::move(msg));
}


Sctl::Sctl(const rclcpp::NodeOptions &opt) : Node("SCTL", opt)
{
	rclcpp::QoS qos(rclcpp::KeepLast(10));

	pub_ = create_publisher<std_msgs::msg::String>(DEFAULT_TOPIC, qos);

	auto cb = std::bind(&Sctl::p2s, this, std::placeholders::_1);
	sub_ = create_subscription<geometry_msgs::msg::Point>("testchat", qos, cb);
}

Sctl::~Sctl(){}

} /* namespace jsrc */

RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::Sctl)