from RGBAImage.RGBAimage import RGBAImage
from AlphaBlendTests.sequentialAlphaBlend import sequentialTest, sequentialTestPlot
from AlphaBlendTests.parallelAlphaBlend import parallelTest, parallelTestPlot


def main():
    numExecutions = 3
    n_threads = 16

    folder_names = ["720", "1080", "2K", "4K"]
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

        print("Sequential Test with " + f + "p")
        # sequentialTestPlot(pandaImg, imgSize, flatImages)
        mean_sequential_test = sequentialTest(numExecutions, imgSize, flatImages)
        print("Mean Sequential execution time:", round(mean_sequential_test, 2), "milliseconds\n")


        print("Joblib Test with " + f + "p")
        # parallelTestPlot(pandaImg, n_threads, imgSize, flatImages)
        mean_joblib_test = parallelTest(numExecutions, n_threads, imgSize, flatImages)
        for n_thread in range(2, n_threads + 1, 2):
            print("Mean Joblib execution time with", str(n_thread), "thread:", str(round(mean_joblib_test[int(n_thread/2) - 1], 2)), "milliseconds")




if __name__ == '__main__':
    main()
