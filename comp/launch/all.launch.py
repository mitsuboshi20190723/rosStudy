#
# -*- coding: utf-8 -*-

##
 #  2023.11.27
 #  all.launch.py
 #  ver.1.0
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


from xml.dom.minicompat import NodeList
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
			ComposableNode(package="comp", plugin="comp::KIKU", extra_arguments=[{"use_intra_process_comms": True}]),
			ComposableNode(package="comp", plugin="comp::IU", extra_arguments=[{"use_intra_process_comms": True}])
		]
	)

	nodes=[
		Node(package="comp", executable="kiku.sa"),
		Node(package="comp", executable="iu.sa")
	]

	return LaunchDescription([container, components, *nodes])
