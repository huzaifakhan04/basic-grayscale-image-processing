#pragma warning(disable:4996)
#include<iostream>
#include<cctype>
#include<cstdbool>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include "Image.h"
#include "Logger.h"

//  Default constructor.

Image::Image()

{
        strcpy(this->PGMType, "P2");
        this->Data=nullptr;
        this->Width=0;
        this->Height=0;
        this->MaximumGreyValue=0;

}

//  Function to return the width of the image.

int Image::getWidth()

{
    return this->Width;
}

//  Function to return the height of the image.

int Image::getHeight()

{
    return this->Height;
}

//  Function to return the maximum value of the pixels in the image.

int Image::getMaximumGreyValue()

{
    return this->MaximumGreyValue;
}

//  Function to ignore any comments (characters that start with '#') in the file.

void Image::ignoreComments(FILE* FilePath)

{
    
    logger("Ignoring any comments in the file...");
    int Character;
    char Line[100];
        while((Character=fgetc(FilePath))!=EOF && isspace(Character));  //  Ignoring any white-spaces.

        //  Recursively ignoring any comments (characters that start with '#') in the file.

        if(Character=='#')
        {
            fgets(Line, sizeof(Line), FilePath);
            ignoreComments(FilePath);
        }
        else
        {
            fseek(FilePath, -1, SEEK_CUR);
        }

}

bool Image::readPGMFile(Image* PGM, const char* FileName)

{

    logger("Reading the PGM file...");
    FILE* PGMFile=fopen(FileName, "rb");    //  Reading the file in a binary format.
        if(PGMFile==nullptr)    //  Condition to check whether the file exists or not.
        {
                std::cout << "File does not exist!" << std::endl;
                logger("File does not exist!");
            return false;
        }
        ignoreComments(PGMFile);    //  Ignoring any comments (characters that start with '#') in the file.
        fscanf(PGMFile, "%s", PGM->PGMType);    //  Reading the PGM type from the file, and storing it in the respective variable.
        logger("Checking whether the file is of the correct PGM binary file type...");
        if(strcmp(PGM->PGMType, "P5"))  //  Condition to check whether the file is of the correct PGM binary file type or not.
        {
            std::cout << "Wrong file type!" << std::endl;
            logger("Wrong file type!");
            exit(EXIT_FAILURE);
        }
        ignoreComments(PGMFile);    //  Ignoring any comments (characters that start with '#') in the file.
        fscanf(PGMFile, "%d %d", &(PGM->Width), &(PGM->Height)); //  Reading the width and height of the image from the file, and storing them in the respective variables.
        ignoreComments(PGMFile);    //  Ignoring any comments (characters that start with '#') in the file.
        fscanf(PGMFile, "%d", &(PGM->MaximumGreyValue));    //  Reading the maximum gray value of the image from the file, and storing it in the respective variable.
        ignoreComments(PGMFile);    //  Ignoring any comments (characters that start with '#') in the file.
        PGM->Data=(unsigned char**)malloc(PGM->Height*sizeof(unsigned char*));  //  Allocating memory to store the image information in the defined class.

        //  Storing the pixel information.

        logger("Storing the pixel information...");
        if(PGM->PGMType[1]=='5')
        {
            fgetc(PGMFile);
            for(unsigned int i=0; i<PGM->Height; i++)
            {
                PGM->Data[i]=(unsigned char*)malloc(PGM->Width*sizeof(unsigned char));  //  Allocating memory to store the pixel information in the defined class.
                if(PGM->Data[i]==nullptr)   //  Condition to check whether the memory allocation was successful or not.
                {
                    std::cout << "Memory allocation failed!" << std::endl;
                    logger("Memory allocation failed!");
                    exit(1);
                }
                fread(PGM->Data[i], sizeof(unsigned char), PGM->Width, PGMFile);    //  Reading the grey values, and storing on the allocated memory.
            }
        }
        fclose(PGMFile);    //  Closing the file.
 
    return true;

}

//  Function to save/display the image details.

void Image::saveImageDetails(Image* PGM, const char* FileName)

{

    logger("Saving the image details...");
    FILE* PGMFile=fopen(FileName, "rb");    //  Reading the file in a binary format.
    const char* FileExtension=strrchr(FileName, '.'); //  Storing the file extension.
    logger("Displaying the image details...");
        if(!FileExtension)
        {
            std::cout << "File extension not found in " << FileName << std::endl;
            logger("File extension not found!");
        }
        else
        {
            std::cout << "File format:\t" << FileExtension+1 << std::endl;
        }
        std::cout << "PGM File Type:\t" << PGM->PGMType << std::endl;

        //  Printing the PGM file type in ASCII and binary format.

        if(!strcmp(PGM->PGMType, "P2"))
        {
            std::cout << "PGM File Type:\tASCII" << std::endl;
        }
        else if(!strcmp(PGM->PGMType, "P5"))
        {
            std::cout << "PGM File Type:\tBinary" << std::endl;
        }
        else
        {
            std::cout << "PGM File Type:\tUnknown" << std::endl;
        }
        std::cout << "Width:\t" << PGM->Width << " Pixels" << std::endl;
        std::cout << "Height:\t" << PGM->Height << " Pixels" << std::endl;
        std::cout << "Maximum Grey Value:\t" << PGM->MaximumGreyValue << std::endl;
        fclose(PGMFile);    //  Closing the file.

}

