cat > ~/ros2_ws/src/scripts/run_demo.sh << 'EOF'
#!/bin/bash

# Source ROS2 environment
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash

echo "Starting camera publisher..."
ros2 run my_cv_pkg camera_publisher &
PUBLISHER_PID=$!

sleep 2

echo "Starting image subscriber..."
ros2 run my_cv_pkg image_subscriber

# Cleanup on exit
trap "kill $PUBLISHER_PID" EXIT
EOF

chmod +x ~/ros2_ws/src/scripts/run_demo.sh
