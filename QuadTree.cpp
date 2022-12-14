#include<iostream>
#include "QuadTree.h"
#include "Logger.h"

//  Function to initialise the quad-tree data structure.

QuadTree* InitialiseQuadTree()

{

        logger("Initialising the quad-tree data structure...");
    QuadTree* Node=new QuadTree;
        Node->CheckLeaf=false;
        Node->PixelValue=0.0;
        Node->MinimumRows=0;
        Node->MaximumRows=0;
        Node->MinimumColumns=0;
        Node->MaximumColumns=0;
        Node->Deviation=0;
        Node->NorthWest=nullptr;
        Node->NorthEast=nullptr;
        Node->SouthWest=nullptr;
        Node->SouthEast=nullptr;

    return Node;

}

//  Function to add the defined values into the quad-tree data structure.

void addValues(QuadTree* Node, int *Data, int NumberOfRows, int NumberOfColumns)

{

        logger("Adding values to the quad-tree data structure...");
        Node->Data=Data;
        Node->PixelRows=NumberOfRows;
        Node->PixelColumns=NumberOfColumns;
        Node->MinimumRows=0;
        Node->MaximumRows=NumberOfRows-1;
        Node->MinimumColumns=0;
        Node->MaximumColumns=NumberOfColumns-1;

}

//  Function to split the quad-tree data structure into its four quadrants with corresponding pixel values.

void splitQuadTree(QuadTree* Node)

{
    
        logger("Splitting the quad-tree data structure into its quadrants...");
    int MinimumQuadTreeRows=Node->MinimumRows;
    int MaximumQuadTreeRows=Node->MaximumRows;
    int MinimumQuadTreeColumns=Node->MinimumColumns;
    int MaximumQuadTreeColumns=Node->MaximumColumns;
    bool NotSouth=(MinimumQuadTreeRows==MaximumQuadTreeRows);   //  Variable to check whether the node is in the southern-most region of the image or not.
    bool NotEast=(MinimumQuadTreeColumns==MaximumQuadTreeColumns);  //  Variable to check whether the node is in the eastern-most region of the image or not.
    
        //  Initialising the north-west quadrant of the quad-tree data structure.
        
        Node->NorthWest=InitialiseQuadTree();
        Node->NorthWest->Data=Node->Data;
        Node->NorthWest->PixelRows=Node->PixelRows;
        Node->NorthWest->PixelColumns=Node->PixelColumns;
        Node->NorthWest->MinimumRows=MinimumQuadTreeRows;
        Node->NorthWest->MaximumRows=(MaximumQuadTreeRows+MinimumQuadTreeRows)/2;
        Node->NorthWest->MinimumColumns=MinimumQuadTreeColumns;
        Node->NorthWest->MaximumColumns=(MaximumQuadTreeColumns+MinimumQuadTreeColumns)/2;
        
        //  If the node is not in the eastern-most region of the image, then the north-west quadrant is initialised.

        if(!NotEast)    //  Condition to check whether the node is in the eastern-most region of the image or not.
        {
            Node->NorthEast=InitialiseQuadTree();
            Node->NorthEast->Data=Node->Data;
            Node->NorthEast->PixelRows=Node->PixelRows;
            Node->NorthEast->PixelColumns=Node->PixelColumns;
            Node->NorthEast->MinimumRows=MinimumQuadTreeRows;
            Node->NorthEast->MaximumRows=(MaximumQuadTreeRows+MinimumQuadTreeRows)/2;
            Node->NorthEast->MinimumColumns=(MaximumQuadTreeColumns+MinimumQuadTreeColumns)/2+1;
            Node->NorthEast->MaximumColumns=MaximumQuadTreeColumns;
        }

        //  If the node is not in the southern-most region of the image, then the south-west quadrant is initialised.
        
        if(!NotSouth)
        {
            Node->SouthWest=InitialiseQuadTree();
            Node->SouthWest->Data=Node->Data;
            Node->SouthWest->PixelRows=Node->PixelRows;
            Node->SouthWest->PixelColumns=Node->PixelColumns;
            Node->SouthWest->MinimumRows=(MaximumQuadTreeRows+MinimumQuadTreeRows)/2+1;
            Node->SouthWest->MaximumRows=MaximumQuadTreeRows;
            Node->SouthWest->MinimumColumns=MinimumQuadTreeColumns;
            Node->SouthWest->MaximumColumns=(MaximumQuadTreeColumns+MinimumQuadTreeColumns)/2;
        }

        //  If the node is not in both the eastern-most and southern-most region of the image, then the south-east quadrant is initialised.
        
        if(!NotEast && !NotSouth)
        {
            Node->SouthEast=InitialiseQuadTree();
            Node->SouthEast->Data=Node->Data;
            Node->SouthEast->PixelRows=Node->PixelRows;
            Node->SouthEast->PixelColumns=Node->PixelColumns;
            Node->SouthEast->MinimumRows=(MaximumQuadTreeRows+MinimumQuadTreeRows)/2+1;
            Node->SouthEast->MaximumRows=MaximumQuadTreeRows;
            Node->SouthEast->MinimumColumns=(MaximumQuadTreeColumns+MinimumQuadTreeColumns)/2+1;
            Node->SouthEast->MaximumColumns=MaximumQuadTreeColumns;
        }

}

