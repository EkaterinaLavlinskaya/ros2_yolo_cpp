#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "my_msgs/msg/detection_array.hpp"
#include "my_msgs/msg/bounding_box.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

class Visualizer : public rclcpp::Node
{
public:
    Visualizer() : Node("visualizer")
    {
        // Подписываемся на изображения
        img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera/image_raw", 10,
            std::bind(&Visualizer::image_callback, this, std::placeholders::_1));
        
        // Подписываемся на детекции
        det_sub_ = this->create_subscription<my_msgs::msg::DetectionArray>(
            "detected_objects", 10,
            std::bind(&Visualizer::detection_callback, this, std::placeholders::_1));
        
        RCLCPP_INFO(this->get_logger(), "🎨 Визуализатор запущен!");
        has_detections_ = false;
    }

private:
    void detection_callback(const my_msgs::msg::DetectionArray::SharedPtr msg)
    {
        detections_ = msg;
        has_detections_ = true;
    }
    
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        
        // Рисуем детекции на изображении
        if (has_detections_) {
            for (const auto& box : detections_->boxes) {
                // Конвертируем центр в верхний левый угол
                int x = box.x - box.width / 2;
                int y = box.y - box.height / 2;
                int w = box.width;
                int h = box.height;
                
                // Рисуем зелёную рамку
                cv::rectangle(cv_ptr->image, cv::Rect(x, y, w, h), cv::Scalar(0, 255, 0), 3);
                
                // Рисуем текст с именем объекта
                std::string label = box.class_name + " (" + std::to_string(box.confidence).substr(0, 4) + ")";
                cv::putText(cv_ptr->image, label, cv::Point(x, y - 10), 
                            cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(0, 255, 0), 2);
                
                // Рисуем центр
                cv::circle(cv_ptr->image, cv::Point(box.x, box.y), 5, cv::Scalar(0, 0, 255), -1);
            }
        }
        
        // Показываем изображение
        cv::imshow("Fake Detector", cv_ptr->image);
        cv::waitKey(1);
    }
    
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
    rclcpp::Subscription<my_msgs::msg::DetectionArray>::SharedPtr det_sub_;
    my_msgs::msg::DetectionArray::SharedPtr detections_;
    bool has_detections_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Visualizer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
