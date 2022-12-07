from RGBAImage.RGBAimage import RGBAImage
from AlphaBlendTests.sequentialAlphaBlend import sequentialTest, sequentialTestPlot
from AlphaBlendTests.parallelAlphaBlend import parallelTest, parallelTestPlot


def main():
    flatImages = []
    # Read the images
    pandaImg = RGBAImage("./images/panda.png")
    flatPandaImg = pandaImg.createFlatImage()
    batmanImg = RGBAImage("./images/batman.png")
    flatBatmanImg = batmanImg.createFlatImage()
    hatImg = RGBAImage("./images/hat.png")
    flatHatImg = hatImg.createFlatImage()
    glassesImg = RGBAImage("./images/3DGlasses.png")
    flatGlassesImg = glassesImg.createFlatImage()
    canImg = RGBAImage("./images/can.png")
    flatCanImg = canImg.createFlatImage()
    flatImages.append(flatPandaImg)
    flatImages.append(flatBatmanImg)
    flatImages.append(flatHatImg)
    flatImages.append(flatGlassesImg)
    flatImages.append(flatCanImg)
    test_phase = False

    imgSize = pandaImg.getSize()
    numExecutions = 3
    n_threads = 16
    print("Sequential Test")


    # if test_phase:
    #     sequentialTestPlot(pandaImg, imgSize, flatImages)
    # else:
    #     mean_sequential_test = sequentialTest(numExecutions, imgSize, flatImages)
    #     print("Mean Sequential execution time:", round(mean_sequential_test, 2), "milliseconds\n")


    print("Joblib Test")
    if test_phase:
        parallelTestPlot(pandaImg, n_threads, imgSize, flatImages)
    else:
        mean_joblib_test = parallelTest(numExecutions, n_threads, imgSize, flatImages)
        for n_thread in range(2, n_threads + 1, 2):
            print("Mean Joblib execution time with", str(n_thread), "thread:", str(round(mean_joblib_test[int(n_thread/2) - 1], 2)), "milliseconds")

    # if not test_phase:
    #     with open("alphaBlendTests.txt", "w") as file:
    #         file.write("Sequential Test\n")
    #         file.write("Mean Sequential execution time: " + str(round(mean_sequential_test, 2)) + " milliseconds\n\n")
    #         file.write("Joblib Test\n")
    #         for n_thread in range(2, n_threads + 1, 2):
    #             file.write("Mean Joblib execution time with " + str(n_thread) + " thread: " + str(round(mean_joblib_test[int(n_thread/2) - 1], 2)) + " milliseconds\n")
    #         file.close()


if __name__ == '__main__':
    main()
