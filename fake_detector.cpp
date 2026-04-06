cd ~/ros2_ws/src/my_cv_pkg/src
cat > fake_detector.cpp << 'EOF'
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "my_msgs/msg/bounding_box.hpp"
#include "my_msgs/msg/detection_array.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

class FakeDetector : public rclcpp::Node
{
public:
    FakeDetector() : Node("fake_detector")
    {
        // Подписываемся на изображения
        sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera/image_raw", 10,
            std::bind(&FakeDetector::detect_callback, this, std::placeholders::_1));
        
        // Публикуем детекции
        pub_ = this->create_publisher<my_msgs::msg::DetectionArray>("detected_objects", 10);
        
        RCLCPP_INFO(this->get_logger(), "🎭 Фейковый детектор запущен!");
    }

private:
    void detect_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        // Конвертируем изображение для получения размеров
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        
        int height = cv_ptr->image.rows;
        int width = cv_ptr->image.cols;
        
        // Создаём фейковый bounding box в центре кадра
        my_msgs::msg::BoundingBox box;
        box.x = width / 2.0;           // центр X
        box.y = height / 2.0;          // центр Y
        box.width = width * 0.3;        // 30% от ширины
        box.height = height * 0.3;      // 30% от высоты
        box.confidence = 0.95;          // 95% уверенности
        box.class_name = "fake_object"; // Имя объекта
        
        // Публикуем массив с одним объектом
        my_msgs::msg::DetectionArray detections;
        detections.boxes.push_back(box);
        pub_->publish(detections);
        
        RCLCPP_INFO(this->get_logger(), "🎯 Опубликован фейковый объект в центре кадра");
    }
    
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr sub_;
    rclcpp::Publisher<my_msgs::msg::DetectionArray>::SharedPtr pub_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<FakeDetector>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
EOF
