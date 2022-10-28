#include <iostream>
#include "AlphaBlendTests/sequentialAlphaBlend.h"
#include "AlphaBlendTests/parallelAlphaBlend.h"

using namespace cv;
using namespace std;

int main(){
    // Read the images
    RGBAImage imgA = RGBAImage("../images/RayBan.png");
    float* flatImgA = imgA.createFlatImage();

    RGBAImage imgB = RGBAImage("../images/Oro_Base.png");
    float* flatImgB = imgB.createFlatImage();
    int imgSize = imgA.getSize();
    int numExecutions = 100;
    cout << "Sequential Test" << endl;
    double meanExecTimeSequentialTest = sequentialTest(numExecutions, imgSize, flatImgA, flatImgB);
    cout << "Mean Sequential execution time: " << floor(meanExecTimeSequentialTest * 100.) / 100. << " milliseconds\n" << endl;

    cout << "OpenMP Test" << endl;
    int n_threads = 10;
    vector<double> meanExecTimeOpenMPTest = parallelOpenMPTest(numExecutions, n_threads, imgSize, flatImgA, flatImgB);
//    vector<double> meanExecTimeOpenMPTest = parallelOpenMPTestProva(imgA, n_threads, imgSize, flatImgA, flatImgB);
    for(int n_thread = 1; n_thread <= n_threads; n_thread++) {
        cout << "Mean OpenMP execution time with " << n_thread << " thread: " << floor(meanExecTimeOpenMPTest[n_thread - 1] * 100.) / 100. << " milliseconds" << endl;
    }

    return 0;
}