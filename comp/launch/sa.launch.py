#
# -*- coding: utf-8 -*-

##
 #  2023.11.4
 #  sa.launch.py
 #  ver.1.2
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


# ros2 run comp kiku.sa
# ros2 run comp iu.sa 


from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
	node_kiku = Node(package="comp", executable="kiku.sa")
	node_iu = Node(package="comp", executable="iu.sa")

	return LaunchDescription([node_kiku, node_iu])
