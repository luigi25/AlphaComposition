import cv2
import numpy as np


class RGBAImage:
    def __init__(self, path):
        self._image = cv2.imread(path, cv2.IMREAD_UNCHANGED)

        self._height = self._image.shape[0]
        self._width = self._image.shape[1]
        self._numChannels = self._image.shape[2]

    def getWidth(self):
        return self._width

    def getHeight(self):
        return self._height

    def getNumChannels(self):
        return self._numChannels

    def getSize(self):
        return self._width * self._height * self._numChannels

    def createFlatImage(self):
        size = self.getSize()
        flatImage = np.zeros(shape=size)
        # scroll by rows
        for i in range(0, self._height):
            for j in range(0, self._width):
                pixel = self._image[i][j]
                flatImage[(i * self._width * self._numChannels) + (j * self._numChannels)] = float(pixel[2])
                flatImage[(i * self._width * self._numChannels) + (j * self._numChannels) + 1] = float(pixel[1])
                flatImage[(i * self._width * self._numChannels) + (j * self._numChannels) + 2] = float(pixel[0])
                flatImage[(i * self._width * self._numChannels) + (j * self._numChannels) + 3] = float(pixel[3])
        return flatImage

    def showImage(self):
        cv2.imshow("RGBA image", self._image)
