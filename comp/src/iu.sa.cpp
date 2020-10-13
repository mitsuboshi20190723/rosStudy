/*
 * 2020.10.8
 * iu.sa.cpp
 * ver 1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class Talker : public rclcpp::Node
{
public:
	explicit Talker(const std::string & topic_name) : Node("iu_sa")
	{
		auto publish_message = [this]() -> void
		{
			auto msg = std::make_unique<std_msgs::msg::String>();
			msg->data = "SA say Hello world!";

			RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>(topic_name, qos);
		timer_ = create_wall_timer(std::chrono::milliseconds(500), publish_message);
	}

private:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);

	auto node = std::make_shared<Talker>("chatter_sa");
	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}
