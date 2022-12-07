import time
import cv2
import numpy as np
from RGBAImage.imageReconstruction import imageReconstruction


def sequentialTest(num_executions, imgSize, flatImages):
    mean_executions_time = 0
    for execution in range(0, num_executions):
        print("execution:", execution)
        flatMixImages = np.zeros(shape=imgSize)
        for i in range(0, imgSize):
            flatMixImages[i] = flatImages[0][i]
        start = time.time()
        for i in range(0, imgSize, 4):
            # create_mixed_image_sequential(flatMixImages[i:i + 4], [flatImages[j][i:i + 4] for j in range(len(flatImages)) if j > 0])
            for j in range(1, len(flatImages)):
                alphaA = flatImages[j][i + 3] / 255
                alphaB = flatMixImages[i + 3] / 255
                alpha_component = alphaA + alphaB * (1 - alphaA)
                if alpha_component == 0:
                    flatMixImages[i] = 0
                    flatMixImages[i + 1] = 0
                    flatMixImages[i + 2] = 0
                    flatMixImages[i + 3] = 0
                else:
                    flatMixImages[i] = ((flatImages[j][i] * alphaA + flatMixImages[i] * alphaB * (1 - alphaA)) / alpha_component)
                    flatMixImages[i + 1] = ((flatImages[j][i + 1] * alphaA + flatMixImages[i + 1] * alphaB * (1 - alphaA)) / alpha_component)
                    flatMixImages[i + 2] = ((flatImages[j][i + 2] * alphaA + flatMixImages[i + 2] * alphaB * (1 - alphaA)) / alpha_component)
                    flatMixImages[i + 3] = (((alpha_component - 0) * 255) / 1)

        exec_time = time.time() - start
        exec_time_milliseconds = exec_time * 1000
        mean_executions_time += exec_time_milliseconds

        del flatMixImages

    return mean_executions_time / num_executions


def sequentialTestPlot(pandaImg, imgSize, flatImages):
    flatMixImages = np.zeros(shape=imgSize)
    for i in range(0, imgSize):
        flatMixImages[i] = flatImages[0][i]
    for i in range(0, imgSize, 4):
        # create_mixed_image_sequential(flatMixImages[i:i + 4], [flatImages[j][i:i + 4] for j in range(len(flatImages)) if j > 0])
        for j in range(1, len(flatImages)):
            alphaA = flatImages[j][i + 3] / 255
            alphaB = flatMixImages[i + 3] / 255
            alpha_component = alphaA + alphaB * (1 - alphaA)
            if alpha_component == 0:
                flatMixImages[i] = 0
                flatMixImages[i + 1] = 0
                flatMixImages[i + 2] = 0
                flatMixImages[i + 3] = 0
            else:
                flatMixImages[i] = ((flatImages[j][i] * alphaA + flatMixImages[i] * alphaB * (1 - alphaA)) / alpha_component)
                flatMixImages[i + 1] = ((flatImages[j][i + 1] * alphaA + flatMixImages[i + 1] * alphaB * (1 - alphaA)) / alpha_component)
                flatMixImages[i + 2] = ((flatImages[j][i + 2] * alphaA + flatMixImages[i + 2] * alphaB * (1 - alphaA)) / alpha_component)
                flatMixImages[i + 3] = (((alpha_component - 0) * 255) / 1)

    reconstructed_image = imageReconstruction(flatMixImages, pandaImg.getWidth(), pandaImg.getHeight(),
                                              pandaImg.getNumChannels())
    # cv2.namedWindow("RGBA Image", cv2.WINDOW_NORMAL)
    # cv2.resizeWindow("RGBA Image", int(pandaImg.getWidth() * 0.35), int(pandaImg.getHeight() * 0.35))
    # cv2.imshow("RGBA Image", reconstructed_image)
    # cv2.waitKey(0)
    cv2.imwrite("results/sequential.png", reconstructed_image)
    del flatMixImages