//  Function to calculate the average pixel value of a quadrant in the quad-tree data structure.

float averagePixelValue(QuadTree* Node)

{

        logger("Calculating the average pixel value of a quadrant in the quad-tree data structure...");
    float Total=0.0;
    float AveragePixelValue=0.0;
    int MinimumRows=Node->MinimumRows;
    int MaximumRows=Node->MaximumRows;
    int MaximumColumns=Node->MaximumColumns;
    int MinimumColumns=Node->MinimumColumns;
    int TotalCells=(MaximumRows-MinimumRows+1)*(MaximumColumns-MinimumColumns+1);
    int PixelColumns=Node->PixelColumns;
        for(int i=MinimumRows; i<=MaximumRows; i++)
        {
            for(int j=MinimumColumns; j<=MaximumColumns; j++)
            {
                Total+=Node->Data[i*PixelColumns+j];    //  Calculating the total pixel value of a specific quadrant.
            }
        }
    AveragePixelValue=float(Total)/float(TotalCells);   //  Calculating the average pixel value of a specific quadrant.

    return AveragePixelValue;

}

//  Function to calculate the pixel variance of a quadrant in the quad-tree data structure.

float pixelVariance(QuadTree* Node)

{

        logger("Calculating the pixel variance of a quadrant in the quad-tree data structure...");
    float AveragePixelValue=averagePixelValue(Node);
    float TotalDeviation=0.0;
    float PixelVariance=0.0;
    int MinimumRows=Node->MinimumRows;
    int MaximumRows=Node->MaximumRows;
    int MaximumColumns=Node->MaximumColumns;
    int MinimumColumns=Node->MinimumColumns;
    int TotalCells=(MaximumRows-MinimumRows+1)*(MaximumColumns-MinimumColumns+1);
    int PixelColumns=Node->PixelColumns;
        for(int i=MinimumRows; i<=MaximumRows; i++)
        {
            for(int j=MinimumColumns; j<=MaximumColumns; j++)
            {
                TotalDeviation+=(AveragePixelValue-Node->Data[i*PixelColumns+j])*(AveragePixelValue-Node->Data[i*PixelColumns+j]);  //  Calculating the total deviation of the pixels in a specific quadrant.
            }
        }
        PixelVariance=TotalDeviation/TotalCells;    //  Calculating the pixel variance of a specific quadrant.

    return PixelVariance;

}

//  Function to build the quad-tree data structure for storing the image.

void buildQuadTree(QuadTree* Start, int MaximumVariance)

