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

double sequentialTest(int numExecutions, int imgSize, vector<float*> flatImages){
    double meanExecutionsTime = 0;
    for(int execution=0; execution < numExecutions; execution++) {
        float* flatMixImages = new float[imgSize];
        for(int i = 0; i < imgSize; i++)
            flatMixImages[i] = flatImages[0][i];
        auto start = chrono::system_clock::now();
        for (int i = 0; i < imgSize; i += 4) {
            for (int j = 1; j < flatImages.size(); j++) {
                float alphaA = flatImages[j][i + 3] / 255;
                float alphaB = flatMixImages[i + 3] / 255;
                float alphaComponent = alphaA + alphaB * (1 - alphaA);
                if(alphaComponent == 0){
                    flatMixImages[i] = 0;
                    flatMixImages[i + 1] = 0;
                    flatMixImages[i + 2] = 0;
                    flatMixImages[i + 3] = 0;
                } else{
                    flatMixImages[i] =
                            (flatImages[j][i] * alphaA + flatMixImages[i] * alphaB * (1 - alphaA)) / alphaComponent ;
                    flatMixImages[i + 1] =
                            (flatImages[j][i + 1] * alphaA + flatMixImages[i + 1] * alphaB * (1 - alphaA)) / alphaComponent;
                    flatMixImages[i + 2] =
                            (flatImages[j][i + 2] * alphaA + flatMixImages[i + 2] * alphaB * (1 - alphaA)) / alphaComponent;
                    float alphaComponentNew = (((alphaComponent - 0) * 255) / 1);
                    flatMixImages[i + 3] = alphaComponentNew;
                }
            }
        }
        chrono::duration<double> executionTime{};
        executionTime = chrono::system_clock::now() - start;
        auto executionTimeMilliseconds = chrono::duration_cast<chrono::milliseconds>(executionTime);
        meanExecutionsTime += (double)executionTimeMilliseconds.count();
        free(flatMixImages);
    }
    return meanExecutionsTime / numExecutions;
}


void sequentialTestPlot(const RGBAImage& pandaImg, int imgSize, vector<float*> flatImages){
    float* flatMixImages = new float[imgSize];
    for(int i = 0; i < imgSize; i++)
        flatMixImages[i] = flatImages[0][i];
    for (int i = 0; i < imgSize; i += 4) {
        for (int j = 1; j < flatImages.size(); j++) {
            float alphaA = flatImages[j][i + 3] / 255;
            float alphaB = flatMixImages[i + 3] / 255;
            float alphaComponent = alphaA + alphaB * (1 - alphaA);
            if(alphaComponent == 0){
                flatMixImages[i] = 0;
                flatMixImages[i + 1] = 0;
                flatMixImages[i + 2] = 0;
                flatMixImages[i + 3] = 0;
            } else{
                flatMixImages[i] =
                        (flatImages[j][i] * alphaA + flatMixImages[i] * alphaB * (1 - alphaA)) / alphaComponent;
                flatMixImages[i + 1] =
                        (flatImages[j][i + 1] * alphaA + flatMixImages[i + 1] * alphaB * (1 - alphaA)) / alphaComponent;
                flatMixImages[i + 2] =
                        (flatImages[j][i + 2] * alphaA + flatMixImages[i + 2] * alphaB * (1 - alphaA)) / alphaComponent;
                float alphaComponentNew = (((alphaComponent - 0) * 255) / 1);
                flatMixImages[i + 3] = alphaComponentNew;
            }
        }
    }
    Mat reconstructed_image = imageReconstruction(flatMixImages, pandaImg.getWidth(), pandaImg.getHeight(), pandaImg.getNumChannels());
//    namedWindow("RGBA Image", WINDOW_NORMAL);
//    resizeWindow("RGBA Image", (int)(pandaImg.getWidth()*0.35), (int)(pandaImg.getHeight()*0.35));
//    imshow("RGBA Image", reconstructed_image);
//    waitKey(0);
    imwrite("../results/sequential.png", reconstructed_image);
    free(flatMixImages);
}
#endif //ALPHACOMPOSITION_SEQUENTIALALPHABLEND_H
