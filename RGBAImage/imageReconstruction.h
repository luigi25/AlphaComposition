#ifndef ALPHACOMPOSITION_IMAGERECONSTRUCTION_H
#define ALPHACOMPOSITION_IMAGERECONSTRUCTION_H
#include "../RGBAImage/RGBAimage.h"

Mat imageReconstruction(float* flatten_img, int width, int height, int channels){
    Mat reconstructed_image = Mat(height, width, CV_8UC4);
    for(int i=0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Vec4b pixel = Vec4b((unsigned char)flatten_img[(i * width * channels) + (j * channels) + 2], (unsigned char)flatten_img[(i * width * channels) + (j * channels) + 1], (unsigned char)flatten_img[(i * width * channels) + (j * channels)], (unsigned char)flatten_img[(i * width * channels) + (j * channels) + 3]);
            reconstructed_image.at<Vec4b>(i,j) = pixel;
        }
    }
    return reconstructed_image;
}
#endif //ALPHACOMPOSITION_IMAGERECONSTRUCTION_H
