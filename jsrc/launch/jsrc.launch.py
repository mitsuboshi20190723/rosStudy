#
# -*- coding: utf-8 -*-

##
 #  2023.11.30
 #  jsrc.launch.py
 #  ver.0.5
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
		executable="component_container_mt"
	)

	components = LoadComposableNodes(
		target_container=container,
		composable_node_descriptions=[
			ComposableNode( # ros2 topic echo /joy
				package="jsrc",
				plugin="jsrc::ShowJoyStatus",
#				name="joymsgs",
				extra_arguments=[{"use_intra_process_comms": True}]
			),
			ComposableNode(
				package="jsrc",
				plugin="jsrc::ImageController",
#				name="joymsgs",
				extra_arguments=[{"use_intra_process_comms": True}]
			),
			ComposableNode(
				package="joy",
				plugin="joy::Joy",
#				name="joymsgs",
				extra_arguments=[{"use_intra_process_comms": True}]
			),
			ComposableNode(
				package="jsrc",
				plugin="jsrc::PanTiltRightLeft",
#				name="joymsgs",
				extra_arguments=[{"use_intra_process_comms": True}]
			)#,
#			ComposableNode(
#				package="jsrc",
#				plugin="jsrc::PanTilt",
#				name="joymsgs",
#				extra_arguments=[{"use_intra_process_comms": True}]
#			)
		]
	)

	nodes=[
#		Node(package="image_tools", executable="cam2image"),
#		Node(package="image_tools", executable="showimage")#,
		Node(package="jsrc", executable="ros_pantilt")
	]

	return LaunchDescription([container, components, *nodes])
