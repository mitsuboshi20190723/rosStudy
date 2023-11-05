/*
 * 2023.11.5
 * calculate.cpp
 * ver.0.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>


namespace collatz
{

class Calculate : public rclcpp::Node
{
public:
	explicit Calculat(const rclcpp::NodeOptions & opt) : Node("CALCULATE", opt)
	{
		auto callback = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
			RCLCPP_INFO(this->get_logger(), "I heard %s", msg->data.c_str());
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>("chatter", qos, callback);
	}

private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

} /* namespace collatz */

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(collatz::Calculat)
