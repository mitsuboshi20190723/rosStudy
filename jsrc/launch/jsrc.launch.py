#
# -*- coding: utf-8 -*-

##
 #  2023.12.2
 #  jsrc.launch.py
 #  ver.0.6
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


from xml.dom.minicompat import NodeList
from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer, LoadComposableNodes, Node
from launch_ros.descriptions import ComposableNode


def generate_launch_description():

	container = ComposableNodeContainer(name="_container", namespace="", package="rclcpp_components", executable="component_container_mt")

	eargs = [{"use_intra_process_comms": True}]
	components = LoadComposableNodes(
		target_container=container,
		composable_node_descriptions=[
			ComposableNode(package="joy", plugin="joy::Joy", extra_arguments=eargs),
#			ComposableNode(package="jsrc", plugin="jsrc::ShowJoyStatus", extra_arguments=eargs),
			ComposableNode(package="jsrc", plugin="jsrc::ImageController", extra_arguments=eargs),
			ComposableNode(package="jsrc", plugin="jsrc::Sctl", extra_arguments=eargs),
#			ComposableNode(package="jsrc", plugin="jsrc::PanTiltRightLeft", extra_arguments=eargs),
#			ComposableNode(package="jsrc", plugin="jsrc::PanTilt", extra_arguments=eargs),
		]
	)

	nodes=[
#		Node(package="image_tools", executable="cam2image"),
#		Node(package="image_tools", executable="showimage"),
		Node(package="jsrc", executable="ros_pantilt"),
	]

	return LaunchDescription([container, components, *nodes])
