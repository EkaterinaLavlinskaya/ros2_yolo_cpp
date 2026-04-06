cd ~/ros2_ws/src/my_cv_pkg
cat >> CMakeLists.txt << 'EOF'

# fake_detector
add_executable(fake_detector src/fake_detector.cpp)
ament_target_dependencies(fake_detector
  rclcpp
  sensor_msgs
  my_msgs
  cv_bridge
  OpenCV
)

# visualizer
add_executable(visualizer src/visualizer.cpp)
ament_target_dependencies(visualizer
  rclcpp
  sensor_msgs
  my_msgs
  cv_bridge
  OpenCV
)

install(TARGETS
  fake_detector
  visualizer
  DESTINATION lib/${PROJECT_NAME}
)
EOF
