/*
 * 2023.11.2
 * iu.cpp
 * ver.0.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <chrono>
//#include <cstdio>
//#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

using namespace std::chrono_literals;
namespace collatz
{

class IU : public rclcpp::Node
{
public:
	__attribute__ ((visibility("default")))
//	COMPOSITION_PUBLIC
	explicit IU(const rclcpp::NodeOptions & opt) : Node("iu", opt)
	{
		auto publish_message = [this]() -> void
		{
			auto msg = std::make_unique<std_msgs::msg::String>();
			msg->data = "lib Hello world!";

			RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>("chatter", qos);
		timer_ = create_wall_timer(500ms, publish_message);
	}

private:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

} /* namespace collatz */

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(collatz::IU)
