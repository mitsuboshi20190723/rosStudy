/*
 * 2023.11.5
 * collatz.hpp
 * ver.1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <chrono>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>


class Talker : public rclcpp::Node
{
public:
//	explicit Talker(const rclcpp::NodeOptions & opt) : Node("test_iu", opt)
	explicit Talker(const std::string & topic_name) : Node("test_iu")
	{
		auto publish_message = [this]() -> void
		{
			auto msg = std::make_unique<std_msgs::msg::String>();
			msg->data = "Hello world!";

			RCLCPP_INFO(this->get_logger(), "TEST IU say %s", msg->data.c_str());
			pub_->publish(std::move(msg));
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		pub_ = create_publisher<std_msgs::msg::String>(topic_name, qos);
		timer_ = create_wall_timer(std::chrono::milliseconds(1000), publish_message);
	}

private:
	rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;
};



class Listener : public rclcpp::Node
{
public:
//	explicit Listener(const rclcpp::NodeOptions & opt) : Node("kiku", opt)
	explicit Listener(const std::string & topic_name) : Node("test_kiku")
	{
		auto callback = [this](const std_msgs::msg::String::UniquePtr msg) -> void
		{
			RCLCPP_INFO(this->get_logger(), "TEST KIKU hear %s", msg->data.c_str());
		};

		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<std_msgs::msg::String>(topic_name, qos, callback);
	}

private:
	rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;
};

