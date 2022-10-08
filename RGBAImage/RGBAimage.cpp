#include "RGBAimage.h"
using namespace cv;

RGBAImage::RGBAImage(String path) {
    image = imread(path, IMREAD_UNCHANGED);

    width = image.cols;
    height = image.rows;
    num_channels = image.channels();
}

int RGBAImage::getWidth() {
    return width;
}

int RGBAImage::getHeight() {
    return height;
}

int RGBAImage::getNumChannels() {
    return num_channels;
}

int RGBAImage::getSize() {
    return getWidth()*getHeight()*getNumChannels();
}

float* RGBAImage::getImage() {
    int size = getSize();
    float* Image = new float[size];

    // scroll by rows
    for(int i=0; i < getHeight(); i++) {
        for (int j = 0; j < getWidth(); j++) {
            Vec4b pixel = image.at<Vec4b>(i, j);
            Image[(i * getWidth() * getNumChannels()) + (j * getNumChannels())] = (float)pixel[2];
            Image[(i * getWidth() * getNumChannels()) + (j * getNumChannels()) + 1] = (float)pixel[1];
            Image[(i * getWidth() * getNumChannels()) + (j * getNumChannels()) + 2] = (float)pixel[0];
            Image[(i * getWidth() * getNumChannels()) + (j * getNumChannels()) + 3] = (float)pixel[3];
        }
    }
    return Image;
}

float* RGBAImage::getPixel(int i, int j){
    Vec4b pixel = image.at<Vec4b>(j, i);
    float* channels_pixel = new float[getNumChannels()];
    channels_pixel[0] = (float)pixel[2];
    channels_pixel[1] = (float)pixel[1];
    channels_pixel[2] = (float)pixel[0];
    channels_pixel[3] = (float)pixel[3];
    return channels_pixel;
}

void RGBAImage::showImage(){
    imshow("RGBA Image", image);
}