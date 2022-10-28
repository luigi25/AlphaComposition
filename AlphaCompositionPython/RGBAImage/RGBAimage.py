import cv2
import numpy as np


class RGBAImage:
    def __init__(self, path):
        self._image = cv2.imread(path, cv2.IMREAD_UNCHANGED)

        self._height = self._image.shape[0]
        self._width = self._image.shape[1]
        self._num_channels = self._image.shape[2]

    def getWidth(self):
        return self._width

    def getHeight(self):
        return self._height

    def getNumChannels(self):
        return self._num_channels

    def getSize(self):
        return self.getWidth() * self.getHeight() * self.getNumChannels()

    def createFlatImage(self):
        size = self.getSize()
        flatImage = np.zeros(shape=size)
        # scroll by rows
        for i in range(0, self.getHeight()):
            for j in range(0, self.getWidth()):
                pixel = self._image[i][j]
                flatImage[(i * self.getWidth() * self.getNumChannels()) + (j * self.getNumChannels())] = float(pixel[2])
                flatImage[(i * self.getWidth() * self.getNumChannels()) + (j * self.getNumChannels()) + 1] = float(pixel[1])
                flatImage[(i * self.getWidth() * self.getNumChannels()) + (j * self.getNumChannels()) + 2] = float(pixel[0])
                flatImage[(i * self.getWidth() * self.getNumChannels()) + (j * self.getNumChannels()) + 3] = float(pixel[3])
        return flatImage

    def showImage(self):
        cv2.imshow("RGBA image", self._image)
