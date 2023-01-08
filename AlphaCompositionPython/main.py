from RGBAImage.RGBAimage import RGBAImage
from AlphaBlendTests.sequentialAlphaBlend import sequentialTest, sequentialTestPlot
from AlphaBlendTests.parallelAlphaBlend import parallelTest, parallelTestPlot


def main():
    num_executions = 100
    n_threads = 20

    folder_names = ["480", "720", "1080", "2K", "4K"]
    for f in folder_names:
        flatImages = []
        # Read the images
        pandaImg = RGBAImage("./images/" + f + "/panda.png")
        flatPandaImg = pandaImg.createFlatImage()
        batmanImg = RGBAImage("./images/" + f + "/batman.png")
        flatBatmanImg = batmanImg.createFlatImage()
        hatImg = RGBAImage("./images/" + f + "/hat.png")
        flatHatImg = hatImg.createFlatImage()
        glassesImg = RGBAImage("./images/" + f + "/3DGlasses.png")
        flatGlassesImg = glassesImg.createFlatImage()
        canImg = RGBAImage("./images/" + f + "/can.png")
        flatCanImg = canImg.createFlatImage()
        flatImages.append(flatPandaImg)
        flatImages.append(flatBatmanImg)
        flatImages.append(flatHatImg)
        flatImages.append(flatGlassesImg)
        flatImages.append(flatCanImg)

        imgSize = pandaImg.getSize()

        # print("Sequential Test with " + f + "p")
        # # sequentialTestPlot(pandaImg, imgSize, flatImages)
        # mean_sequential_test = sequentialTest(num_executions, imgSize, flatImages)
        # print("Mean Sequential execution time:", round(mean_sequential_test, 2), "microseconds\n")

        print("Joblib Test with " + f + "p")
        # parallelTestPlot(pandaImg, n_threads, imgSize, flatImages)
        mean_joblib_test = parallelTest(num_executions, n_threads, imgSize, flatImages)
        index = 0
        for n_thread in range(2, n_threads + 1, 2):
            print("Mean Joblib execution time with", str(n_thread), "thread:",
                  str(round(mean_joblib_test[index], 2)), "microseconds")
            index = index + 1


if __name__ == '__main__':
    main()
