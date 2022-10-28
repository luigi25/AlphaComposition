#ifndef ALPHACOMPOSITION_PARALLELALPHABLEND_H
#define ALPHACOMPOSITION_PARALLELALPHABLEND_H
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "../RGBAImage/RGBAimage.h"
#include "../RGBAImage/imageReconstruction.h"

using namespace cv;
using namespace std;

vector<double> parallelOpenMPTest(int numExecutions, int nThreads, int imgSize, const float* flatImgA, const float* flatImgB){
    vector<double> meanExecutionsTimeVec;
    for(int n_thread = 1; n_thread <= nThreads; n_thread++) {
        double meanExecutionsTime = 0;
        for (int execution = 0; execution < numExecutions; execution++) {
            float* flatMixImages = new float[imgSize];
            auto start = chrono::system_clock::now();
            #pragma omp parallel num_threads(n_thread) default(none) shared(imgSize, flatMixImages, flatImgA, flatImgB)
            {
                #pragma omp for schedule(static) nowait //todo add schedule, nowait
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
                        flatMixImages[i + 3] = (((alphaComponent - 0) * 255) / 1);
                    }
                }
            }
            chrono::duration<double> executionTime{};
            executionTime = chrono::system_clock::now() - start;
            auto executionTimeMilliseconds = chrono::duration_cast<chrono::milliseconds>(executionTime);
            meanExecutionsTime += (double)executionTimeMilliseconds.count();
            free(flatMixImages);
        }
        meanExecutionsTimeVec.push_back(meanExecutionsTime / numExecutions);
    }
    return meanExecutionsTimeVec;
}

/*
vector<double> parallelOpenMPTestProva(RGBAImage imgA, int numExecutions, int nThreads, int imgSize, const float* flatImgA, const float* flatImgB){
    int numExecutions = 100;
    vector<double> meanExecutionsTimeVec;
    for(int n_thread = 1; n_thread <= nThreads; n_thread++) {
        double meanExecutionsTime = 0;
        for (int execution = 0; execution < numExecutions; execution++) {
            float* flatMixImages = new float[imgSize];
            auto start = chrono::system_clock::now();
            #pragma omp parallel num_threads(n_thread) default(none) shared(imgSize, flatMixImages, flatImgA, flatImgB)
            {
            #pragma omp for schedule(static) nowait
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
            }
            chrono::duration<double> executionTime{};
            executionTime = chrono::system_clock::now() - start;
            auto executionTimeMilliseconds = chrono::duration_cast<chrono::milliseconds>(executionTime);
            meanExecutionsTime += (double)executionTimeMilliseconds.count();
            // todo visualize result image (need to pass imgA image to the function)
            if(n_thread == 5){
                Mat reconstructed_image = imageReconstruction(flatMixImages, imgA.getWidth(), imgA.getHeight(), imgA.getNumChannels());
                namedWindow("RGBA Image", WINDOW_NORMAL);
                resizeWindow("RGBA Image", (int)(imgA.getWidth()*0.35), (int)(imgA.getHeight()*0.35));
                imshow("RGBA Image", reconstructed_image);
                waitKey(0);
            }
            free(flatMixImages);
        }
        meanExecutionsTimeVec.push_back(meanExecutionsTime / numExecutions);
    }
    return meanExecutionsTimeVec;
}
*/

#endif //ALPHACOMPOSITION_PARALLELALPHABLEND_H
