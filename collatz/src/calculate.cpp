/*
 * 2023.11.6
 * calculate.cpp
 * ver.0.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>


namespace collatz
{

class Calculate : public rclcpp::Node
{
public:
	explicit Calculate(const rclcpp::NodeOptions &opt) : Node("CALCULATE", opt)
	{
		rclcpp::QoS q(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>("chatter", q, &call_back(msg_));
		//sub_ = create_subscription<std_msgs::msg::String>("chatter", q, std::bind(&call_back, this, std::placeholders::_1));
	}
	//~Calculate(){}

private:
	void call_back(const std_msgs::msg::String::SharedPtr msg)
	{
		RCLCPP_INFO(this->get_logger(), "Next %s +1", msg->data.c_str());
	}
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
	std_msgs::msg::String::SharedPtr s_msg_;
	std_msgs::msg::String::UniquePtr u_msg_;
};

/*
void Calculate::call_back(const std_msgs::msg::String::SharedPtr msg)
{
	RCLCPP_INFO(this->get_logger(), "Next %s +1", msg->data.c_str());
}
*/

} /* namespace collatz */

#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(collatz::Calculate)
