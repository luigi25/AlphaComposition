import time
import cv2
import numpy as np
from RGBAImage.imageReconstruction import imageReconstruction
from RGBAImage.createMixedImage import create_mixed_image


def sequentialTest(imgA, num_executions, imgSize, flatImgA, flatImgB):
    mean_executions_time = 0
    for execution in range(0, num_executions):
        print("execution:", execution)
        flatMixImages = np.zeros(shape=imgSize)
        start = time.time()
        for i in range(0, imgSize, 4):
            create_mixed_image(flatMixImages[i:i + 4], flatImgA[i:i + 4], flatImgB[i:i + 4])

        exec_time = time.time() - start
        exec_time_milliseconds = exec_time * 1000
        mean_executions_time += exec_time_milliseconds

        # todo visualize result image (need to pass imgA image to the function)
        # reconstructed_image = imageReconstruction(flatMixImages, imgA.getWidth(), imgA.getHeight(),
        #                                           imgA.getNumChannels())
        # cv2.namedWindow("RGBA Image", cv2.WINDOW_NORMAL)
        # cv2.resizeWindow("RGBA Image", int(imgA.getWidth()*0.35), int(imgA.getHeight()*0.35))
        # cv2.imshow("RGBA Image", reconstructed_image)
        # cv2.waitKey(0)
        # cv2.imwrite("sequential.png", reconstructed_image)

        del flatMixImages

    return mean_executions_time / num_executions
