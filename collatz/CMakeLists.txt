cmake_minimum_required(VERSION 3.8)
project(collatz)

if(NOT CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)

include_directories(include)

add_executable(test_iu src/test_iu.cpp)
ament_target_dependencies(test_iu rclcpp std_msgs)
install(TARGETS test_iu DESTINATION lib/${PROJECT_NAME})

add_executable(test_kiku src/test_kiku.cpp)
ament_target_dependencies(test_kiku rclcpp std_msgs)
install(TARGETS test_kiku DESTINATION lib/${PROJECT_NAME})

add_library(map SHARED src/map.cpp)
ament_target_dependencies(map rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(map "collatz::Map")
install(TARGETS map DESTINATION lib)

add_library(calculate SHARED src/calculate.cpp)
ament_target_dependencies(calculate rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(calculate "collatz::Calculate")
# install(TARGETS calculate DESTINATION lib)

add_library(iu SHARED src/iu.cpp)
target_compile_definitions(iu PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(iu rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(iu "collatz::IU")

add_library(kiku SHARED src/kiku.cpp)
target_compile_definitions(kiku PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(kiku rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(kiku "collatz::KIKU")


install(DIRECTORY launch DESTINATION share/${PROJECT_NAME}/)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
