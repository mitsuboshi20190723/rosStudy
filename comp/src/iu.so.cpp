/*
 * 2023.11.3
 * iu.so.cpp
 * ver.1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <chrono>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#define SO_TOPIC_NAME "chatter_so"

namespace comp
{

class IU : public rclcpp::Node
{
public:
	__attribute__ ((visibility("default")))
//	COMPOSITION_PUBLIC
	explicit IU(const rclcpp::NodeOptions & opt) : Node("iu_so", opt)
	{
		auto publish_message = [this]() -> void
		{
			auto msg = std::make_unique<std_msgs::msg::String>();
			msg->data = "Hello world!";

			RCLCPP_INFO(this->get_logger(), "SO say %s", msg->data.c_str());
			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>(SO_TOPIC_NAME, qos);
		timer_ = create_wall_timer(std::chrono::milliseconds(500), publish_message);
	}

private:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

} /* namespace comp */

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(comp::IU)
