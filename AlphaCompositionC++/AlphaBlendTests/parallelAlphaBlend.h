#ifndef ALPHACOMPOSITION_PARALLELALPHABLEND_H
#define ALPHACOMPOSITION_PARALLELALPHABLEND_H
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <omp.h>

#include "../RGBAImage/RGBAimage.h"
#include "../RGBAImage/imageReconstruction.h"

using namespace cv;
using namespace std;

vector<double> parallelOpenMPTest(int numExecutions, int nThreads, int imgSize, vector<float*> flatImages){
    vector<double> meanExecutionsTimeVec;
    for(int n_thread = 2; n_thread <= nThreads; n_thread+=2) {
        cout << "Thread number: " << n_thread << endl;
        double meanExecutionsTime = 0;
        for (int execution = 0; execution < numExecutions; execution++) {
            float* flatMixImages = new float[imgSize];
            auto start = chrono::system_clock::now();
            #pragma omp parallel num_threads(n_thread) default(none) shared(imgSize, flatMixImages, flatImages)
            {
                #pragma omp for schedule(static) nowait
                for (int i = 0; i < imgSize; i += 4) {
                    float r = 0;
                    float g = 0;
                    float b = 0;
                    float a = 0;

                    for (int j = 0; j < flatImages.size(); j++) {
                        float alphaA = flatImages[j][i + 3] / 255;
                        float alphaB = a / 255;
                        float alphaComponent = alphaA + alphaB * (1 - alphaA);
                        if(alphaComponent == 0){
                            r = 0;
                            g = 0;
                            b = 0;
                            a = 0;
                        } else{
                            r = (flatImages[j][i] * alphaA + r * alphaB * (1 - alphaA)) / alphaComponent;
                            g = (flatImages[j][i + 1] * alphaA + g * alphaB * (1 - alphaA)) / alphaComponent;
                            b = (flatImages[j][i + 2] * alphaA + b * alphaB * (1 - alphaA)) / alphaComponent;
                            a = (((alphaComponent - 0) * 255) / 1);
                        }

                    }
                    flatMixImages[i] = r;
                    flatMixImages[i + 1] = g;
                    flatMixImages[i + 2] = b;
                    flatMixImages[i + 3] = a;
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


void parallelOpenMPTestPlot(RGBAImage pandaImg, int nThreads, int imgSize, vector<float*> flatImages){
    for(int n_thread = 2; n_thread <= nThreads; n_thread+=2) {
        cout << "Thread number: " << n_thread << endl;
        float* flatMixImages = new float[imgSize];
//        for(int i = 0; i < imgSize; i++)
//            flatMixImages[i] = flatImages[0][i];
        #pragma omp parallel num_threads(n_thread) default(none) shared(imgSize, flatMixImages, flatImages)
        {
            #pragma omp for schedule(static) nowait
            for (int i = 0; i < imgSize; i += 4) {
                float r = 0;
                float g = 0;
                float b = 0;
                float a = 0;

                for (int j = 0; j < flatImages.size(); j++) {
                    float alphaA = flatImages[j][i + 3] / 255;
                    float alphaB = a / 255;
                    float alphaComponent = alphaA + alphaB * (1 - alphaA);
                    if(alphaComponent == 0){
                        r = 0;
                        g = 0;
                        b = 0;
                        a = 0;
                    } else{
                        r = (flatImages[j][i] * alphaA + r * alphaB * (1 - alphaA)) / alphaComponent;
                        g = (flatImages[j][i + 1] * alphaA + g * alphaB * (1 - alphaA)) / alphaComponent;
                        b = (flatImages[j][i + 2] * alphaA + b * alphaB * (1 - alphaA)) / alphaComponent;
                        a = (((alphaComponent - 0) * 255) / 1);
                    }

                }
                flatMixImages[i] = r;
                flatMixImages[i + 1] = g;
                flatMixImages[i + 2] = b;
                flatMixImages[i + 3] = a;
            }
        }
        Mat reconstructed_image = imageReconstruction(flatMixImages, pandaImg.getWidth(), pandaImg.getHeight(), pandaImg.getNumChannels());
//        namedWindow("RGBA Image", WINDOW_NORMAL);
//        resizeWindow("RGBA Image", (int)(pandaImg.getWidth()*0.35), (int)(pandaImg.getHeight()*0.35));
//        imshow("RGBA Image", reconstructed_image);
//        waitKey(0);
        imwrite("../results/sequential_" + to_string(n_thread) + ".png", reconstructed_image);
        free(flatMixImages);
    }
}


#endif //ALPHACOMPOSITION_PARALLELALPHABLEND_H
