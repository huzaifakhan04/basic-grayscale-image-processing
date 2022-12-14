//  Header file for the class defined for the quad-tree data structure to store the image into.

#ifndef QUADTREE_H
#define QUADTREE_H
#include <iostream>

class QuadTree

{

    public:

        bool CheckLeaf;
        float PixelValue;
        int* Data;

        //  These two variables are constant in every node of the quad-tree data structure.

        int PixelRows;
        int PixelColumns;

        //  The variables below are the attributes of the image that the nodes represent.

        int MinimumRows;
        int MaximumRows;
        int MinimumColumns;
        int MaximumColumns;

        int Deviation;  //  The deviation of the pixel values in the nodes.

        //  The variables below are used to point to the four children of the nodes.
        
        QuadTree* NorthWest;
        QuadTree* NorthEast;
        QuadTree* SouthEast;
        QuadTree* SouthWest;
    
};

//  Declaring global functions to manipulate the quad-tree data structure.

QuadTree* InitialiseQuadTree();
void addValues(QuadTree* Node, int* Data, int NumberOfRows, int NumberOfColumns);
void splitQuadTree(QuadTree* Node);
float averagePixelValue(QuadTree* Node);
float pixelVariance(QuadTree* Node);
void buildQuadTree(QuadTree* Start, int MaximumVariance);
int* unpackQuadTree(QuadTree* Start, int TotalRows, int TotalColumns);
void exportQuadTreeUtility(QuadTree* Start, int Space);
void exportQuadTree(QuadTree* Start);
int countQuadTreeNodes(QuadTree* Start);
int numberOfPixels(QuadTree* Start);
void convertToNegative(QuadTree* Start);
void printPreOrder(QuadTree* Start);
void printInOrder(QuadTree* Start);
void printPostOrder(QuadTree* Start);

#endif