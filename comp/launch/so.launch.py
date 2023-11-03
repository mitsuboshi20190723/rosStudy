#
# -*- coding: utf-8 -*-

##
 #  2023.11.3
 #  so.launch.py
 #  ver.1.0
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


# ros2 run rclcpp_components component_container
# ros2 component load /ComponentManager comp comp::KIKU -e use_intra_process_comms:=true
# ros2 component load /ComponentManager comp comp::IU -e use_intra_process_comms:=true

from launch import LaunchDescription
from launch_ros.actions import LoadComposableNodes
from launch_ros.descriptions import ComposableNode

def generate_launch_description():
	components = LoadComposableNodes(
		target_container="comp_container",
		composable_node_descriptions=[
			ComposableNode(
				package="comp",
				plugin="comp::KIKU",
				name="kiku.so",
				extra_arguments=[
					{"use_intra_process_comms": True}
				]
			),
			ComposableNode(
				package="comp",
				plugin="comp::IU",
				name="iu.so",
				extra_arguments=[
					{"use_intra_process_comms": True}
				]
			)
		]
	)

	return LaunchDescription([components])
