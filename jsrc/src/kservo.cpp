/*
 *  2020.10.4
 *  kservo.cpp
 *  ver 0.5
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */
/*
 *  ~/tools/libics3/script/setup.sh
 *  sudo chmod o+rw /dev/ttyUSB0
 *  ~/workspace/ros2/build/jsrc/kservo
 */
#include <iostream>

#include <iomanip>
#include <vector>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#include <stdexcept>
#include <fstream>
#include <chrono>
#include <thread>
#include <ics3/ics>

#define JOY_DEV "/dev/input/js0"
#define SERVO_DEV "/dev/ttyUSB0"

int main(int argc, char *argv[])
{
	int joy_fd(-1), num_of_axis(0), num_of_buttons(0);
	auto servo_id(0), servo_d(0), servo_a(0);

	char name_of_joystick[80];
	std::vector<char> joy_button;
	std::vector<int> joy_axis;

	if((joy_fd=open(JOY_DEV,O_RDONLY)) < 0)
	{
		std::cerr << "Failed to open " << JOY_DEV << std::endl;
		return -1;
	}
	ioctl(joy_fd, JSIOCGAXES, &num_of_axis);
	joy_axis.resize(num_of_axis,0);
	ioctl(joy_fd, JSIOCGBUTTONS, &num_of_buttons);
	joy_button.resize(num_of_buttons,0);
	ioctl(joy_fd, JSIOCGNAME(80), &name_of_joystick);

	std::cout << "Joystick : " << name_of_joystick << std::endl << "  axis : " << num_of_axis << std::endl << "  buttons : " << num_of_buttons << std::endl;

//	fcntl(joy_fd, F_SETFL, O_NONBLOCK);   // using non-blocking mode

//	if servo open error
	ics::ICS3 servo {SERVO_DEV, ics::Baudrate::RATE115200()};

	servo_id = servo.getID();
	std::cout << "KONDO SERVO ID : " << (int)servo_id << std::endl;

/*
	try {
		auto rom = s.getRom(id);

		std::cout << "SIZE OF ROM : " << sizeof(rom) << std::endl;
		std::fstream f;
		f.open("kondo.rom", std::ios::out|std::ios::binary);
		f.write((const char*)&rom, sizeof(rom));
		f.close();
	}
	catch (...) {
		std::cout << "Error" << std::endl;
		std::exit(1);
	}
*/
	while(true)
	{
		js_event js;
		read(joy_fd, &js, sizeof(js_event));
		switch (js.type & ~JS_EVENT_INIT)
		{
		case JS_EVENT_AXIS :
//			if((int)js.number>=joy_axis.size())  {std::cerr<<"err:"<<(int)js.number<<std::endl; continue;}
			joy_axis[(int)js.number] = js.value;
			break;
		case JS_EVENT_BUTTON :
//			if((int)js.number>=joy_button.size())  {std::cerr<<"err:"<<(int)js.number<<std::endl; continue;}
			joy_button[(int)js.number] = js.value;
			break;
		}

		std::cout << std::endl;
		std::cout << "axis0 : " << joy_axis[0] << std::endl;
		std::cout << "btn 1 : " << (int)joy_button[1] << std::endl;
		std::cout << "btn 2 : " << (int)joy_button[2] << std::endl;

		servo_d = (int)(joy_axis[0]/300);
//		servo_a = (int)(joy_axis[0]/10 + 7500);
//		std::cout << "input DEGREE : "; std::cin >> servo_d;
//		servo.move(servo_id, ics::Angle::newDegree(servo_d));

//		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		auto ans = servo.move(servo_id, ics::Angle::newDegree(servo_d));
		std::cout << "POS = " << ans.getRaw() << std::endl;

		usleep(500);
	}

	close(joy_fd);
//	servo close


	return(0); // return 0;
}
