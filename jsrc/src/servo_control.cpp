/*
 *  2023.12.14
 *  servo_control.cpp
 *  ver.0.7
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <string>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/joy.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "rclcpp_components/register_node_macro.hpp"

#define DEFAULT_TOPIC "testctl"

namespace jsrc
{

class ServoControl : public rclcpp::Node
{
private :
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_to_servo_;
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_from_joy_;
	rclcpp::Subscription<geometry_msgs::msg::Point>::SharedPtr sub_from_video_;

	void j2s(const sensor_msgs::msg::Joy::UniquePtr joy);
	void p2s(const geometry_msgs::msg::Point::UniquePtr pnt);

public :
	explicit ServoControl(const rclcpp::NodeOptions &opt);
	~ServoControl();
};


void ServoControl::j2s(const sensor_msgs::msg::Joy::UniquePtr joy)
{
	int pan(3);
	double deg;
	auto msg = std::make_unique<std_msgs::msg::String>();

	deg = joy->axes[pan] * 130;
	if(std::abs(deg) > 130) deg *= 130/std::abs(deg);


	msg->data = std::to_string(deg);
	pub_to_servo_->publish(std::move(msg));
}

void ServoControl::p2s(const geometry_msgs::msg::Point::UniquePtr pnt)
{
	double deg;
	auto msg = std::make_unique<std_msgs::msg::String>();

	deg = pnt->x * 150;
	if(std::abs(deg) > 130) deg *= 130/std::abs(deg);

	msg->data = std::to_string(deg);
	pub_to_servo_->publish(std::move(msg));
}


ServoControl::ServoControl(const rclcpp::NodeOptions &opt) : Node("SCTL", opt)
{
	rclcpp::QoS qos(rclcpp::KeepLast(10));

	pub_to_servo_ = create_publisher<std_msgs::msg::String>(DEFAULT_TOPIC, qos);

	auto cb4sj = std::bind(&ServoControl::j2s, this, std::placeholders::_1);
	sub_from_joy_ = create_subscription<sensor_msgs::msg::Joy>("joy", qos, cb4sj);
	auto cb4sv = std::bind(&ServoControl::p2s, this, std::placeholders::_1);
	sub_from_video_ = create_subscription<geometry_msgs::msg::Point>("vctl", qos, cb4sv);
}

ServoControl::~ServoControl(){}

} /* namespace jsrc */

RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::ServoControl)