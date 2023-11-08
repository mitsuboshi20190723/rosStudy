#
# -*- coding: utf-8 -*-

##
 #  2023.11.9
 #  jsrc.launch.py
 #  ver.0.3
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
		executable="component_container_mt"
	)
	components = LoadComposableNodes(
		target_container=container,
		composable_node_descriptions=[
			ComposableNode( # ros2 topic echo /joy
				package="jsrc",
				plugin="jsrc::SJS",
				extra_arguments=[{"use_intra_process_comms": True}]
			),
			ComposableNode(
				package="joy",
				plugin="joy::Joy",
				extra_arguments=[{"use_intra_process_comms": True}]
			)
		]
	)
	image1 = Node(package="image_tools", executable="cam2image")
	image2 = Node(package="image_tools", executable="showimage")


	return LaunchDescription([container, components, image1, image2])
