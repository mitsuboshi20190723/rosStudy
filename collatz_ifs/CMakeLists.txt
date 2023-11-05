cmake_minimum_required(VERSION 3.8)
project(collatz_ifs)

if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

set(MSG_FILES "msg/test.msg")

rosidl_generate_interfaces(${PROJECT_NAME} ${MSG_FILES} DEPENDENCIES std_msgs)


ament_package()
