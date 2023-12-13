/*
 *  2023.12.14
 *  video.cpp
 *  ver.1.2
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "rclcpp_components/register_node_macro.hpp"


#define JSRC_FRAME_WIDTH 640
#define JSRC_FRAME_HEIGHT 480
#define JSRC_FPS 30

#define PATH4CAP "/dev/video0"
#define PATH4CASCADE "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
#define DEFAULT_TOPIC "vctl"

namespace jsrc
{

class Video : public rclcpp::Node
{
private :
	cv::VideoCapture cap_;
	cv::Mat img_;
	cv::CascadeClassifier cascade_;
	rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;

	void imag2point(); /* call back */

public :
	explicit Video(const rclcpp::NodeOptions &opt);
	~Video();
};


void Video::imag2point()
{
	unsigned long i, biggest(0);
	double s;
	geometry_msgs::msg::Point p; // p = std::make_unique<geometry_msgs::msg::Point>();
	std::vector<cv::Rect> faces;

	cap_ >> img_;

	cascade_.detectMultiScale(img_, faces, 1.1, 3, 0, cv::Size(50, 50));

	if(faces.size() == 0)
	{
		p.x = p.y = p.z = -1.0;
	}
	else
	{
		p.z = (double)faces[0].width * (double)faces[0].height;
		for(i=0; i<faces.size(); i++)
		{
			RCLCPP_INFO(this->get_logger(), "Find face %lu", i);

			s = (double)faces[i].width * (double)faces[i].height;
			if(p.z < s){biggest = i; p.z = s;}
		}

		p.x = ((double)faces[biggest].x + (double)faces[i].width/2);
		p.y = ((double)faces[biggest].y + (double)faces[i].height/2);

		RCLCPP_INFO(this->get_logger(), "Face locate ( %lf, %lf )", p.x, p.y);

		p.x -= JSRC_FRAME_WIDTH/2; p.x /= JSRC_FRAME_WIDTH/2;
		p.y -= JSRC_FRAME_HEIGHT/2; p.y /= JSRC_FRAME_HEIGHT/2;

		RCLCPP_INFO(this->get_logger(), "Control amount ( %lf, %lf )", p.x, p.y);
	}

	pub_->publish(std::move(p));
}


Video::Video(const rclcpp::NodeOptions &opt) : Node("VDO", opt) // int main(int argc, char **argv)
{
	auto path4cap = this->declare_parameter<std::string>("camera_path", PATH4CAP);

	cap_.open(path4cap);
	if(!cap_.isOpened())
	{
		RCLCPP_ERROR(this->get_logger(), "Cannot open %s.", path4cap.c_str());
		exit(0);
	}

	cap_.set(cv::CAP_PROP_FRAME_WIDTH, JSRC_FRAME_WIDTH);
	cap_.set(cv::CAP_PROP_FRAME_HEIGHT, JSRC_FRAME_HEIGHT);
	cap_.set(cv::CAP_PROP_FPS, JSRC_FPS);
//	cap_.set(cv::CAP_PROP_FORMAT, 16);

	auto path4cascade = this->declare_parameter<std::string>("cascade_path", PATH4CASCADE);
	cascade_.load(path4cascade);

	rclcpp::QoS qos(rclcpp::KeepLast(10));
	pub_ = create_publisher<geometry_msgs::msg::Point>(DEFAULT_TOPIC, qos);

	auto cb = std::bind(&Video::imag2point, this);
	timer_ = create_wall_timer(std::chrono::milliseconds(1000), cb);
}


Video::~Video() // return
{
	cap_.release();
}

} /* namespace jsrc */

RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::Video)
