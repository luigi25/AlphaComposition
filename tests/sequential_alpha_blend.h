#ifndef ALPHACOMPOSITION_SEQUENTIAL_ALPHA_BLEND_H
#define ALPHACOMPOSITION_SEQUENTIAL_ALPHA_BLEND_H

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "../RGBAImage/RGBAimage.h"

using namespace cv;
using namespace std;

double sequentialTest(int img_size, float* flatten_comb_img, float* flatten_imgA, float* flatten_imgB){
    int num_executions = 100;
    double mean_executions_time = 0;
    for(int execution=0; execution<num_executions; execution++) {
        auto start = chrono::system_clock::now();
        for (int i = 0; i < img_size; i += 4) {
            float alphaA = flatten_imgA[i + 3] / 255;
            float alphaB = flatten_imgB[i + 3] / 255;
            float alpha_component = alphaA + alphaB * (1 - alphaA);
            flatten_comb_img[i] =
                    (flatten_imgA[i] * alphaA + flatten_imgB[i] * alphaB * (1 - alphaA)) / alpha_component;
            flatten_comb_img[i + 1] =
                    (flatten_imgA[i + 1] * alphaA + flatten_imgB[i + 1] * alphaB * (1 - alphaA)) / alpha_component;
            flatten_comb_img[i + 2] =
                    (flatten_imgA[i + 2] * alphaA + flatten_imgB[i + 2] * alphaB * (1 - alphaA)) / alpha_component;
        }

        chrono::duration<double> exec_time{};
        exec_time = chrono::system_clock::now() - start;
        auto exec_time_milliseconds = chrono::duration_cast<chrono::milliseconds>(exec_time);
        mean_executions_time += (double)exec_time_milliseconds.count();

        // todo visualize result image (need to pass imgA image to the function)
//        Mat reconstructed_image = imageReconstruction(flatten_comb_img, imgA.getWidth(), imgA.getHeight(), imgA.getNumChannels());
//        namedWindow("RGBA Image", WINDOW_NORMAL);
//        resizeWindow("RGBA Image", (int)(imgA.getWidth()*0.35), (int)(imgA.getHeight()*0.35));
//        imshow("RGBA Image", reconstructed_image);
//        waitKey(0);

    }
    return mean_executions_time/num_executions;
}

#endif //ALPHACOMPOSITION_SEQUENTIAL_ALPHA_BLEND_H
