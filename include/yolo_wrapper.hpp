Создайте класс-обертку для YOLO (include/yolo_wrapper.hpp)
  
#pragma once
#include <opencv2/opencv.hpp>
#include <torch/script.h>
#include <torch/torch.h>

class YOLOWrapper {
public:
    YOLOWrapper(const std::string& model_path);
    std::vector<Detection> detect(const cv::Mat& image);
    
private:
    torch::jit::script::Module module_;
    torch::Device device_;
    cv::Mat preprocess(const cv::Mat& image);
};
