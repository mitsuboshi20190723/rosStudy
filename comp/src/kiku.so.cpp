/*
 * 2023.11.3
 * kiku.so.cpp
 * ver.1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#define SO_TOPIC_NAME "chatter_so"

namespace comp
{

class KIKU : public rclcpp::Node
{
public:
	__attribute__ ((visibility("default")))
//	COMPOSITION_PUBLIC
	explicit KIKU(const rclcpp::NodeOptions & opt) : Node("kiku_so", opt)
	{
		auto callback = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
			RCLCPP_INFO(this->get_logger(), "SO hear %s", msg->data.c_str());
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>(SO_TOPIC_NAME, qos, callback);
	}

private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

} /* namespace comp */

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(comp::KIKU)
