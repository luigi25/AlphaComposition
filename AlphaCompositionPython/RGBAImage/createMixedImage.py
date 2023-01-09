def create_mixed_image_parallel(flatMixImages, flatImages):
    # start alpha composition
    for i in range(0, len(flatMixImages), 4):
        r, g, b, a = 0, 0, 0, 0
        for j in range(0, len(flatImages)):
            alphaA = flatImages[j][i + 3] / 255
            alphaB = a / 255
            alpha_component = alphaA + alphaB * (1 - alphaA)
            if alpha_component == 0:
                r = 0
                g = 0
                b = 0
                a = 0
            else:
                r = (flatImages[j][i] * alphaA + r * alphaB * (1 - alphaA)) / alpha_component
                g = (flatImages[j][i + 1] * alphaA + g * alphaB * (1 - alphaA)) / alpha_component
                b = (flatImages[j][i + 2] * alphaA + b * alphaB * (1 - alphaA)) / alpha_component
                a = (((alpha_component - 0) * 255) / 1)
        flatMixImages[i] = r
        flatMixImages[i + 1] = g
        flatMixImages[i + 2] = b
        flatMixImages[i + 3] = a