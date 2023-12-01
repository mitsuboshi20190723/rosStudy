/*
 *  2023.12.2
 *  ptrl.cpp
 *  ver.0.1
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <string>
#include <chrono>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

#define DEFAULT_TOPIC "chatter0"

namespace jsrc
{

class PanTiltRightLeft : public rclcpp::Node
{
public :
	explicit PanTiltRightLeft(const rclcpp::NodeOptions &opt) : Node("PTRL", opt)
	{
		cp_ = 0;
		auto cb_string_input = [this]() -> void
		{
			auto msg = std::make_unique<std_msgs::msg::String>();

			if(cp_ == 0)
			{
				cp_ = 1;
				msg->data = "90";
			}
			else
			{
				cp_ = 0;
				msg->data = "-90";
			}

			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>(DEFAULT_TOPIC, qos);
		timer_ = create_wall_timer(std::chrono::milliseconds(5000), cb_string_input);
	}

private :
	int cp_;
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::PanTiltRightLeft)
