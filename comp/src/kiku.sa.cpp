/*
 * 2020.10.8
 * kiku.sa.cpp
 * ver 1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class Listener : public rclcpp::Node
{
public:
	explicit Listener(const std::string & topic_name) : Node("kiku.sa")
	{
		auto callback = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
			RCLCPP_INFO(this->get_logger(), "KIKUSA : %s", msg->data.c_str());
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>(topic_name, qos, callback);
	}

private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

int main(int argc, char * argv[])
{
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);

	auto node = std::make_shared<Listener>("chatter.sa");
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}
