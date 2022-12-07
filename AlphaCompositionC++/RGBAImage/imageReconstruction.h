#ifndef ALPHACOMPOSITION_IMAGERECONSTRUCTION_H
#define ALPHACOMPOSITION_IMAGERECONSTRUCTION_H

#include "../RGBAImage/RGBAimage.h"

Mat imageReconstruction(float* flatImg, int width, int height, int channels){
    Mat reconstructedImage = Mat(height, width, CV_8UC4);
    for(int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Vec4b pixel = Vec4b((unsigned char)flatImg[(i * width * channels) + (j * channels) + 2], (unsigned char)flatImg[(i * width * channels) + (j * channels) + 1], (unsigned char)flatImg[(i * width * channels) + (j * channels)], (unsigned char)flatImg[(i * width * channels) + (j * channels) + 3]);
            reconstructedImage.at<Vec4b>(i,j) = pixel;
        }
    }
    return reconstructedImage;
}
#endif //ALPHACOMPOSITION_IMAGERECONSTRUCTION_H