//  Function to retrieve the pixel information.

int Image::getPixel(unsigned int Row, unsigned int Column)

{
    
        logger("Retrieving the pixel information...");
        if(Row>this->Height || Column>this->Width || Row<this->Height || Column<this->Width)    //  Condition to check whether the pixel information is within the image dimensions or not.
        {
                std::cout << "Invalid pixel location!" << std::endl;
                logger("Invalid pixel location!");
            exit(EXIT_FAILURE);
        }

    return this->Data[Row][Column];

}

//  Function to set the pixel information.

void Image::setPixel(unsigned int Row, unsigned int Column, unsigned int Value)

{

        logger("Setting the pixel information...");
        if(Value>255 || Value<0)    //  Condition to check whether the pixel information is within the maximum grey value or not.
        {
                std::cout << "Pixel value out of range!" << std::endl;
                logger("Pixel value out of range!");
            exit(EXIT_FAILURE);
        }
        if(Row>this->Height || Column>this->Width || Row<this->Height || Column<this->Width)    //  Condition to check whether the pixel information is within the image dimensions or not.
        {
                std::cout << "Invalid pixel location!" << std::endl;
                logger("Invalid pixel location!");
            exit(EXIT_FAILURE);
        }
        this->Data[Row][Column]=Value;

}

//  Function to return the image size.

int Image::getSize()

{

        logger("Retrieving the image size...");
    return (this->Height*this->Width);

}

//  Function to convert the image to negative.

void Image::convertToNegative()

{

        logger("Converting the image to negative...");
        for(unsigned int i=0; i<this->Height; i++)
        {
            for(unsigned int j=0; j<this->Width; j++)
            {

                //  Inverting the values of all the black and white pixels.

                if(this->Data[i][j]==0)
                {
                    this->Data[i][j]=255;
                }
                else
                {
                    this->Data[i][j]=0;
                }
            }
        }

}

//  Function to calculate and return the mean pixel value of the image.

int Image::meanPixelValue()

{

    int MeanPixelValue=0;
        logger("Calculating the mean pixel value...");
        for(unsigned int i=0; i<this->Height; i++)
        {
            for(unsigned int j=0; j<this->Width; j++)
            {
                MeanPixelValue+=this->Data[i][j];
            }
        }
        MeanPixelValue/=this->Height*this->Width;   //  Calculating the mean pixel value.

    return MeanPixelValue;

}

//  Function to calculate and return the number of black pixels in the image.

int Image::numberOfBlackPixels()

{

    int NumberOfBlackPixels=0;
        logger("Calculating the number of black pixels...");
        for(unsigned int i=0; i<this->Height; i++)
        {
            for(unsigned int j=0; j<this->Width; j++)
            {
                if(this->Data[i][j]==0) //  Condition to check whether the pixel is black or not.
                {
                    NumberOfBlackPixels++;
                }
            }
        }

    return NumberOfBlackPixels;

}

//  Function to calculate and return the number of white pixels in the image.

int Image::numberOfWhitePixels()

{

    int NumberOfWhitePixels=0;
        logger("Calculating the number of white pixels...");
        for(unsigned int i=0; i<this->Height; i++)
        {
            for(unsigned int j=0; j<this->Width; j++)
            {
                if(this->Data[i][j]==this->MaximumGreyValue)    //  Condition to check whether the pixel is white or not.
                {
                    NumberOfWhitePixels++;
                }
            }
        }

    return NumberOfWhitePixels;

}

//  Function to calculate and return the average number of black pixels in each row of the image.

int Image::averageBlackPixelsInRow()

{

    int AverageBlackPixelsInRow=0;
        logger("Calculating the average number of black pixels in a row...");
        for(unsigned int i=0; i<this->Height; i++)
        {
            for(unsigned int j=0; j<this->Width; j++)
            {
                if(this->Data[i][j]==0)
                {
                    AverageBlackPixelsInRow++;
                }
            }
        }
        AverageBlackPixelsInRow/=this->Height; //  Calculating the average number of black pixels in a row.

    return AverageBlackPixelsInRow;

}

void Image::displayImageDetails()

{

        logger("Displaying the image details...");
        std::cout << "PGM File Type:\t" << this->PGMType << std::endl;

        //  Printing the PGM file type in ASCII and binary format.

        if(!strcmp(this->PGMType, "P2"))
        {
            std::cout << "PGM File Type:\tASCII" << std::endl;
        }
        else if(!strcmp(this->PGMType, "P5"))
        {
            std::cout << "PGM File Type:\tBinary" << std::endl;
        }
        else
        {
            std::cout << "PGM File Type:\tUnknown" << std::endl;
        }
        std::cout << "Width:\t" << this->Width << " Pixels" << std::endl;
        std::cout << "Height:\t" << this->Height << " Pixels" << std::endl;
        std::cout << "Maximum Grey Value:\t" << this->MaximumGreyValue << std::endl;

}