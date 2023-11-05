/*
 * 2023.11.3
 * test_kiku.cpp
 * ver.1.1
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <cstdio>
#include <memory>

#include <rclcpp/rclcpp.hpp>
#include "collatz/collatz.hpp"


int main(int argc, char **argv)
{
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);

	auto node = std::make_shared<Listener>("test_chat");
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}
