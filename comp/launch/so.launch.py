#
# -*- coding: utf-8 -*-

##
 #  2023.11.4
 #  so.launch.py
 #  ver.1.2
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


# ros2 run rclcpp_components component_container
# ros2 component load /ComponentManager comp comp::KIKU -e use_intra_process_comms:=true
# ros2 component load /ComponentManager comp comp::IU -e use_intra_process_comms:=true


from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer, LoadComposableNodes
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
	container = ComposableNodeContainer(
		name="comp_container",
		namespace="",
		package="rclcpp_components",
		executable="component_container"
	)
	components = LoadComposableNodes(
		target_container=container,
		composable_node_descriptions=[
			ComposableNode(
				package="comp",
				plugin="comp::KIKU",
				extra_arguments=[{"use_intra_process_comms": True}]
			),
			ComposableNode(
				package="comp",
				plugin="comp::IU",
				extra_arguments=[{"use_intra_process_comms": True}]
			)
		]
	)

	return LaunchDescription([container, components])
