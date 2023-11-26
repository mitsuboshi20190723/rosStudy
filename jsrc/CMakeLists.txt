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

add_library(image_controller SHARED src/image_controller.cpp)
target_compile_definitions(image_controller PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(image_controller rclcpp rclcpp_components std_msgs geometry_msgs OpenCV)
rclcpp_components_register_nodes(image_controller "jsrc::ImageController")

add_library(ptrl SHARED src/ptrl.cpp)
target_compile_definitions(ptrl PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(ptrl rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(ptrl "jsrc::PanTiltRightLeft")

add_library(pantilt SHARED src/pantilt.cpp)
target_compile_definitions(pantilt PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(pantilt rclcpp rclcpp_components std_msgs)
# target_link_libraries(pantilt ics3)
rclcpp_components_register_nodes(pantilt "jsrc::PanTilt")


install(TARGETS
	show_joy_status image_controller ptrl pantilt
	#  EXPORT export_minimal_comp_node
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

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
