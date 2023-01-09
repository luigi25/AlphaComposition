import os
import shutil
import time
import cv2
import numpy as np
from joblib import Parallel, delayed
from RGBAImage.imageReconstruction import imageReconstruction
from RGBAImage.createMixedImage import create_mixed_image_parallel


def parallelTest(num_executions, nThreads, imgSize, flatImages):
    mean_executions_time_vec = np.zeros(shape=nThreads)
    # create shared memory location where threads can write
    folder = "shared_mem/"
    if not os.path.exists(folder):
        os.makedirs(folder)
    output_filename_memmap = os.path.join(folder, 'flatMixImage')

    index = 0
    for n_thread in range(2, nThreads + 1, 2):
        mean_executions_time = 0
        # compute chunk and bounds
        chunk = int(imgSize / n_thread / 4)
        bounds = []
        for i in range(0, n_thread - 1):
            bounds.append((i * 4 * chunk, (i + 1) * 4 * chunk))
        bounds.append(((n_thread - 1) * 4 * chunk, imgSize))
        for execution in range(0, num_executions):
            # create the output image
            flatMixImage = np.memmap(output_filename_memmap, shape=imgSize, mode='w+')
            start = time.time()
            # multiprocessing, threading, loky backend
            Parallel(n_jobs=n_thread, backend="loky", mmap_mode="r+")(
                delayed(create_mixed_image_parallel)(flatMixImage[bounds[i][0]:bounds[i][1]],
                                                     [image[bounds[i][0]:bounds[i][1]] for image in flatImages]) for i in range(0, n_thread))

            exec_time = time.time() - start
            exec_time_microseconds = exec_time * pow(10, 6)
            mean_executions_time += exec_time_microseconds

            del flatMixImage
        mean_executions_time_vec[index] = mean_executions_time / num_executions
        index = index + 1

    try:
        shutil.rmtree(folder)
    except:
        print('Could not clean-up automatically.')

    return mean_executions_time_vec


def parallelTestPlot(pandaImg, nThreads, imgSize, flatImages):
    folder = "shared_mem/"
    if not os.path.exists(folder):
        os.makedirs(folder)
    output_filename_memmap = os.path.join(folder, 'flatMixImage')

    for n_thread in range(2, nThreads + 1, 2):
        print("n_thread:", n_thread)
        chunk = int(imgSize / n_thread / 4)
        bounds = []
        for i in range(0, n_thread - 1):
            bounds.append((i * 4 * chunk, (i + 1) * 4 * chunk))
        bounds.append(((n_thread - 1) * 4 * chunk, imgSize))

        flatMixImage = np.memmap(output_filename_memmap, shape=imgSize, mode='w+')

        Parallel(n_jobs=n_thread, backend="loky", mmap_mode="r+")(
            delayed(create_mixed_image_parallel)(flatMixImage[bounds[i][0]:bounds[i][1]],
                                                 [image[bounds[i][0]:bounds[i][1]] for image in flatImages]) for i in range(0, n_thread))

        reconstructed_image = imageReconstruction(flatMixImage, pandaImg.getWidth(), pandaImg.getHeight(),
                                                  pandaImg.getNumChannels())
        # cv2.namedWindow("RGBA Image", cv2.WINDOW_NORMAL)
        # cv2.resizeWindow("RGBA Image", int(pandaImg.getWidth() * 0.35), int(pandaImg.getHeight() * 0.35))
        # cv2.imshow("RGBA Image", reconstructed_image)
        # cv2.waitKey(0)
        cv2.imwrite("results/parallel_" + str(n_thread) + ".png", reconstructed_image)
        del flatMixImage
    try:
        shutil.rmtree(folder)
    except:
        print('Could not clean-up automatically.')
