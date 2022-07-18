class RGBPixel:

    def __init__(self, red, green, blue, value):
        self.Red = red;
        self.Green = green;
        self.Blue = blue;
        self.value = value | (red << 16);
        self.value = value | (green << 8);
        self.value = value | (blue);

    def RGBPixel_copy(self, pixel):
        self.Red = pixel.Red;
        self.Green = pixel.Green;
        self.Blue = pixel.Blue;
        self.value = pixel.value;

    def RGBPixel_yuv(self, pixel):
        redToBe = ((298 * (pixel.getY() - 16) + 409 * (pixel.getV() - 128) + 128) >> 8);
        greenToBe = ((298 * (pixel.getY() - 16) - 100 * (pixel.getU() - 128) - 208 * (pixel.getV() - 128) + 128) >> 8);
        blueToBe = ((298 * (pixel.getY() - 16) + 516 * (pixel.getU() - 128) + 128) >> 8);

        if redToBe < 0:
            self.setRed(0);
        elif redToBe > 255:
            self.setRed(255);
        else:
            self.setRed(redToBe);

        if greenToBe < 0:
            self.setGreen(0);
        elif (greenToBe > 255):
            self.setGreen(255);
        else:
            self.setGreen(greenToBe);

        if blueToBe < 0:
            self.setBlue(0);
        elif blueToBe > 255:
            self.setBlue(255);
        else:
            self.setBlue(blueToBe);


    def getRed(self):
        return (self.Red);

    def getGreen(self):
        return (self.Green);

    def getBlue(self):
        return (self.Blue);

    def setRed(self, red):
        self.Red = red;
        self.value = self.value & 0x0000ffff;

        self.value = (red << 16) | self.value;

    def setGreen(self, green):
        self.Green = green;
        self.value = self.value & 0xffff00ff;
        self.value = self.value | (green << 8);

    def setBlue(self, blue):
        self.Blue = blue;
        self.value = self.value & 0x00ffff00;
        self.value = blue | self.value;

    def getRGB(self):
        return (self.value);

    def setRGB(self, value):
        self.setRed(((self.value & 0x00ff0000) >> 16));
        self.setBlue((self.value & 0x00000ff));
        self.setGreen(((self.value & 0x0000ff00) >> 8));


    def setRGB(self, red, green, blue):
        self.Red = red;
        self.Green = green;
        self.Blue = blue;
        
    def printPixel(self):
        print("Blue: ", self.Blue, " Red: ", self.Red, " Green: ", self.Green);


