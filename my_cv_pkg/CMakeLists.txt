# Добавьте после find_package(OpenCV REQUIRED)
find_package(Torch REQUIRED PATHS /usr/local/libtorch)

# Добавьте Torch в target_link_libraries
target_link_libraries(yolo_detector ${OpenCV_LIBS} ${TORCH_LIBRARIES})
