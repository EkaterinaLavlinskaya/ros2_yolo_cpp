cmake_minimum_required(VERSION 3.8)
project(my_cv_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)
find_package(my_msgs REQUIRED)

# camera_publisher
add_executable(camera_publisher src/camera_publisher.cpp)
ament_target_dependencies(camera_publisher
  rclcpp
  sensor_msgs
  std_msgs
  cv_bridge
  OpenCV
)

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
  camera_publisher
  fake_detector
  visualizer
  DESTINATION lib/${PROJECT_NAME}
)

# Установка launch файлов
install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
