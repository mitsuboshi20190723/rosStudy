/*
 *  2023.11.26
 *  image_controller.cpp
 *  ver.1.0
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <rclcpp/rclcpp.hpp>
//#include <sensor_msgs/msg/image.hpp>
#include <geometry_msgs/msg/point.hpp>
#include "rclcpp_components/register_node_macro.hpp"


#define JSRC_FRAME_WIDTH 640
#define JSRC_FRAME_HEIGHT 480
#define JSRC_FPS 30

#define PATH4CAP "/dev/video0"
#define PATH4CASCADE "/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
//                   "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
#define DEFAULT_TOPIC "chatter0"

namespace jsrc
{

class ImageController : public rclcpp::Node
{
private :
	cv::VideoCapture cap_;
	cv::Mat img_;
	cv::CascadeClassifier cascade_;
	rclcpp::Publisher<geometry_msgs::msg::Point>::SharedPtr pub_;
	rclcpp::TimerBase::SharedPtr timer_;

	geometry_msgs::msg::Point imag2point(); /* call back */

public :
	explicit ImageController(const rclcpp::NodeOptions &opt);
	~ImageController();
};


geometry_msgs::msg::Point ImageController::imag2point()
{
	unsigned long i, biggest(0);
	double s;
	geometry_msgs::msg::Point p;
//	cv::Rect face;
	std::vector<cv::Rect> faces;

	cap_ >> img_;

	cascade_.detectMultiScale(img_, faces, 1.1, 3, 0, cv::Size(50, 50));

	if(faces.size() == 0)
	{
		p.x = p.y = p.z = -1;
	}
	else
	{
		p.z = faces[0].width * faces[0].height;
		for(i=0; i<faces.size(); i++)
		{
			RCLCPP_INFO(this->get_logger(), "Find face %ld", i);

			s = faces[i].width * faces[i].height;
			if(p.z < s){biggest = i; p.z = s;}
		}

		p.x = (faces[biggest].x + faces[i].width/2) / JSRC_FRAME_WIDTH;
		p.y = (faces[biggest].y + faces[i].height/2) / JSRC_FRAME_HEIGHT;
	}

	return p;
}


ImageController::ImageController(const rclcpp::NodeOptions &opt) : Node("IMGCTL", opt) // int main(int argc, char **argv)
{
	auto path4cap = this->declare_parameter<std::string>("camera_path", PATH4CAP);

	cap_.open(path4cap);
	if(!cap_.isOpened())
	{
		RCLCPP_ERROR(this->get_logger(), "Faild to open %s", path4cap.c_str());
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

	auto cb = std::bind(&ImageController::imag2point, this);
	timer_ = create_wall_timer(std::chrono::milliseconds(1000 / 30), cb);
}


ImageController::~ImageController()
{
	cap_.release();
}

} /* namespace jsrc */

RCLCPP_COMPONENTS_REGISTER_NODE(jsrc::ImageController)