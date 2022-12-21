#include "RGBAimage.h"
using namespace cv;

RGBAImage::RGBAImage(const String& path) {
    image = imread(path, IMREAD_UNCHANGED);

    width = image.cols;
    height = image.rows;
    numChannels = image.channels();
}

int RGBAImage::getWidth() const {
    return width;
}

int RGBAImage::getHeight() const {
    return height;
}

int RGBAImage::getNumChannels() const {
    return numChannels;
}

int RGBAImage::getSize() const {
    return width * height * numChannels;
}

float* RGBAImage::createFlatImage() {
    int size = getSize();
    float* flatImage = new float[size];

    // scroll by rows
    for(int i=0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Vec4b pixel = image.at<Vec4b>(i, j);
            flatImage[(i * width * numChannels) + (j * numChannels)] = (float)pixel[2];
            flatImage[(i * width * numChannels) + (j * numChannels) + 1] = (float)pixel[1];
            flatImage[(i * width * numChannels) + (j * numChannels) + 2] = (float)pixel[0];
            flatImage[(i * width * numChannels) + (j * numChannels) + 3] = (float)pixel[3];
        }
    }
    return flatImage;
}