{

        logger("Building the quad-tree data structure to store the image into...");
        if(Start==nullptr)  //  Base condition.
        {
            return;
        }
    float PixelVariance=pixelVariance(Start);
        if(PixelVariance>MaximumVariance)   //  Condition to check whether the pixel variance of a specific quadrant is greater than the maximum variance defined.
        {
            splitQuadTree(Start);   //  Function to split the specific quadrant into its four sub-quadrants.
            buildQuadTree(Start->NorthWest, MaximumVariance);
            buildQuadTree(Start->NorthEast, MaximumVariance);
            buildQuadTree(Start->SouthWest, MaximumVariance);
            buildQuadTree(Start->SouthEast, MaximumVariance);
        }
        else
        {
            float AveragePixelValue=averagePixelValue(Start);
            Start->PixelValue=AveragePixelValue;    //  Assigning the average pixel value of a specific quadrant to the pixel value of the node.
            Start->CheckLeaf=true;
        }

}

//  Function to convert the quad-tree data structure into a one-dimensional array (unpacking).

int* unpackQuadTree(QuadTree* Start, int TotalRows, int TotalColumns)

{

        logger("Unpacking the quad-tree data structure to obtain the image...");
        if(Start==nullptr)  //  Base condition.
        {
            return nullptr;
        }
    int* Image=new int[TotalRows*TotalColumns]; //  Creating a one-dimensional array to store the image data into.
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            int MinimumRows=Start->MinimumRows;
            int MaximumRows=Start->MaximumRows;
            int MaximumColumns=Start->MaximumColumns;
            int MinimumColumns=Start->MinimumColumns;
            int PixelColumns=Start->PixelColumns;
            int PixelValue=Start->PixelValue;
                for(int i=MinimumRows; i<=MaximumRows; i++)
                {
                    for(int j=MinimumColumns; j<=MaximumColumns; j++)
                    {
                        Image[i*PixelColumns+j]=PixelValue;    //  Assigning the pixel value of the specific node to the corresponding index in the one-dimensional array.
                    }
                }
        }
        else
        {
            unpackQuadTree(Start->NorthWest, TotalRows, TotalColumns);
            unpackQuadTree(Start->NorthEast, TotalRows, TotalColumns);
            unpackQuadTree(Start->SouthWest, TotalRows, TotalColumns);
            unpackQuadTree(Start->SouthEast, TotalRows, TotalColumns);
        }

    return Image;

}

#define COUNT 10

//  Function to export the quad-tree data structure containing the image into a separate file.

void exportQuadTreeUtility(QuadTree* Start, int Space)

{  

    std::ofstream QuadTreeFile;
    QuadTreeFile.open("quad_tree_image.txt", std::ios::app);    //  Opening the file to store the quad-tree data structure containing the image into.
        if(Start==nullptr)  //  Base condition.
        {
            QuadTreeFile.close();   //  Closing the opened file.
            return;
        }
        Space+=COUNT;   //  Indenting of the quad-tree data structure.
        exportQuadTreeUtility(Start->NorthEast, Space);
        QuadTreeFile << std::endl;
        for(int i=COUNT; i<Space; i++)
        {
            QuadTreeFile << " ";
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            QuadTreeFile << Start->PixelValue << std::endl;
        }
        else
        {
            QuadTreeFile << " --> " << std::endl;
        }
        exportQuadTreeUtility(Start->NorthWest, Space);
        exportQuadTreeUtility(Start->SouthWest, Space);
        exportQuadTreeUtility(Start->SouthEast, Space);

}

//  Wrapper function to export the quad-tree data structure containing the image into a separate file.

void exportQuadTree(QuadTree* Start)

{  

        logger("Exporting the quad-tree data structure containing the image into a separate file...");
        exportQuadTreeUtility(Start, 0); 

}

//  Function to count the number of nodes in the quad-tree data structure.

int countQuadTreeNodes(QuadTree* Start)

{

        logger("Counting the number of nodes in the quad-tree data structure...");
        if(Start==nullptr)  //  Base condition.
        {
            return 0;
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            return 1;
        }
        else
        {
            return countQuadTreeNodes(Start->NorthWest)+countQuadTreeNodes(Start->NorthEast)+countQuadTreeNodes(Start->SouthWest)+countQuadTreeNodes(Start->SouthEast);
        }

}

