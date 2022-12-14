//  Header file for the class defined for hashing operations on the images (objects).

#ifndef HASH_H
#define HASH_H
#include<list>
#include "Image.h"
#include "LinkedList.h"
#include "Logger.h"

//  Function to calculate the sum of the four-digit folding of the projection profile of the image.

inline int sumFourDigitFolding(Image* Horizontal, Image* Vertical)

{

    
    //  Computing the horizontal projection profile of the image.
    
        logger("Computing the horizontal projection profile of the image...");
    int *HorizontalProjection=new int[Horizontal->Height];
        for(unsigned int i=0; i<Horizontal->Height; i++)
        {
            HorizontalProjection[i]=0;
        }
        for(unsigned int i=0; i<Horizontal->Height; i++)
        {
            for(unsigned int j=0; j<Horizontal->Width; j++)
            {
                if(Horizontal->Data[i][j]==0)   //  Condition to check whether the pixel is black or not.
                {
                    Horizontal->Data[i][j]=1;   //  Converting all the black pixels to '1'.
                }
                else if(Horizontal->Data[i][j]==255)    //  Condition to check whether the pixel is white or not.
                {
                    Horizontal->Data[i][j]=0;   //  Converting all the white pixels to '0'.
                }
            }
        }

        //  Calculating the sum of all '1' for every row of the image.

        for(unsigned int i=0; i<Horizontal->Height; i++)
        {
            for(unsigned int j=0; j<Horizontal->Width; j++)
            {
                HorizontalProjection[i]+=Horizontal->Data[i][j];
            }
        }

    //  Computing the vertical projection profile of the image.

        logger("Computing the vertical projection profile of the image...");
    int *VerticalProjection=new int[Vertical->Width];
        for(unsigned int i=0; i<Vertical->Width; i++)
        {
            VerticalProjection[i]=0;
        }
        for(unsigned int i=0; i<Vertical->Height; i++)
        {
            for(unsigned int j=0; j<Vertical->Width; j++)
            {
                if(Vertical->Data[i][j]==0) //  Condition to check whether the pixel is black or not.
                {
                    Vertical->Data[i][j]=1; //  Converting all the black pixels to '1'.
                }
                else if(Vertical->Data[i][j]==255)  //  Condition to check whether the pixel is white or not.
                {
                    Vertical->Data[i][j]=0; //  Converting all the white pixels to '0'.
                }
            }
        }

        //  Calculating the sum of all '1' for every column of the image.

        for(unsigned int i=0; i<Vertical->Width; i++)
        {
            for(unsigned int j=0; j<Vertical->Height; j++)
            {
                VerticalProjection[i]+=Vertical->Data[j][i];
            }
        }

    //  Combining both the horizontal and vertical projection profiles into a single array.

        logger("Combining both the horizontal and vertical projection profiles into a single array...");
    int *MergedArray=new int[Horizontal->Height+Vertical->Width];
        for(unsigned int i=0; i<Horizontal->Height+Vertical->Width; i++)
        {
            MergedArray[i]=0;
        }
        for(unsigned int i=0; i<Horizontal->Height; i++)
        {
            MergedArray[i]=HorizontalProjection[i];
        }
        for(unsigned int i=0; i<Vertical->Width; i++)
        {
            MergedArray[i+Vertical->Height]=VerticalProjection[i];
        }
    unsigned int Size=Horizontal->Height+Vertical->Width;

    //  Calculating the sum of the four-digit folding of the projection profile of the image.

        logger("Calculating the sum of the four-digit folding of the projection profile of the image...");
    int Remainder=Size%4;   //  Checking if the array can be divided into four equal segments or not.

        //  If the array cannot be divided into four equal segments, zeros are added to the end of the array, so that it can be divided into four equal segments.
        if(Remainder!=0)
        {
            int* Temporary=new int[Size+4-Remainder];   //  Creating a temporary array to store the modified array into.
            for(unsigned int i=0; i<Size; i++)
            {
                Temporary[i]=MergedArray[i];    //  Copying the elements of the previous array into the newly created array.
            }

            //  Adding zeros to the end of the newly created array.

            for(unsigned int i=Size; i<Size+4-Remainder; i++)
            {
                Temporary[i]=0;
            }
            delete[] MergedArray;
            MergedArray=Temporary;  //  Assigning the modified array to the original array.
            Size=Size+4-Remainder;  //  Updating the size of the array.
        }

    //  Calculating the sum of the four-digit folding of the projection profile of the image.

    int Sum=0;
        for(unsigned int i=0; i<Size; i=i+4)    //  Iterating through the array in steps of four.
        {
            Sum+=MergedArray[i]*1000+MergedArray[i+1]*100+MergedArray[i+2]*10+MergedArray[i+3];
        }

    return Sum;

}

//  Defining the class to store image objects in a hash table.

class Hash

{

    std::list<Image> *Table;
    int Size;

        public:

            Hash();
            Hash(int Size);
            int hashFunction(int Key);
            void insert(Image* PGM);
            void display();
            bool search(std::string FileName);
            void remove(int Key);

};

#endif