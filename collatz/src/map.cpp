/*
 * 2023.11.5
 * map.cpp
 * ver.0.2
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <chrono>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace collatz
{

class Map : public rclcpp::Node
{
public:
	explicit Map(const rclcpp::NodeOptions &opt) : Node("MAP", opt), count_(0)
	{
		auto publish_message = [this]() -> void
		{
			count_++;
			auto msg = std::make_unique<std_msgs::msg::String>();
			msg->data = /*"Rady " + */ std::to_string(count_);

			RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>("chatter", qos);
		timer_ = create_wall_timer(std::chrono::milliseconds(1000), publish_message);
	}

private:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
	long count_;
};

} /* namespace collatz */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(collatz::Map)