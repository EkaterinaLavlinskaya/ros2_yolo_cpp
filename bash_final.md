# Сборка всего workspace
cd ~/ros2_ws
colcon build --packages-select my_msgs my_cv_pkg
source install/setup.bash

# Запуск издателя камеры
ros2 run my_cv_pkg camera_publisher

# В другом терминале - подписчик для проверки
ros2 run my_cv_pkg image_subscriber

# Просмотр активных топиков
ros2 topic list
ros2 topic echo /camera/image_raw --once
