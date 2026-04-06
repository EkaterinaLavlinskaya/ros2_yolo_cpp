#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "cv_bridge/cv_bridge.h"
#include "opencv2/opencv.hpp"

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    auto node = rclcpp::Node::make_shared("camera_publisher");
    auto pub = node->create_publisher<sensor_msgs::msg::Image>("camera/image_raw", 10);
    
    cv::VideoCapture cap("/tmp/test_video.avi");
    if (!cap.isOpened()) {
        RCLCPP_ERROR(node->get_logger(), "Video failed!");
        return -1;
    }
    RCLCPP_INFO(node->get_logger(), "✅ Video opened! Publishing frames...");
    
    rclcpp::Rate rate(30);
    while (rclcpp::ok()) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) {
            cap.set(cv::CAP_PROP_POS_FRAMES, 0);
            continue;
        }
        auto msg = cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", frame).toImageMsg();
        pub->publish(*msg);
        rate.sleep();
    }
    
    rclcpp::shutdown();
    return 0;
}
