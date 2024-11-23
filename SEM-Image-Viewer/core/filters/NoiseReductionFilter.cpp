#include "NoiseReductionFilter.h"

NoiseReductionFilter::NoiseReductionFilter(double intensity) {
    if (intensity < 0)
        _intensity = 0;
    else if (intensity > 100)
        _intensity = 100;
    else
        _intensity = intensity;
}

cv::Mat NoiseReductionFilter::applyFilter(const Image& inputImage) const {
    cv::Mat res;

    if (inputImage.getMetadata().getColorSpace() == ColorSpace::Gray)
    {
        cv::fastNlMeansDenoising(cv::InputArray(inputImage.getImageMat()), cv::OutputArray(res), _intensity);
    }
    else
    {
        cv::fastNlMeansDenoisingColored(cv::InputArray(inputImage.getImageMat()), cv::OutputArray(res), _intensity, _intensity);
    }
    //Logger::instance()->logMessage("F201",{"Noise Reduction "});
    return res;
}

ImageStateSource NoiseReductionFilter::getImageSource() const {
    return ImageStateSource::NoiseReductionFilter;
}

double NoiseReductionFilter::getIntensity(void) const {
    return _intensity;
}
