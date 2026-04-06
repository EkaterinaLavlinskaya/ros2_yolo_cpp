
[![ROS2](https://img.shields.io/badge/ROS2-Jazzy-blue)](https://docs.ros.org/en/jazzy/)
[![C++](https://img.shields.io/badge/C++-17-blue)](https://isocpp.org/)
[![OpenCV](https://img.shields.io/badge/OpenCV-4.x-green)](https://opencv.org/)

## 📋 Описание проекта

Этот проект реализует пайплайн обнаружения объектов на C++ с использованием ROS2 Jazzy и YOLO. 
Система состоит из трёх основных узлов:

- **camera_publisher** — публикует изображения с камеры или из файла в топик `/camera/image_raw`
- **image_subscriber** — подписывается на изображения и отображает их (для отладки)
- **yolo_detector** — (в разработке) детектирует объекты с помощью YOLO

## 🏗️ Архитектура
┌─────────────────┐ ┌─────────────────┐ ┌─────────────────┐
│ camera_publisher │────▶│ /camera/image_raw │────▶│ image_subscriber │
└─────────────────┘ └─────────────────┘ └─────────────────┘
│ │
▼ ▼
(WebCam/File) (OpenCV Window)



## 📦 Требования

- Ubuntu 24.04 (Noble) или новее
- ROS2 Jazzy
- OpenCV 4.x
- cv_bridge

## 🔧 Установка

### 1. Клонируйте репозиторий
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
git clone https://github.com/YOUR_USERNAME/ros2_yolo_cpp.git

2. Установите зависимости
sudo apt update
sudo apt install ros-jazzy-cv-bridge libopencv-dev

3. Соберите workspace
cd ~/ros2_ws
colcon build --packages-select my_msgs my_cv_pkg
source install/setup.bash

🚀 Запуск
Запуск издателя камеры
ros2 run my_cv_pkg camera_publisher

Запуск подписчика (отображение изображений)
ros2 run my_cv_pkg image_subscriber

Просмотр топиков
ros2 topic list
ros2 topic echo /camera/image_raw --once



# ROS2 YOLO Object Detection Pipeline

[![ROS2](https://img.shields.io/badge/ROS2-Jazzy-blue)](https://docs.ros.org/en/jazzy/)
[![C++](https://img.shields.io/badge/C++-17-blue)](https://isocpp.org/)

🚀 Быстрый запуск

# Запуск всех узлов одной командой
ros2 launch my_cv_pkg demo.launch.py

🎥 Демонстрация
test_video.avi

📁 Архитектура системы



camera_publisher → /camera/image_raw → fake_detector → /detected_objects → visualizer
                                          ↓
                                    (публикует фейковый
                                     bounding box в центре)
🎯 Что показывает визуализатор
- Зелёная рамка в центре кадра

- Текст с именем объекта и уверенностью

- Красная точка в центре объекта


📁 Структура пакетов

ros2_yolo_cpp/
│
├── README.md                          # Описание проекта
├── .gitignore                         # Игнорируемые файлы
│
├── my_msgs/                           # Пакет с кастомными сообщениями
│   ├── msg/
│   │   ├── BoundingBox.msg
│   │   └── DetectionArray.msg
│   ├── CMakeLists.txt
│   └── package.xml
│
└── my_cv_pkg/                         # Основной пакет
    ├── launch/
    │   └── demo.launch.py             # Launch-файл для запуска всех нод
    ├── src/
    │   ├── camera_publisher.cpp       # Публикация кадров (видео/камера)
    │   ├── fake_detector.cpp          # Фейковый детектор
    │   └── visualizer.cpp             # Визуализация с рамкой
    ├── CMakeLists.txt
    └── package.xml
📝 Лицензия
Apache 2.0

👤 Автор
Ekaterina Lavlinskaya

🚧 Планы
- Интеграция YOLO с LibTorch

- Добавление ноды controller_node

- Launch-файл для автоматического запуска

- Поддержка видеофайлов
- EOF

