

echo "Installing dependencies for ROS2 YOLO project..."

# Update system
sudo apt update

# Install ROS2 Jazzy if not installed
if [ ! -d "/opt/ros/jazzy" ]; then
    echo "Installing ROS2 Jazzy..."
    sudo apt install ros-jazzy-ros-base -y
fi

# Install OpenCV and cv_bridge
sudo apt install -y libopencv-dev ros-jazzy-cv-bridge

# Install image_transport
sudo apt install -y ros-jazzy-image-transport-plugins

echo "Dependencies installed successfully!"
EOF

chmod +x ~/ros2_ws/src/scripts/install_deps.sh
