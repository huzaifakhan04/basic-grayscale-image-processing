//  Header file for the class defined for image processing.

#ifndef IMAGE_H
#define IMAGE_H
#include "Logger.h"

//  Defining the class for all the image processing operations.

class Image

{

    public:

        char PGMType[3];
        unsigned char** Data;
        unsigned int Width;
        unsigned int Height;
        unsigned int MaximumGreyValue;
        
                Image();
                int getWidth();
                int getHeight();
                int getMaximumGreyValue();
                void ignoreComments(FILE* FilePath);
                bool readPGMFile(Image* PGM, const char* FileName);
                void saveImageDetails(Image* PGM, const char* FileName);
                int getPixel(unsigned int Row, unsigned int Column);
                void setPixel(unsigned int Row, unsigned int Column, unsigned int Value);
                int getSize();
                void convertToNegative();
                int meanPixelValue();
                int numberOfBlackPixels();
                int numberOfWhitePixels();
                int averageBlackPixelsInRow();
                void displayImageDetails();

};

#endif