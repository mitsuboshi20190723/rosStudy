#
# -*- coding: utf-8 -*-

##
 #  2023.11.5
 #  collatz.launch.py
 #  ver.1.0
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer, LoadComposableNodes, Node
from launch_ros.descriptions import ComposableNode


def generate_launch_description():
	container = ComposableNodeContainer(
		name="_container",
		namespace="",
		package="rclcpp_components",
		executable="component_container"
	)
	components = LoadComposableNodes(
		target_container=container,
		composable_node_descriptions=[
			ComposableNode(
				package="collatz",
				plugin="collatz::Calculate",
				extra_arguments=[{"use_intra_process_comms": True}]
			),
			ComposableNode(
				package="collatz",
				plugin="collatz::Map",
				extra_arguments=[{"use_intra_process_comms": True}]
			)
		]
	)
	node_kiku = Node(package="collatz", executable="test_kiku")
	node_iu = Node(package="collatz", executable="test_iu")


	return LaunchDescription([container, components, node_kiku, node_iu])
