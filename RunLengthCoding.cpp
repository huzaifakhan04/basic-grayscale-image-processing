#include<iostream>
#include<cctype>
#include<cstdbool>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<fstream>
#include "LinkedList.h"
#include "Image.h"
#include "RunLengthCoding.h"
#include "Logger.h"
#include "LinkedList.cpp"

static int WhitePixelCount=0;   //  Global variable to store the total number of white pixels in the image.

//  Function to execute the run-length encoding algorithm on the image using the doubly linked list data structure.

void RunLengthCoding::runLengthEncoding(Image* RLC)

{

        logger("Performing the run-length encoding algorithm using the doubly linked list data structure...");
    LinkedList<int> *List=new LinkedList<int>();    //  Creating a doubly linked list object.

        //  Loop to traverse the image data, and perform the run-length encoding algorithm.

        for(int i=0; i<RLC->getHeight(); i++)
        {
            for(int j=0; j<RLC->getWidth(); j++)
            {
                if(RLC->Data[i][j]==255)    //  Conditiion to check whether the specific pixel is white or not.
                {
                    WhitePixelCount++;  //  Incrementing the total number of white pixels in the image.
                    if(RLC->Data[i][j-1]==0)    //  Condition to check whether the previous pixel is black or not.
                    {
                        List->addLast(j);   //  Adding the column number of the white pixel to the doubly linked list.
                    }
                    if(RLC->Data[i][j+1]==0)    //  Condition to check whether the next pixel is black or not.
                    {
                        List->addLast(j);   //  Adding the column number of the white pixel to the doubly linked list.
                    }
                }
            }
            List->addLast(-1);  //  Adding the delimiter to the doubly linked list.
        }

    //  Writing the encoded data into a separate file.

    std::ofstream File;
        File.open("encoded_image.txt");
        File << RLC->getHeight() << " " << RLC->getWidth() << std::endl;

        //  Loop to traverse the doubly linked list, and write the encoded data into a separate file.

        for(int i=0;i<List->Size;i++)
        {
            if(List->getAt(i)==-1 && List->getAt(i)!=(RLC->getWidth())-1 && List->getAt(i)!=(RLC->getWidth())-2)    //    Condition to check whether the delimiter is encountered or not.
            {
                File << List->getAt(i) << std::endl;
            }
            else if(List->getAt(i)!=-1 && List->getAt(i)!=(RLC->getWidth())-1 && List->getAt(i)!=(RLC->getWidth())-2)   //  Condition to check whether the delimiter is not encountered.
            {
                File << List->getAt(i) << " ";
            }
        }
        File.close();

}

//  Function to execute the run-length decoding algorithm on the image using the doubly linked list data structure.

void RunLengthCoding::runLengthDecoding(std::string InputFile)

{

    //  Reading the encoded data from the stored file.
    
    std::ifstream File;
        File.open(InputFile.c_str());
    int Height;
    int Width;
        File >> Height >> Width;    //  Reading the height and width of the image.
    int Data;
    LinkedList<int> *List=new LinkedList<int>();    //  Creating a doubly linked list object.

        //  Loop to read the encoded data from the stored file, and store it in a doubly linked list.

        while(File >> Data)
        {
            List->addLast(Data);
        }
        File.close();

    //  Creating a separate file to store the decoded image in.

    std::ofstream DecodedImageFile;
        DecodedImageFile.open("decoded_image.txt", std::ios::out);

        //  Writing the header information into the decoded image file.

        DecodedImageFile << "P5" << std::endl;
        DecodedImageFile << Width << " " << Height << std::endl;
        DecodedImageFile << 255 << std::endl;

    LinkedList<int>::Node *Iterator=List->Head; //  Creating an iterator to traverse the doubly linked list.
    int HighLimit=0;
    int LowLimit=0;
    int Line=0;
    int MaximumLimit=Iterator->Data;
        Iterator=Iterator->Next;
    int Temporary=MaximumLimit*Iterator->Data;
    int WhitePixels=0;

        //  Loop to traverse the doubly linked list, and perform the run-length decoding algorithm.

        for(int i=0; i<Temporary; ) //  Creating an infinite loop (terminates only when a certain condition is fulfilled).
        {
            if(Iterator->Next==NULL)    //  Condition to check whether the end of the doubly linked list is reached or not.
            {
                break;
            }
            Iterator=Iterator->Next;    //  Incrementing the iterator to the next node.
            Line=Iterator->Data;    //  Storing the column number of the white pixel.
            if(Line==-1)    //  Condition to check whether the delimiter is encountered or not.
            {
                if(HighLimit<=MaximumLimit)   //  Condition to check whether the end of the image is reached or not.
                {
                    for(int j=HighLimit; j<MaximumLimit; j++)
                    {
                        DecodedImageFile << " ";
                    }
                }
                LinkedList<int>::Node *Temporary=Iterator->Next;    //  Creating a temporary node to store the next node of the iterator.
                if(Iterator->Next==NULL)    //  Condition to check whether the end of the temporary doubly linked list is reached or not.
                {
                    break;
                }
                if(Temporary->Data==-1) //  Condition to check whether the delimiter is encountered or not.
                {
                    for(int j=MaximumLimit-HighLimit; j<MaximumLimit; j++)  //  Loop to write the white pixels into the decoded image file.
                    {
                        DecodedImageFile << " ";
                    }
                }
                DecodedImageFile << std::endl;
                WhitePixels=0;
            }
            else
            {
                LowLimit=Line;  //  Storing the column number of the white pixel.
                for(int j=WhitePixels; j<Line; j++)  //  Loop to write the white pixels into the decoded image file.
                {
                    DecodedImageFile << " ";
                }
                Iterator=Iterator->Next;    //  Incrementing the iterator to the next node.
                if(Iterator->Next==NULL)    //  Condition to check whether the end of the doubly linked list is reached or not.
                {
                    break;
                }
                HighLimit=Iterator->Data;   //  Storing the column number of the white pixel.
                for(int j=LowLimit; j<HighLimit; j++)   //  Loop to write the black pixels into the decoded image file.
                {
                    DecodedImageFile << 0;
                }
                WhitePixels=HighLimit;   //  Storing the column number of the white pixel.
            }
        }
        DecodedImageFile.close();

}

//  Function to compute the total number of black pixels in the image.

int RunLengthCoding::totalBlackPixels()

{

        logger("Computing the total number of black pixels in the image...");

    //  Reading the encoded data from the stored file.

        logger("Reading the encoded data from the stored file...");
    std::ifstream File;
        File.open("encoded_image.txt");
        int Height=0;
        int Width=0;
        File >> Height >> Width;
        File.close();

    return (Height*Width)-WhitePixelCount;


}