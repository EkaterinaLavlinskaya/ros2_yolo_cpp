#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

using namespace std::chrono_literals;

class CameraPublisher : public rclcpp::Node
{
public:
    CameraPublisher() : Node("camera_publisher")
    {
        // Создаем издателя для топика /camera/image_raw
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("camera/image_raw", 10);
        
        // Таймер для захвата и публикации кадров (30 FPS)
        timer_ = this->create_wall_timer(33ms, std::bind(&CameraPublisher::timer_callback, this));
        
        // Открываем веб-камеру (0 - первая камера)
        cap_.open(0);
        if (!cap_.isOpened()) {
            RCLCPP_ERROR(this->get_logger(), "Не удалось открыть камеру!");
        }
    }

private:
    void timer_callback()
    {
        cv::Mat frame;
        cap_ >> frame;
        
        if (frame.empty()) {
            RCLCPP_WARN(this->get_logger(), "Получен пустой кадр");
            return;
        }
        
        // Конвертируем cv::Mat в ROS Image message
        auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
        publisher_->publish(*msg);
        
        RCLCPP_INFO(this->get_logger(), "Кадр опубликован");
    }
    
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CameraPublisher>());
    rclcpp::shutdown();
    return 0;
}
