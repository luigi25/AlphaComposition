#include "RGBAimage.h"
using namespace cv;

RGBAImage::RGBAImage(const String& path) {
    image = imread(path, IMREAD_UNCHANGED);

    width = image.cols;
    height = image.rows;
    num_channels = image.channels();
}

int RGBAImage::getWidth() const {
    return width;
}

int RGBAImage::getHeight() const {
    return height;
}

int RGBAImage::getNumChannels() const {
    return num_channels;
}

int RGBAImage::getSize() const {
    return getWidth()*getHeight()*getNumChannels();
}

float* RGBAImage::createFlatImage() {
    int size = getSize();
    float* flatImage = new float[size];

    // scroll by rows
    for(int i=0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            Vec4b pixel = image.at<Vec4b>(i, j);
            flatImage[(i * getWidth() * getNumChannels()) + (j * getNumChannels())] = (float)pixel[2];
            flatImage[(i * getWidth() * getNumChannels()) + (j * getNumChannels()) + 1] = (float)pixel[1];
            flatImage[(i * getWidth() * getNumChannels()) + (j * getNumChannels()) + 2] = (float)pixel[0];
            flatImage[(i * getWidth() * getNumChannels()) + (j * getNumChannels()) + 3] = (float)pixel[3];
        }
    }
    return flatImage;
}

float* RGBAImage::getPixel(int i, int j){
    Vec4b pixel = image.at<Vec4b>(j, i);
    float* pixelChannels = new float[getNumChannels()];
    pixelChannels[0] = (float)pixel[2];
    pixelChannels[1] = (float)pixel[1];
    pixelChannels[2] = (float)pixel[0];
    pixelChannels[3] = (float)pixel[3];
    return pixelChannels;
}

void RGBAImage::showImage(){
    imshow("RGBA Image", image);
}