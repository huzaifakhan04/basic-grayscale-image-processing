#pragma warning(disable:4996)
#ifndef LOGGER_H
#define LOGGER_H
#include<ctime>
#include<fstream>

//  Function to retrieve and return the current date and/or time from the system module.

inline std::string getCurrentDateTime(std::string Input)

{

    time_t CurrentTime=time(0);
    struct tm Time;
    char Buffer[80];
        Time=*localtime(&CurrentTime);
        if(Input=="Now")
        {
            strftime(Buffer, sizeof(Buffer), "%Y-%m-%d %X", &Time);
        }
        else if(Input=="Date")
        {
            strftime(Buffer, sizeof(Buffer), "%Y%m%d%H%M", &Time);
        }
        else if(Input=="Time")
        {
            strftime(Buffer, sizeof(Buffer), "%H%M", &Time);
        }

    return std::string(Buffer);

};

//  Function to log all the events in the programme, and store in a log file.

inline void logger(std::string LogMessage)

{

    std::string FilePath="log_"+getCurrentDateTime("Date")+".txt";
    std::string CurrentTime=getCurrentDateTime("Now");
    std::ofstream Output(FilePath.c_str(), std::ios_base::out | std::ios_base::app);
        Output << CurrentTime << "\t" << LogMessage << std::endl;
        Output.close();

}

#endif