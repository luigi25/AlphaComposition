from RGBAImage.RGBAimage import RGBAImage
from RGBAImage.imageReconstruction import imageReconstruction
import numpy as np
from AlphaBlendTests.sequentialAlphaBlend import sequentialTest
from AlphaBlendTests.parallelAlphaBlend import parallelTest
import cv2


def main():
    # Read the images
    imgA = RGBAImage("images/RayBan.png")
    flatImgA = imgA.createFlatImage()
    imgB = RGBAImage("images/Oro_Base.png")
    flatImgB = imgB.createFlatImage()
    imgSize = imgA.getSize()
    num_executions = 1
    n_threads = 2
    print("Sequential Test")
    # mean_sequential_test = sequentialTest(num_executions, imgSize, flatImgA, flatImgB)
    mean_sequential_test = sequentialTest(imgA, num_executions, imgSize, flatImgA, flatImgB)
    print("Mean Sequential execution time:", round(mean_sequential_test, 2), "milliseconds\n")

    print("Joblib Test")
    # mean_joblib_test = parallelTest(imgA, num_executions, n_threads, imgSize, flatImgA, flatImgB)
    mean_joblib_test = parallelTest(num_executions, n_threads, imgSize, flatImgA, flatImgB)
    for n_thread in range(2, n_threads + 1):
        print("Mean Joblib execution time with", n_thread, "thread:", round(mean_joblib_test[n_thread - 1], 2),
              "milliseconds")

    with open("alphaBlendTests.txt", "w") as file:
        file.write("Sequential Test")
        file.write("Mean Sequential execution time: " + str(round(mean_sequential_test, 2)) + " milliseconds\n")
        file.write("Joblib Test")
        for n_thread in range(2, n_threads + 1):
            file.write("Mean Joblib execution time with " + str(n_thread) + " thread: " + str(round(mean_joblib_test[n_thread - 1], 2)) + " milliseconds")
        file.close()


if __name__ == '__main__':
    main()
