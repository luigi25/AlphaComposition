#ifndef ALPHACOMPOSITION_SEQUENTIALALPHABLEND_H
#define ALPHACOMPOSITION_SEQUENTIALALPHABLEND_H
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "../RGBAImage/RGBAimage.h"
#include "../RGBAImage/imageReconstruction.h"

using namespace cv;
using namespace std;

double sequentialTest(int numExecutions, int imgSize, const float* flatImgA, const float* flatImgB){
    double meanExecutionsTime = 0;
    for(int execution=0; execution < numExecutions; execution++) {
        float* flatMixImages = new float[imgSize];
        auto start = chrono::system_clock::now();
        for (int i = 0; i < imgSize; i += 4) {
            float alphaA = flatImgA[i + 3] / 255;
            float alphaB = flatImgB[i + 3] / 255;
            float alphaComponent = alphaA + alphaB * (1 - alphaA);
            if(alphaComponent == 0){
                flatMixImages[i] = 0;
                flatMixImages[i + 1] = 0;
                flatMixImages[i + 2] = 0;
                flatMixImages[i + 3] = 0;
            } else{
                flatMixImages[i] =
                        (flatImgA[i] * alphaA + flatImgB[i] * alphaB * (1 - alphaA)) / alphaComponent;
                flatMixImages[i + 1] =
                        (flatImgA[i + 1] * alphaA + flatImgB[i + 1] * alphaB * (1 - alphaA)) / alphaComponent;
                flatMixImages[i + 2] =
                        (flatImgA[i + 2] * alphaA + flatImgB[i + 2] * alphaB * (1 - alphaA)) / alphaComponent;
                float alphaComponentNew = (((alphaComponent - 0) * 255) / 1);
                flatMixImages[i + 3] = alphaComponentNew;
            }
        }
        chrono::duration<double> executionTime{};
        executionTime = chrono::system_clock::now() - start;
        auto executionTimeMilliseconds = chrono::duration_cast<chrono::milliseconds>(executionTime);
        meanExecutionsTime += (double)executionTimeMilliseconds.count();
        free(flatMixImages);
        // todo visualize result image (need to pass imgA image to the function)
//        Mat reconstructed_image = imageReconstruction(flatMixImages, imgA.getWidth(), imgA.getHeight(), imgA.getNumChannels());
//        namedWindow("RGBA Image", WINDOW_NORMAL);
//        resizeWindow("RGBA Image", (int)(imgA.getWidth()*0.35), (int)(imgA.getHeight()*0.35));
//        imshow("RGBA Image", reconstructed_image);
//        waitKey(0);

    }
    return meanExecutionsTime / numExecutions;
}
#endif //ALPHACOMPOSITION_SEQUENTIALALPHABLEND_H
