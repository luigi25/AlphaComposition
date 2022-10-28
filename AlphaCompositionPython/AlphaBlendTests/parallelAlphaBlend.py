import os
import shutil
import time
import cv2
import numpy as np
from joblib import Parallel, delayed
from RGBAImage.imageReconstruction import imageReconstruction
from RGBAImage.createMixedImage import create_mixed_image


def parallelTest(num_executions, nThreads, imgSize, flatImgA, flatImgB):
    mean_executions_time_vec = np.zeros(shape=nThreads)
    folder = "shared_mem/"
    if not os.path.exists(folder):
        os.makedirs(folder)
    output_filename_memmap = os.path.join(folder, 'flatMixImage')

    for n_thread in range(2, nThreads + 1):
        print("n_thread:", n_thread)
        mean_executions_time = 0
        for execution in range(0, num_executions):
            print("execution:", execution)
            flatMixImage = np.memmap(output_filename_memmap, shape=imgSize, mode='w+')
            start = time.time()
            # todo try with loky and multithreading backend
            Parallel(n_jobs=n_thread, backend="multiprocessing", mmap_mode="r+")(
                delayed(create_mixed_image)(flatMixImage[i:i + 4], flatImgA[i:i + 4], flatImgB[i:i + 4]) for i in
                range(0, imgSize, 4))

            exec_time = time.time() - start
            exec_time_milliseconds = exec_time * 1000
            mean_executions_time += exec_time_milliseconds

            # todo visualize result image (need to pass imgA image to the function)
            # if n_thread == 2:
            #     reconstructed_image = imageReconstruction(flatMixImage, imgA.getWidth(), imgA.getHeight(),
            #                                               imgA.getNumChannels())
            #     cv2.namedWindow("RGBA Image", cv2.WINDOW_NORMAL)
            #     cv2.resizeWindow("RGBA Image", int(imgA.getWidth() * 0.35), int(imgA.getHeight() * 0.35))
            #     cv2.imshow("RGBA Image", reconstructed_image)
            #     cv2.waitKey(0)

            del flatMixImage
        mean_executions_time_vec[n_thread - 1] = mean_executions_time / num_executions

    try:
        shutil.rmtree(folder)
    except:
        print('Could not clean-up automatically.')

    return mean_executions_time_vec
