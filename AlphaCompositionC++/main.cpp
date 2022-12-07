#include <iostream>
#include "AlphaBlendTests/sequentialAlphaBlend.h"
#include "AlphaBlendTests/parallelAlphaBlend.h"

using namespace cv;
using namespace std;

int main(){
    vector<float*> flatImages;
    // Read the images
    RGBAImage pandaImg = RGBAImage("../images/panda.png");
    float* flatPandaImg = pandaImg.createFlatImage();
    RGBAImage batmanImg = RGBAImage("../images/batman.png");
    float* flatBatmanImg = batmanImg.createFlatImage();
    RGBAImage hatImg = RGBAImage("../images/hat.png");
    float* flatHatImg = hatImg.createFlatImage();
    RGBAImage glassesImg = RGBAImage("../images/3DGlasses.png");
    float* flatGlassesImg = glassesImg.createFlatImage();
    RGBAImage canImg = RGBAImage("../images/can.png");
    float* flatCanImg = canImg.createFlatImage();
    flatImages.push_back(flatPandaImg);
    flatImages.push_back(flatBatmanImg);
    flatImages.push_back(flatHatImg);
    flatImages.push_back(flatGlassesImg);
    flatImages.push_back(flatCanImg);
    bool test_phase = false;

    int imgSize = pandaImg.getSize();
    int numExecutions = 10;
    int n_threads = 16;
    cout << "Sequential Test" << endl;
    if (test_phase){
        sequentialTestPlot(pandaImg, imgSize, flatImages);
    } else {
        double meanExecTimeSequentialTest = sequentialTest(numExecutions, imgSize, flatImages);
        cout << "Mean Sequential execution time: " << floor(meanExecTimeSequentialTest * 100.) / 100. << " milliseconds\n" << endl;
    }

    cout << "OpenMP Test" << endl;
    if (test_phase){
        parallelOpenMPTestPlot(pandaImg, n_threads, imgSize, flatImages);
    } else {
        vector<double> meanExecTimeOpenMPTest = parallelOpenMPTest(numExecutions, n_threads, imgSize, flatImages);
        for(int n_thread = 2; n_thread <= n_threads; n_thread+=2) {
            cout << "Mean OpenMP execution time with " << n_thread << " thread: " << floor(meanExecTimeOpenMPTest[n_thread/2 - 1] * 100.) / 100. << " milliseconds" << endl;
        }
    }
    return 0;
}