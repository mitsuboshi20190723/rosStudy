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


#include_directories(include)

add_library(iu SHARED src/iu.cpp)
target_compile_definitions(iu PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(iu rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(iu "jsrc::IU")

add_library(show_joy_status SHARED src/show_joy_status.cpp)
target_compile_definitions(show_joy_status PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(show_joy_status rclcpp rclcpp_components std_msgs sensor_msgs)
rclcpp_components_register_nodes(show_joy_status "jsrc::ShowJoyStatus")

#add_library(ptrl SHARED src/ptrl.cpp)
#target_compile_definitions(ptrl PRIVATE "COMPOSITION_BUILDING_DLL")
#ament_target_dependencies(ptrl rclcpp rclcpp_components std_msgs)
#rclcpp_components_register_nodes(ptrl "jsrc::ptrl")

#add_executable(kservo src/kservo.cpp)
#target_link_libraries(kservo ics3)

#add_library(pantilt SHARED src/pantilt.cpp)
#target_compile_definitions(pantilt PRIVATE "COMPOSITION_BUILDING_DLL")
#ament_target_dependencies(pantilt rclcpp rclcpp_components std_msgs)
#target_link_libraries(pantilt ics3)
#rclcpp_components_register_nodes(pantilt "jsrc::pantilt")


install(TARGETS
	show_joy_status
	#  EXPORT export_minimal_comp_node
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

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
