#include <iostream>
#include "tests/sequential_alpha_blend.h"
#include "tests/parallel_alpha_blend.h"

#include "RGBAImage/RGBAimage.h"

using namespace cv;
using namespace std;

int main(){
    // Read the images
    RGBAImage imgA = RGBAImage("../images/RayBan.png");
    float* flatten_imgA = imgA.getImage();

    RGBAImage imgB = RGBAImage("../images/Oro_Base.png");
    float* flatten_imgB = imgB.getImage();
    int img_size = imgA.getSize();
    float* flatten_comb_img = new float[img_size];

    cout << "Sequential Test" << endl;
    double mean_sequential_test = sequentialTest(img_size, flatten_comb_img, flatten_imgA, flatten_imgB);
    cout << "Mean Sequential execution time: " << floor(mean_sequential_test * 100.) / 100. << " milliseconds\n" << endl;

    cout << "OpenMP Test" << endl;
    int n_threads = 10;
    vector<double> mean_openmp_test = parallelOpenMPTest(n_threads, img_size, flatten_comb_img, flatten_imgA, flatten_imgB);
    for(int n_thread = 1; n_thread <= n_threads; n_thread++) {
        cout << "Mean OpenMP execution time with "<< n_thread << " thread: " << floor(mean_openmp_test[n_thread-1] * 100.) / 100. << " milliseconds" << endl;
    }

    return 0;
}