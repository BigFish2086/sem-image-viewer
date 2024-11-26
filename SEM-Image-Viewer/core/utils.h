#include <opencv2/opencv.hpp>

class Image;

namespace Utils {
    std::string generateString(size_t length);
    cv::Mat diffTwoImages(const cv::Mat &image1, const cv::Mat &image2, const int threshold);
    bool createDirectory(const std::string &path);
    void loadSessionJson(const std::string &filename);
    cv::Mat heatmap(const cv::Mat& image);
};
