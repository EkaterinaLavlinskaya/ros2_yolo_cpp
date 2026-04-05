cmake_minimum_required(VERSION 3.8)
project(my_cv_pkg)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(camera_publisher src/camera_publisher.cpp)
ament_target_dependencies(camera_publisher
  rclcpp
  std_msgs
  sensor_msgs
  cv_bridge
  OpenCV
)

install(TARGETS camera_publisher
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()

# image_subscriber executable
add_executable(image_subscriber src/image_subscriber.cpp)
ament_target_dependencies(image_subscriber
  rclcpp
  sensor_msgs
  cv_bridge
  OpenCV
)

install(TARGETS image_subscriber
  DESTINATION lib/${PROJECT_NAME}
)
