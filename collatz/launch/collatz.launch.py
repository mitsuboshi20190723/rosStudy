#
# -*- coding: utf-8 -*-

##
 #  2023.11.3
 #  collatz.launch.py
 #  ver.1.0
 #  Kunihito Mitsuboshi
 #  license(Apache-2.0) at http://www.apache.org/licenses/LICENSE-2.0
 ##


from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
	node_kiku = Node(
		package = 'collatz',
		executable = 'test_kiku'
	)
	node_iu = Node(
		package = 'collatz',
		executable = 'test_iu'
	)

	return LaunchDescription([
		node_kiku,
		node_iu
	])
