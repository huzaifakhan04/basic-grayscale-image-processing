#include<iostream>
#include "Image.h"
#include "ConnectedComponentLabelling.h"
#include "Logger.h"

//  Function to display the start menu of the image processing programme.

int start()

{

            std::cout << "-----" << std::endl;
            std::cout << "MENU:" << std::endl;
            std::cout << "-----" << std::endl;
            std::cout << "1. QUESTION #1" << std::endl;
            std::cout << "--------------" << std::endl;
            std::cout << "2. QUESTION #2" << std::endl;
            std::cout << "--------------" << std::endl;
            std::cout << "3. QUESTION #3" << std::endl;
            std::cout << "--------------" << std::endl;
            std::cout << std::endl;
            std::cout << "CHOICE: ";
        int Choice;
            std::cin >> Choice;
            std::cout << std::endl;

    return Choice;

}

//  Driver code.

int main(int ArgumentCount, char const* ArgumentVector[])

{

        logger("Starting the image processing programme...");
    Image* PGM=new Image(); //  Creating an object of the defined class for image processing.
    ConnectedComponentLabelling* CCL=new ConnectedComponentLabelling(); //  Creating an object of the defined class for connected-component labelling.
    const char* InputFile;
        if(ArgumentCount==2)
        {
            InputFile=ArgumentVector[1];
        }
        else
        {

			InputFile="D:\\DSA_N_Muhammad-Huzaifa-Khan_i212689_Module_1\\Images\\image009.pgm";
        }
        if(PGM->readPGMFile(PGM, InputFile))
        {
            
                logger("Displaying the start menu...");
                std::cout << "---------------------" << std::endl;
                std::cout << "ASSIGNMENT: MODULE #1" << std::endl;
                std::cout << "---------------------" << std::endl;
                std::cout << std::endl;
                std::cout << "--------------" << std::endl;
                std::cout << "IMAGE DETAILS:" << std::endl;
                std::cout << "--------------" << std::endl;
                std::cout << "Input File:\t" << InputFile << std::endl;
                PGM->saveImageDetails(PGM, InputFile);
                std::cout << std::endl;
            int UserChoice=start();
            unsigned int UserHeight;
            unsigned int UserWidth;
                switch(UserChoice)
                {
                    case 1:
                            std::cout << "------------" << std::endl;
                            std::cout << "QUESTION #1:" << std::endl;
                            std::cout << "------------" << std::endl;
                            std::cout << "- Mean Pixel Value:\t" << PGM->meanPixelValue() << std::endl;
                            std::cout << "- Number of Black Pixels:\t" << PGM->numberOfBlackPixels() << std::endl;
                            std::cout << "- Number of White Pixels:\t" << PGM->numberOfWhitePixels() << std::endl;
                            std::cout << "- Average Number of Black Pixels in Each Row:\t" << PGM->averageBlackPixelsInRow() << std::endl;
                            PGM->convertToNegative();
                            std::cout << "- Image converted to negative successfully!" << std::endl;
                            break;
                    case 2:
                                std::cout << "------------" << std::endl;
                                std::cout << "QUESTION #2:" << std::endl;
                                std::cout << "------------" << std::endl;
                                std::cout << std::endl;
                                std::cout << "HEIGHT: ";
                                std::cin >> UserHeight;
                                std::cout << std::endl;
                                std::cout << "WIDTH: ";
                                std::cin >> UserWidth;
                                std::cout << std::endl;
                                std::cout << "- Connected Components Extracted (Queue):\t" << CCL->connectedComponentLabellingQueue(PGM, UserHeight, UserWidth) << std::endl;
                                break;
                    case 3:
                                std::cout << "------------" << std::endl;
                                std::cout << "QUESTION #3:" << std::endl;
                                std::cout << "------------" << std::endl;
                                std::cout << std::endl;
                                std::cout << "HEIGHT: ";
                                std::cin >> UserHeight;
                                std::cout << std::endl;
                                std::cout << "WIDTH: ";
                                std::cin >> UserWidth;
                                std::cout << std::endl;
                                std::cout << "- Connected Components Extracted (Stack):\t" << CCL->connectedComponentLabellingStack(PGM, UserHeight, UserWidth) << std::endl;
                                break;
                    default:
                            std::cout << "INVALID CHOICE!" << std::endl;
                            logger("Invalid choice!");
                            logger("Ending the image processing programme...");
                            exit(EXIT_FAILURE); //  Unsuccessful execution of the programme.
                            break;
                }
        }
        else
        {
            std::cout << "Unable to read the input file!" << std::endl;
            logger("Unable to read the input file!");
        }
        logger("Ending the image processing programme...");
 
    exit(EXIT_SUCCESS); //  Successful execution of the programme.
    
}