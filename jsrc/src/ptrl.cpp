/*
 *  2020.10.4
 *  ptrl.cpp
 *  ver 0.1
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <cstdio>
#include <string>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

namespace jsrc
{

class ptrl : public rclcpp::Node
{
public :

	explicit ptrl(const rclcpp::NodeOptions & opt) : Node("ptrl", opt)
	{
		auto cb_string_input = [this]() -> void
		{
			auto msg = std::make_unique<std_msgs::msg::String>();

			msg->data = "pr";
//			std::scanf("pt rl %s", msg->data);

			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>("chatter0", qos);
		timer_ = create_wall_timer(std::chrono::milliseconds(2000), cb_string_input);
	}

private :
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::ptrl)
