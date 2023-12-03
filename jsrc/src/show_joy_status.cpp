/*
 * 2023.12.3
 * show_joy_status.cpp
 * ver.1.0
 * Kunihito Mitsuboshi
 * license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

/* $ ros2 topic echo /joy */

#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joy.hpp>


namespace jsrc
{

class ShowJoyStatus : public rclcpp::Node
{
public:
	explicit ShowJoyStatus(const rclcpp::NodeOptions &opt) : Node("SJS", opt)
	{
		auto callback = [this](const sensor_msgs::msg::Joy::UniquePtr j) -> void
		{
			sprintf(s_,     "        %5.2f                    %5.2f           \n", j->axes[2], j->axes[5]);
			sprintf(s_+50,  "         %3d                      %3d            \n", j->buttons[4], j->buttons[5]);
			sprintf(s_+100, "                  %3d    %3d                     \n", j->buttons[6], j->buttons[7]);
			sprintf(s_+150, "        %5.2f                     %3d            \n",         P(j->axes[7]),               j->buttons[3]);
			sprintf(s_+200, "   %5.2f     %5.2f           %3d       %3d       \n", P(j->axes[6]), N(j->axes[6]), j->buttons[2], j->buttons[1]);
			sprintf(s_+250, "        %5.2f                     %3d            \n",         N(j->axes[7]),               j->buttons[0]);
			sprintf(s_+300, "                                                 \n");
			sprintf(s_+350, "        %5.2f                    %5.2f           \n",         P(j->axes[1]),               P(j->axes[4]));
			sprintf(s_+400, "   %5.2f     %5.2f          %5.2f     %5.2f      \n", P(j->axes[0]), N(j->axes[0]), P(j->axes[3]), N(j->axes[3]));
			sprintf(s_+450, "        %5.2f                    %5.2f           \n",         N(j->axes[1]),               N(j->axes[4]));
			
			RCLCPP_INFO(this->get_logger(), "JOY STATUS\n%s\n", s_);
		};
		
		rclcpp::QoS qos(rclcpp::KeepLast(10));
		sub_ = create_subscription<sensor_msgs::msg::Joy>("joy", qos, callback);
	}

private:
	double P(double f){ return f>0.0 ? f : 0.0; } /* positive */
	double N(double f){ return f<0.0 ? f : 0.0; } /* negative */
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub_;
	char s_[500 + 1];
};

} /* namespace jsrc */


#include "rclcpp_components/register_node_macro.hpp"
RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::ShowJoyStatus)
