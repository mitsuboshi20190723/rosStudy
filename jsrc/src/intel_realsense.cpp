/*
 *  2023.11.25
 *  intel_realsense.cpp
 *  ver.0.3
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define PATH4CAPTURE "/dev/video0"
#define PATH4CASCADE "/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
//                   "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
//                        ^^^^^^


int main(int argc, char **argv)
{
	int t, d;
	double w, h, f;
	cv::Mat img;
	cv::CascadeClassifier cascade;
	std::vector<cv::Rect> faces;
	cv::Point left_up, right_down;
	cv::Size wh;
	std::string str;

	cv::VideoCapture cap(PATH4CAPTURE);
	if(!cap.isOpened()) return -1;

	w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	f = cap.get(cv::CAP_PROP_FPS);
	t = cap.get(cv::CAP_PROP_FORMAT);
	std::cout << "w=" << w << ",h=" << h << ",fps=" << f << std::endl;
	std::cout << "FORMAT=" << t << std::endl;

	cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	cap.set(cv::CAP_PROP_FPS, 30);
//	cap.set(cv::CAP_PROP_FORMAT, 16);


	cascade.load(PATH4CASCADE);

	wh = cv::Size((int)w, (int)h);

//	cv::namedWindow("camera", cv::WINDOW_AUTOSIZE);
	for(int cnt=0; ; cnt++)
	{
		cap >> img;

		cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(50, 50));

		for(int i=0; i<faces.size(); i++)
		{
			left_up = cv::Point(faces[i].x, faces[i].y);
			right_down = cv::Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height);
			cv::rectangle(img, left_up, right_down, cv::Scalar(0,0,255), 3);
		}
		str = "frame counter : " + std::to_string(cnt);
		cv::putText(img, str, cv::Point(10,22), 1, 1.0, cv::Scalar(0,255,0));

		str = "passed " + std::to_string((float)d/1000000) + " seconds";
		cv::putText(img, str, cv::Point(330,22), 1, 1.0, cv::Scalar(255,255,255));

		cv::imshow("webcamera  ( q : quit )", img);

//		if(cv::waitKey(30) >= 0) break;
		const int key = cv::waitKey(1);
		if(key == 'q') break; // 113
		
//		std::this_thread::sleep_for(std::chrono::milliseconds((int)(1000/f)));
	}
	
	cv::destroyAllWindows();
	cap.release();

	return 0;
}