/*
 *  2023.11.11
 *  kondo_servo.cpp
 *  ver.0.6
 *  Kunihito Mitsuboshi
 *  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 */


#include <iostream>
//#include <iomanip>
//#include <stdexcept>
//#include <fstream>
#include <chrono>
#include <thread>
#include <ics3/ics>


#define SERVO_DEV "/dev/ttyUSB0"


int main(int argc, char *argv[])
{
	auto servo_id(0), servo_d(0);

	for(int i=0; i < argc; i++) std::cout << argv[i] << std::endl;


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
		servo_d = 500;

//		std::cout << "input DEGREE : "; std::cin >> servo_d;
//		servo.move(servo_id, ics::Angle::newDegree(servo_d));

//		std::this_thread::sleep_for(std::chrono::milliseconds(2000));

		auto ans = servo.move(servo_id, ics::Angle::newDegree(servo_d));
		std::cout << "POS = " << ans.getRaw() << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}


//	servo close


	return(0); // return 0;
}
