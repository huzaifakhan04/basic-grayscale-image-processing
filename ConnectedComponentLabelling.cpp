#pragma warning(disable:4996)
#include<iostream>
#include<cctype>
#include<cstdbool>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include "Queue.h"
#include "Stack.h"
#include "Image.h"
#include "ConnectedComponentLabelling.h"
#include "Logger.h"
#include "Queue.cpp"
#include "Stack.cpp"

//  Function to extract the connected components from the given image region using the queue data structure.

int ConnectedComponentLabelling::connectedComponentLabellingQueue(Image* CCL, unsigned int UserHeight, unsigned int UserWidth)

{

        if(UserHeight<0 || UserWidth<0 || UserHeight>CCL->Height || UserWidth>CCL->Width) //  Condition to check whether the input received is within the image dimensions.
        {
            std::cout << "Invalid height and width!" << std::endl;
            logger("Invalid height and width!");
            exit(1);
        }
        logger("Performing the connected component labelling algorithm using the queue data structure...");
    int Label=1;
    int **LabelledImage=new int*[UserHeight];   //  Creating a two-dimensional array to store the labelled image.
        for(unsigned int i=0; i<UserHeight; i++)
        {
            LabelledImage[i]=new int[UserWidth];
        }
        for(unsigned int i=0; i<UserHeight; i++)    //  Initialising the newly created two-dimensional array.
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                LabelledImage[i][j]=0;
            }
        }

        //  Performing the connected-component labelling algorithm using the queue data structure.

        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                if(CCL->Data[i][j]==0 && LabelledImage[i][j]==0)   //  Condition to check whether the certain dimension is both a black pixel and unlabelled.
                {
                    class Queue<int> RowQueue;   //  Creating a queue to store the row values.
                    class Queue<int> ColumnQueue;    //  Creating a queue to store the column values.
                        RowQueue.enqueue(i);
                        ColumnQueue.enqueue(j);
                        while(!RowQueue.isEmpty() && !ColumnQueue.isEmpty())    //  Condition to check whether the queue is empty or not.
                        {
                            unsigned int Row=RowQueue.peek();
                            unsigned int Column=ColumnQueue.peek();
                                RowQueue.dequeue();
                                ColumnQueue.dequeue();
                                if(Row>=0 && Row<UserHeight && Column>=0 && Column<UserWidth && CCL->Data[Row][Column]==0 && LabelledImage[Row][Column]==0)    //  Condition for exception handling, and to check whether the certain dimension is both a black pixel and unlabelled.
                                {
                                    LabelledImage[Row][Column]=Label;
                                    RowQueue.enqueue(Row-1);
                                    ColumnQueue.enqueue(Column);
                                    RowQueue.enqueue(Row+1);
                                    ColumnQueue.enqueue(Column);
                                    RowQueue.enqueue(Row);
                                    ColumnQueue.enqueue(Column-1);
                                    RowQueue.enqueue(Row);
                                    ColumnQueue.enqueue(Column+1);
                                }
                        }
                        Label++;
                }
            }
        }

    //  Relabelling the labelled image to be exported to the output file.

        logger("Relabelling the labelled image...");
    int *RelabelledImage=new int[Label];    //  Creating a one-dimensional array to store the relabelled image.
        for(int i=0; i<Label; i++)
        {
            RelabelledImage[i]=0;
        }
        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                if(LabelledImage[i][j]==0)  //  Condition to check whether the certain dimension is unlabelled or not.
                {
                    RelabelledImage[LabelledImage[i][j]]++;
                }
            }
        }
        int NewLabel=1;
        for(int i=1; i<Label; i++)
        {
            if(RelabelledImage[i]!=0)   //  Condition to check whether the certain pixel is a black pixel or not.
            {
                RelabelledImage[i]=NewLabel;
                NewLabel++;
            }
        }
        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                if(LabelledImage[i][j]==0)  //  Condition to check whether the certain dimension is unlabelled or not.
                {
                    LabelledImage[i][j]=RelabelledImage[LabelledImage[i][j]];   //  Relabelling the unlabelled dimension of the image with the new label.
                }
            }
        }

    //  Writing the labelled image into a separate file.

        logger("Writing the labelled image (queue) into a file...");
    std::string Time=getCurrentDateTime("Time");    //  Retrieving the current time from the system module.
    const char* TimeString=Time.c_str();
    std::string LabelledImageFileName="labelled-image_queue_";
        LabelledImageFileName+=TimeString;
        LabelledImageFileName+=".pgm";
    const char* FileName=LabelledImageFileName.c_str(); //  Storing the file name for the labelled image file in a variable.
    FILE *LabelledImageFile=fopen(FileName, "wb");   //  Opening the labelled image file for writing in a binary format.

        //  Writing the header information into the labelled image file.

        fprintf(LabelledImageFile, "%s\n", CCL->PGMType);
        fprintf(LabelledImageFile, "%d %d\n", UserWidth, UserHeight);
        fprintf(LabelledImageFile, "%d\n", CCL->MaximumGreyValue);

        //  Writing the labelled image into the defined labelled image file.

        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                fputc(LabelledImage[i][j], LabelledImageFile);  //  Writing a single character at a time into the labelled image file.
            }
        }
        fclose(LabelledImageFile);  //  Closing the labelled image file.
        logger("Labelled image written (queue) into a file successfully!");

        //  Deallocting the dynamically allocated memory for the labelled image.

        for(unsigned int i=0; i<UserHeight; i++)
        {
            delete[] LabelledImage[i];
        }
        delete[] LabelledImage;

    return Label-1;

}

