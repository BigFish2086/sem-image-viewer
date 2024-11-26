#include "sharpen_filter.h"
#include "../engines/logger.h"

cv::Mat SharpenFilter::applyFilter(const Image &inputImage) const
{

    const cv::Mat &image = inputImage.readImageMat();
    cv::Mat outputImage;
    float laplacianBoostFactor = 1.0;                                                                // Controls the amount of Laplacian Sharpening
    cv::Mat kern = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5 * laplacianBoostFactor, -1, 0, -1, 0); // The filtering mask for Laplacian sharpening
    filter2D(image.clone(), outputImage, image.depth(), kern, cv::Point(-1, -1));                    // Applies the masking operator to the image

    Logger::instance()->logMessage(
        Logger::MessageTypes::info, Logger::MessageID::filter_applied,
        Logger::MessageOption::with_path,
        {"Sharpen Filter"},
        "https://www.opencvhelp.org/tutorials/image-processing/how-to-sharpen-image/");
    return outputImage;
}

ImageStateSource SharpenFilter::getImageSource() const
{
    return ImageStateSource::SharpenFilter;
}
