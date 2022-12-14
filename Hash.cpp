#include<iostream>
#include<list>
#include "LinkedList.h"
#include "Image.h"
#include "Hash.h"
#include "Logger.h"

Hash::Hash()

{

        Size=0;

}

Hash::Hash(int Size)

{

        Table=new std::list<Image>[Size];
        this->Size=Size;

}

int Hash::hashFunction(int Key)

{

    return Key%Size;

}

void Hash::insert(Image* PGM)

{

        logger("Inserting an object into the hash table...");
    int Key=sumFourDigitFolding(PGM, PGM);
    int Index=hashFunction(Key);
        Table[Index].push_back(*PGM);

}

void Hash::display()

{

        logger("Displaying the contents of the hash table...");
        for(int i=0; i<Size; i++)
        {
            std::cout << i << " -> ";
            for(std::list<Image>::iterator it=Table[i].begin(); it!=Table[i].end(); it++)
            {
                std::cout << it->Name << " ";
            }
            std::cout<<std::endl;
        }

}

bool Hash::search(std::string FileName)

{

        logger("Searching for an image file within the hash table...");
        for(int i=0; i<Size; i++)
        {
            if(Table[i].empty())
            {
                continue;
            }
            else
            {
                for(std::list<Image>::iterator it=Table[i].begin(); it!=Table[i].end(); it++)
                {
                    if(it->Name==FileName)
                    {
                        logger("The image file was successfully found within the hash table!");
                        return true;
                    }
                }
            }
        }
        logger("The image file was not found within the hash table!");

    return false;

}

void Hash::remove(int Key)

{

        logger("Removing an object from the hash table...");
    int Index=hashFunction(Key);
        Table[Index].clear();

}