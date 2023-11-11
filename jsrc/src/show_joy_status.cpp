/*
 * 2023.11.11
 * show_joy_status.cpp
 * ver.0.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <sensor_msgs/msg/joy.hpp>

namespace jsrc
{

class ShowJoyStatus : public rclcpp::Node
{
public:
	explicit ShowJoyStatus(const rclcpp::NodeOptions &opt) : Node("SJS", opt)
	{
		auto callback = [this](const sensor_msgs::msg::Joy::UniquePtr j) -> void
		{
			RCLCPP_INFO(this->get_logger(), "%f", j->axes[0]);
//			RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<sensor_msgs::msg::Joy>("joy", qos, callback);
	}

private:
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::ShowJoyStatus)