//  Function to extract the connected components from the given image region using the stack data structure.

int ConnectedComponentLabelling::connectedComponentLabellingStack(Image* CCL, unsigned int UserHeight, unsigned int UserWidth)

{

        if(UserHeight<0 || UserWidth<0 || UserHeight>CCL->Height || UserWidth>CCL->Width) //  Condition to check whether the input received is within the image dimensions.
        {
            std::cout << "Invalid height and width!" << std::endl;
            logger("Invalid height and width!");
            exit(1);
        }
        logger("Performing the connected component labelling algorithm using the stack data structure...");
    int Label=1;
    int **LabelledImage=new int*[UserHeight];   //  Creating a two-dimensional array to store the labelled image.
        for(unsigned int i=0; i<UserHeight; i++)
        {
            LabelledImage[i]=new int[UserWidth];
        }
        for(unsigned int i=0; i<UserHeight; i++)    //  Initialising the newly created two-dimensional array.
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                LabelledImage[i][j]=0;
            }
        }

        //  Performing the connected-component labelling algorithm using the stack data structure.

        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                if(CCL->Data[i][j]==0 && LabelledImage[i][j]==0)   //  Condition to check whether the certain dimension is both a black pixel and unlabelled.
                {
                    class Stack<int> RowStack;   //  Creating a stack to store the row values.
                    class Stack<int> ColumnStack;    //  Creating a stack to store the column values.
                        RowStack.push(i);
                        ColumnStack.push(j);
                        while(!RowStack.empty() && !ColumnStack.empty())    //  Condition to check whether the stack is empty or not.
                        {
                            unsigned int Row=RowStack.top();
                            unsigned int Column=ColumnStack.top();
                                RowStack.pop();
                                ColumnStack.pop();
                                if(Row>=0 && Row<UserHeight && Column>=0 && Column<UserWidth && CCL->Data[Row][Column]==0 && LabelledImage[Row][Column]==0)    //  Condition for exception handling, and to check whether the certain dimension is both a black pixel and unlabelled.
                                {
                                    LabelledImage[Row][Column]=Label;
                                    RowStack.push(Row-1);
                                    ColumnStack.push(Column);
                                    RowStack.push(Row+1);
                                    ColumnStack.push(Column);
                                    RowStack.push(Row);
                                    ColumnStack.push(Column-1);
                                    RowStack.push(Row);
                                    ColumnStack.push(Column+1);
                                }
                        }
                        Label++;
                }
            }
        }

    //  Relabelling the labelled image to be exported to the output file.

        logger("Relabelling the labelled image...");
    int *RelabelledImage=new int[Label];    //  Creating a one-dimensional array to store the relabelled image.
        for(int i=0; i<Label; i++)
        {
            RelabelledImage[i]=0;
        }
        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                if(LabelledImage[i][j]==0)  //  Condition to check whether the certain dimension is unlabelled or not.
                {
                    RelabelledImage[LabelledImage[i][j]]++;
                }
            }
        }
        int NewLabel=1;
        for(int i=1; i<Label; i++)
        {
            if(RelabelledImage[i]!=0)   //  Condition to check whether the certain pixel is a black pixel or not.
            {
                RelabelledImage[i]=NewLabel;
                NewLabel++;
            }
        }
        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                if(LabelledImage[i][j]==0)  //  Condition to check whether the certain dimension is unlabelled or not.
                {
                    LabelledImage[i][j]=RelabelledImage[LabelledImage[i][j]];   //  Relabelling the unlabelled dimension of the image with the new label.
                }
            }
        }

    //  Writing the labelled image into a separate file.

        logger("Writing the labelled image (stack) into a file...");
    std::string Time=getCurrentDateTime("Time");    //  Retrieving the current time from the system module.
    const char* TimeString=Time.c_str();
    std::string LabelledImageFileName="labelled-image_stack_";
        LabelledImageFileName+=TimeString;
        LabelledImageFileName+=".pgm";
    const char* FileName=LabelledImageFileName.c_str(); //  Storing the file name for the labelled image file in a variable.
    FILE *LabelledImageFile=fopen(FileName, "wb");   //  Opening the labelled image file for writing in a binary format.

        //  Writing the header information into the labelled image file.

        fprintf(LabelledImageFile, "%s\n", CCL->PGMType);
        fprintf(LabelledImageFile, "%d %d\n", UserWidth, UserHeight);
        fprintf(LabelledImageFile, "%d\n", CCL->MaximumGreyValue);

        //  Writing the labelled image into the defined labelled image file.

        for(unsigned int i=0; i<UserHeight; i++)
        {
            for(unsigned int j=0; j<UserWidth; j++)
            {
                fputc(LabelledImage[i][j], LabelledImageFile);  //  Writing a single character at a time into the labelled image file.
            }
        }
        fclose(LabelledImageFile);  //  Closing the labelled image file.
        logger("Labelled image written (stack) into a file successfully!");

        //  Deallocting the dynamically allocated memory for the labelled image.

        for(unsigned int i=0; i<UserHeight; i++)
        {
            delete[] LabelledImage[i];
        }
        delete[] LabelledImage;

    return Label-1;

}