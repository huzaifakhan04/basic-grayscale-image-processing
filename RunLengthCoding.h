//  Header file for the class defined for run-length coding.

#ifndef RUNLENGTHCODING_H
#define RUNLENGTHCODING_H
#include "LinkedList.h"
#include "Image.h"

//  Defining the class for the run-length encoding/decoding algorithm.

class RunLengthCoding

{

    public:

            void runLengthEncoding(Image* RLC);
            void runLengthDecoding(std::string InputFile);
            int totalBlackPixels();

};

#endif