//  Header file for the class defined for connected-component labelling.

#ifndef CONNECTEDCOMPONENTLABELLING_H
#define CONNECTEDCOMPONENTLABELLING_H
#include "Image.h"

//  Defining the class for all the connected-component labelling algorithm.

class ConnectedComponentLabelling

{

    public:

        int connectedComponentLabellingQueue(Image* CCL, unsigned int UserHeight, unsigned int UserWidth);
        int connectedComponentLabellingStack(Image* CCL, unsigned int UserHeight, unsigned int UserWidth);

};

#endif