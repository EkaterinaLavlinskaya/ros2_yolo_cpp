#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class CameraPublisher : public rclcpp::Node
{
public:
    CameraPublisher() : Node("camera_publisher")
    {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("camera/image_raw", 10);
        timer_ = this->create_wall_timer(33ms, std::bind(&CameraPublisher::timer_callback, this));
        
        // Загружаем изображение один раз
        frame_ = cv::imread("/tmp/test_image.jpg");
        if (frame_.empty()) {
            RCLCPP_ERROR(this->get_logger(), "Не удалось загрузить изображение /tmp/test_image.jpg");
            // Создаём пустое изображение, чтобы программа не падала
            frame_ = cv::Mat::zeros(480, 640, CV_8UC3);
        } else {
            RCLCPP_INFO(this->get_logger(), "Изображение успешно загружено");
        }
    }

private:
    void timer_callback()
    {
        // Публикуем то же самое изображение каждый раз
        auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame_).toImageMsg();
        publisher_->publish(*msg);
        RCLCPP_INFO(this->get_logger(), "Кадр опубликован");
    }
    
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::Mat frame_;  // Храним изображение в памяти
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraPublisher>());
    rclcpp::shutdown();
    return 0;
}
