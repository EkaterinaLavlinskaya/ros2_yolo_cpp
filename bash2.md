Создание пользовательского сообщения (Custom Message)
Для передачи координат обнаруженных объектов создадим свой тип сообщения.

Шаг 1: Создайте отдельный пакет для сообщений
bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_cmake my_msgs
cd my_msgs
mkdir msg
