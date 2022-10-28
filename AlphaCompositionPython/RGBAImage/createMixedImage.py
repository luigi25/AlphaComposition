def create_mixed_image(flatMixImages, flatImgA, flatImgB):
    alphaA = flatImgA[3] / 255
    alphaB = flatImgB[3] / 255
    alpha_component = alphaA + alphaB * (1 - alphaA)
    if alpha_component == 0:
        flatMixImages[0] = 0
        flatMixImages[1] = 0
        flatMixImages[2] = 0
        flatMixImages[3] = 0
    else:
        flatMixImages[0] = ((flatImgA[0] * alphaA + flatImgB[0] * alphaB * (1 - alphaA)) / alpha_component)
        flatMixImages[1] = ((flatImgA[1] * alphaA + flatImgB[1] * alphaB * (1 - alphaA)) / alpha_component)
        flatMixImages[2] = ((flatImgA[2] * alphaA + flatImgB[2] * alphaB * (1 - alphaA)) / alpha_component)
        flatMixImages[3] = (((alpha_component - 0) * 255) / 1)
    # print("Index", i)