//  Function to calculate the number of pixels of the image stored in the quad-tree data structure.

int numberOfPixels(QuadTree* Start)

{

        logger("Counting the number of pixels of the image stored in the quad-tree data structure...");
        if(Start==nullptr)  //  Base condition.
        {
            return 0;
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            int Size=(Start->MaximumRows-Start->MinimumRows+1)*(Start->MaximumColumns-Start->MinimumColumns+1); //  Calculating the size of the quad-tree data structure.
            return Size;
        }
        else
        {
            return numberOfPixels(Start->NorthWest)+numberOfPixels(Start->NorthEast)+numberOfPixels(Start->SouthWest)+numberOfPixels(Start->SouthEast);
        }

}

void convertToNegative(QuadTree* Start)

{

        logger("Converting the image to its negative...");
        if(Start==nullptr)  //  Base condition.
        {
            return;
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            if(Start->PixelValue==0)    //  Condition to check whether the pixel value of the specific node is zero or not.
            {
                Start->PixelValue=255;
            }
            else
            {
                Start->PixelValue=0;
            }
        }
        else
        {
            convertToNegative(Start->NorthWest);
            convertToNegative(Start->NorthEast);
            convertToNegative(Start->SouthWest);
            convertToNegative(Start->SouthEast);
        }

}

//  Function to export the pre-order traversal of the quad-tree data structure into a separate file.

void printPreOrder(QuadTree* Start)

{

        logger("Exporting the pre-order traversal of the quad-tree data structure into a separate file...");
    std::ofstream QuadTreeFile;
        QuadTreeFile.open("quad_tree_preorder.txt", std::ios::app); //  Opening the file to store the pre-order traversal of the quad-tree data structure into.
        if(Start==nullptr)  //  Base condition.
        {
            return;
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            QuadTreeFile << Start->PixelValue << " ";
        }
        else
        {
            QuadTreeFile << " --> ";
            printPreOrder(Start->NorthWest);
            printPreOrder(Start->NorthEast);
            printPreOrder(Start->SouthWest);
            printPreOrder(Start->SouthEast);
        }

}

//  Function to export the in-order traversal of the quad-tree data structure into a separate file.

void printInOrder(QuadTree* Start)

{

        logger("Exporting the in-order traversal of the quad-tree data structure into a separate file...");
    std::ofstream QuadTreeFile;
        QuadTreeFile.open("quad_tree_inorder.txt", std::ios::app);  //  Opening the file to store the in-order traversal of the quad-tree data structure containing the image into.
        if(Start==nullptr)  //  Base condition.
        {
            return;
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            QuadTreeFile << Start->PixelValue << " ";
        }
        else
        {
            printInOrder(Start->NorthWest);
            printInOrder(Start->NorthEast);
            QuadTreeFile << " --> ";
            printInOrder(Start->SouthWest);
            printInOrder(Start->SouthEast);
        }

}

//  Function to export the post-order traversal of the quad-tree data structure into a separate file.

void printPostOrder(QuadTree* Start)

{

        logger("Exporting the post-order traversal of the quad-tree data structure into a separate file...");
    std::ofstream QuadTreeFile;
        QuadTreeFile.open("quad_tree_postorder.txt", std::ios::app);    //  Opening the file to store the post-order traversal of the quad-tree data structure containing the image into.
        if(Start==nullptr)  //  Base condition.
        {
            return;
        }
        if(Start->CheckLeaf)    //  Condition to check whether the specific node is a leaf node or not.
        {
            QuadTreeFile << Start->PixelValue << " ";
        }
        else
        {
            printPostOrder(Start->NorthWest);
            printPostOrder(Start->NorthEast);
            printPostOrder(Start->SouthWest);
            printPostOrder(Start->SouthEast);
            QuadTreeFile << " --> ";
        }

}