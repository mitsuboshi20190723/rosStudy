/*
 * 2023.11.3
 * test_iu.cpp
 * ver.1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <chrono>
#include <cstdio>
#include <memory>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "collatz/collatz.hpp"


int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);

	auto node = std::make_shared<Talker>("test_chat");
	rclcpp::spin(node);
	rclcpp::shutdown();

	return 0;
}
