import numpy as np


def imageReconstruction(flatImg, width, height, channels):
    reconstructed_image = np.zeros(shape=(height, width, channels), dtype=np.uint8)

    for i in range(0, height):
        for j in range(0, width):
            reconstructed_image[i, j, 0] = np.uint8(flatImg[(i * width * channels) + (j * channels) + 2])
            reconstructed_image[i, j, 1] = np.uint8(flatImg[(i * width * channels) + (j * channels) + 1])
            reconstructed_image[i, j, 2] = np.uint8(flatImg[(i * width * channels) + (j * channels)])
            reconstructed_image[i, j, 3] = np.uint8(flatImg[(i * width * channels) + (j * channels) + 3])

    return reconstructed_image
