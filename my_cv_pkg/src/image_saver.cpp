#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"
#include <chrono>

class ImageSaver : public rclcpp::Node
{
public:
    ImageSaver() : Node("image_saver")
    {
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera/image_raw", 10,
            std::bind(&ImageSaver::image_callback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Сохранение кадров в /tmp/");
    }

private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        static int count = 0;
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        
        std::string filename = "/tmp/frame_" + std::to_string(count++) + ".jpg";
        cv::imwrite(filename, cv_ptr->image);
        RCLCPP_INFO(this->get_logger(), "Сохранён: %s", filename.c_str());
        
        if (count >= 10) {
            RCLCPP_INFO(this->get_logger(), "Сохранено 10 кадров. Завершение...");
            rclcpp::shutdown();
        }
    }
    
    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ImageSaver>());
    rclcpp::shutdown();
    return 0;
}
