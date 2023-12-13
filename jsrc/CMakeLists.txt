cmake_minimum_required(VERSION 3.5)
project(jsrc)

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
find_package(sensor_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(OpenCV REQUIRED) # COMPONENTS core highgui


#include_directories(include)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(show_joy_status SHARED src/show_joy_status.cpp)
target_compile_definitions(show_joy_status PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(show_joy_status rclcpp rclcpp_components std_msgs sensor_msgs)
rclcpp_components_register_nodes(show_joy_status "jsrc::ShowJoyStatus")

add_library(video SHARED src/video.cpp)
target_compile_definitions(video PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(video rclcpp rclcpp_components std_msgs geometry_msgs OpenCV)
rclcpp_components_register_nodes(video "jsrc::Video")

add_library(servo_control SHARED src/servo_control.cpp)
target_compile_definitions(servo_control PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(servo_control rclcpp rclcpp_components std_msgs sensor_msgs geometry_msgs)
rclcpp_components_register_nodes(servo_control "jsrc::ServoControl")

#add_library(ptrl SHARED src/ptrl.cpp)
#target_compile_definitions(ptrl PRIVATE "COMPOSITION_BUILDING_DLL")
#ament_target_dependencies(ptrl rclcpp rclcpp_components std_msgs)
#rclcpp_components_register_nodes(ptrl "jsrc::PanTiltRightLeft")


install(TARGETS
	show_joy_status video servo_control # ptrl
	#  EXPORT export_minimal_comp_node
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

add_executable(ros_pantilt src/ros_pantilt.cpp)
ament_target_dependencies(ros_pantilt rclcpp std_msgs)
target_link_libraries(ros_pantilt ics3)
install(TARGETS ros_pantilt DESTINATION lib/${PROJECT_NAME})

add_executable(kondo_servo src/kondo_servo.cpp)
target_link_libraries(kondo_servo ics3)
# ~/workspace/ros2/build/jsrc/kondo_servo

add_executable(intel_realsense src/intel_realsense.cpp)
target_link_libraries(intel_realsense ${OpenCV_LIBS})
# ~/workspace/ros2/build/jsrc/intel_realsense

install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
