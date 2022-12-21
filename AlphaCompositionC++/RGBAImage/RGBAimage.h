#ifndef ALPHACOMPOSITION_RGBAIMAGE_H
#define ALPHACOMPOSITION_RGBAIMAGE_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

class RGBAImage {
private:
    int width, height, numChannels;
    Mat image;

public:
    explicit RGBAImage(const String& path);
    int getWidth() const;
    int getHeight() const;
    int getNumChannels() const;
    int getSize() const;
    float* createFlatImage();
};
#endif //ALPHACOMPOSITION_RGBAIMAGE_H
