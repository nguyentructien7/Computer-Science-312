// Names: Kelsey Nguyen & Maram Almutairi
// Project: Mips Simulator
// Date: 4-6-2017
// Class: CS312 - Prof. McKenney

//Program takes Mip binary instructions then processes them and sends results to .txt file

#include <iostream>
#include <fcntl.h>
#include <iomanip>
#include <stdio.h>
#include "mipsClass.hpp"
using namespace std;

int main()
{
    string filename;
    cout << "Enter the name of the binary file holding the instructions:";
    cin >> filename;
     
    int j = 0;
    
    char buffer[4];
    int i;
    char * iPtr;
    iPtr = (char*)(void*) &i;
    
    FILE * FD;
    
    
    if(filename == "test1")
    {
        
        FD = fopen("test1.bin", "rb+");
    }
    else if(filename =="test2")
    {
        ;
        FD = fopen("test2.bin", "rb+");
    }
    else if(filename == "test3")
    {
        
        FD = fopen("test3.bin", "rb+");
    }
    else
    {
        cout << endl << "File not Found next time Please enter test#. # being (1,2, or3)\n\n";
        system("pause");
        exit(0);
    }
    
    Mips instruction;
    
    int amt = 4;
    while( amt != 0 )
    {
        amt = fread(buffer, 1, 4,FD);
        if( amt == 4)
        {
            iPtr[0] = buffer[3];
            iPtr[1] = buffer[2];
            iPtr[2] = buffer[1];
            iPtr[3] = buffer[0];
            instruction.loadInstructions(j,i);
            j++;
        }
    }
    instruction.SetInstructionAmount(j);
    instruction.OutputDis(filename);
    instruction.findAfterBreak();
    
    instruction.ComputeInstructions(filename);
    system("pause");
}
