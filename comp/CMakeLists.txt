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

##include_directories(include)

add_executable(iu.sa src/iu.sa.cpp)
ament_target_dependencies(iu.sa rclcpp std_msgs)
##install(TARGETS iu.sa DESTINATION lib/${PROJECT_NAME})

add_executable(kiku.sa src/kiku.sa.cpp)
ament_target_dependencies(kiku.sa rclcpp std_msgs)
##install(TARGETS kiku.sa DESTINATION lib/${PROJECT_NAME})


add_library(iu.so SHARED src/iu.so.cpp)
target_compile_definitions(iu.so PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(iu.so rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(iu.so "jsrc::IU.so")

add_library(kiku.so SHARED src/kiku.so.cpp)
target_compile_definitions(kiku.so PRIVATE "COMPOSITION_BUILDING_DLL")
ament_target_dependencies(kiku.so rclcpp rclcpp_components std_msgs)
rclcpp_components_register_nodes(kiku.so "jsrc::KIKU.so")


install(TARGETS iu.sa kiku.sa DESTINATION lib/${PROJECT_NAME})
install(TARGETS
	iu.so kiku.so
##	EXPORT export_minimal_comp_node
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	RUNTIME DESTINATION bin
)

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
