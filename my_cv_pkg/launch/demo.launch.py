from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='my_cv_pkg',
            executable='camera_publisher',
            name='camera_publisher',
            output='screen'
        ),
        Node(
            package='my_cv_pkg',
            executable='fake_detector',
            name='fake_detector',
            output='screen'
        ),
        Node(
            package='my_cv_pkg',
            executable='visualizer',
            name='visualizer',
            output='screen'
        ),
    ])
