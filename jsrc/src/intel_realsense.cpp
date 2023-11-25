/*
 *  2023.11.25
 *  intel_realsense.cpp
 *  ver.0.5
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */

#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define PATH4CAPTURE "/dev/video0"
#define PATH4CASCADE "/usr/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
//                   "/usr/local/share/opencv4/haarcascades/haarcascade_frontalface_alt.xml"
//                        ^^^^^^

void face_detect(cv::VideoCapture &cap)
{
	cv::Mat img;
	cv::CascadeClassifier cascade;
	std::vector<cv::Rect> faces;
	cv::Point left_up, right_down, center;
//	cv::Size wh;
	std::string str;
	
//	devs.set(cv::CAP_PROP_FRAME_WIDTH, 640);
//	devs.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
//	devs.set(cv::CAP_PROP_FPS, 30);
//	devs.set(cv::CAP_PROP_FORMAT, 16);


	cascade.load(PATH4CASCADE);

//	wh = cv::Size((int)w, (int)h);

	while(1)
	{
		cap >> img;

		cascade.detectMultiScale(img, faces, 1.1, 3, 0, cv::Size(50, 50));

		for(int i=0; i<(int)faces.size(); i++)
		{
			left_up = cv::Point(faces[i].x, faces[i].y);
			right_down = cv::Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height);
			center = cv::Point(faces[i].x+faces[i].width/2, faces[i].y+faces[i].height/2);
			str = faces[i].width > 220 ? "face center ( " : "( ";
			str += std::to_string(faces[i].x+faces[i].width/2) + ", " + std::to_string(faces[i].y+faces[i].height/2) + " )";
			cv::rectangle(img, left_up, right_down, cv::Scalar(0,255,0), 3);
			cv::drawMarker(img, center, cv::Scalar(0,255,0));
			cv::putText(img, str, cv::Point(faces[i].x+5, faces[i].y+15), 1, 1.0, cv::Scalar(0,255,0));
		}

		cv::imshow("webcamera  ( q : quit )", img);

		const int key = cv::waitKey(1);
		if(key == 'q') break; // 113
	}
}


int chk_arg(int c, char **v, std::vector<std::string> &n)
{
	int i;
	std::string zero(PATH4CAPTURE);

	n.push_back(zero);
	std::cout << n[0] << std::endl;
	if(c==1) return c;

	for(i=1; i<c; i++)
	{
		n[i-1].resize(10);
		n[i-1] += v[i];
		std::cout << n[i-1] << std::endl;
		n.push_back(zero);
	}
	n.pop_back();

	return c-1;
}


int main(int argc, char **argv)
{
	int i, n, t;
	double w, h, f;
	std::vector<std::string> vdp;
	std::vector<cv::VideoCapture> caps;
//	std::vector<std::thread> th;
	cv::VideoCapture cap;


	n = chk_arg(argc, argv, vdp);

	for(i=0; i<n; i++)
	{
		cap.open(vdp[i]);
		if(!cap.isOpened()) continue;

		w = cap.get(cv::CAP_PROP_FRAME_WIDTH);
		h = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		f = cap.get(cv::CAP_PROP_FPS);
		t = cap.get(cv::CAP_PROP_FORMAT);
		std::cout << vdp[i] << " : w=" << w << ", h=" << h << ", fps=" << f << ", FORMAT=" << t << std::endl;

		caps.push_back(cap);
	}


	if(caps.size() == 0)
	{
		std::cout << "No camera found." << std::endl;
		return 0;		
	}


//	std::thread th1(face_detect, caps[0]);
//	th1.join();
	face_detect(caps[caps.size()-1]);

//	cv::destroyAllWindows();
	cap.release();
	for(i=0; i<(int)caps.size(); i++) caps[i].release();

	return 0;
}