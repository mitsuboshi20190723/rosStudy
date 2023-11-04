cmake_minimum_required(VERSION 3.5)
project(comp)

if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)


add_executable(iu.sa src/iu.sa.cpp)
ament_target_dependencies(iu.sa rclcpp std_msgs)
install(TARGETS iu.sa DESTINATION lib/${PROJECT_NAME})

add_executable(kiku.sa src/kiku.sa.cpp)
ament_target_dependencies(kiku.sa rclcpp std_msgs)
install(TARGETS kiku.sa DESTINATION lib/${PROJECT_NAME})

add_library(iu.so SHARED src/iu.so.cpp)
ament_target_dependencies(iu.so rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(iu.so "comp::IU")

add_library(kiku.so SHARED src/kiku.so.cpp)
ament_target_dependencies(kiku.so rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(kiku.so "comp::KIKU")


install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)


ament_package()
