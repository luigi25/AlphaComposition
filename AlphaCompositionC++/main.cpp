#include <iostream>
#include "AlphaBlendTests/sequentialAlphaBlend.h"
#include "AlphaBlendTests/parallelAlphaBlend.h"

using namespace cv;
using namespace std;

int main(){
    int numExecutions = 100;
    int n_threads = 20;
//    sequentialTestPlot(pandaImg, imgSize, flatImages);
//    parallelOpenMPTestPlot(pandaImg, n_threads, imgSize, flatImages);
    vector<string> folder_names = {"480", "720", "1080", "2K", "4K"};

    for(const auto& name: folder_names){
        vector<float*> flatImages;
        // Read the images
        RGBAImage pandaImg = RGBAImage("../images/" + name + "/panda.png");
        float* flatPandaImg = pandaImg.createFlatImage();
        RGBAImage batmanImg = RGBAImage("../images/" + name + "/batman.png");
        float* flatBatmanImg = batmanImg.createFlatImage();
        RGBAImage hatImg = RGBAImage("../images/" + name + "/hat.png");
        float* flatHatImg = hatImg.createFlatImage();
        RGBAImage glassesImg = RGBAImage("../images/" + name + "/3DGlasses.png");
        float* flatGlassesImg = glassesImg.createFlatImage();
        RGBAImage canImg = RGBAImage("../images/" + name + "/can.png");
        float* flatCanImg = canImg.createFlatImage();
        flatImages.push_back(flatPandaImg);
        flatImages.push_back(flatBatmanImg);
        flatImages.push_back(flatHatImg);
        flatImages.push_back(flatGlassesImg);
        flatImages.push_back(flatCanImg);
        int imgSize = pandaImg.getSize();
//        cout << "Sequential Test with " << name << "p" << endl;
//        double meanExecTimeSequentialTest = sequentialTest(numExecutions, imgSize, flatImages);
//        cout << "Mean Sequential execution time: " << floor(meanExecTimeSequentialTest * 100.) / 100. << " microseconds\n" << endl;

        cout << "OpenMP Test with " << name << "p" << endl;
        vector<double> meanExecTimeOpenMPTest = parallelOpenMPTest(numExecutions, n_threads, imgSize, flatImages);
        int index = 0;
        for(int n_thread = 2; n_thread <= n_threads; n_thread += 2) {
            cout << "Mean OpenMP execution time with " << n_thread << " thread: " << floor(meanExecTimeOpenMPTest[index] * 100.) / 100. << " microseconds" << endl;
            index++;
        }
    }
    return 0;
}