/*
 *  2023.11.27
 *  kondo_servo.cpp
 *  ver.0.7
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
#include <chrono>
#include <thread>
#include <ics3/ics>


#define SERVO_DEV "/dev/ttyUSB0"


int main(int argc, char *argv[])
{
	int id(0);
	char in[50];
//	ics::ICS3 servo;
	auto servo_id(0), servo_d(0);

	for(int i=0; i<argc; i++){ std::cout << " " << argv[i]; } std::cout << std::endl;


//	if servo open error
	ics::ICS3 servo {SERVO_DEV, ics::Baudrate::RATE115200()};
//	servo = new ics::ICS3(SERVO_DEV, ics::Baudrate::RATE115200());
	
	servo_id = servo.getID();
	std::cout << "KONDO SERVO ID : " << (int)servo_id << std::endl;
//	multiple servo


	std::cout << "\nCange ID ? [yes / no] > "; std::cin >> in;
	if(in[0] == 'y')
	{
		std::cout << "input ID (0 to 31) > "; std::cin >> in;
		if(in[0] >= '0' && in[0] <= '9')
		{
			if(in[0] >= '1' && in[0] <= '3')
			{
				if(in[1] >= '0' && in[1] <= '9') id = std::atoi(in);
			}
			id = std::atoi(in);
		}
		if(id > 31) id = 31;
		std::cout << "Cange ID=" << id << " [yes / no] > "; std::cin >> in;
		if(in[0] == 'y')
		{
//			servo.setID(id);
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			servo_id = servo.getID();
			std::cout << "KONDO SERVO ID : " << (int)servo_id << std::endl;
		}
	}
	

	while(true)
	{
		std::cout << "\ninput DEGREE (-130 to 130) > "; std::cin >> in;
		if((in[0] >= 'a' && in[0] <= 'z') || (in[0] >= 'A' && in[0] <= 'Z')) return 0;

		servo_d = std::atof(in);
		if(servo_d >= -130 && servo_d <= 130)
		{
			servo.move(servo_id, ics::Angle::newDegree(servo_d));

			std::this_thread::sleep_for(std::chrono::milliseconds(2000));

			auto ans = servo.move(servo_id, ics::Angle::newDegree(servo_d));
			std::cout << "POS = " << ans.getRaw() << std::endl;
		}
	}


//	servo close

	return 0;
}
