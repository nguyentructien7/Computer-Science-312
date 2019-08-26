// Names: Kelsey Nguyen & Maram Almutairi
// Project: Mips Simulator
// Date: 5-5-2017
// Class: CS312 - Prof. McKenney

//Program takes Mip binary instructions then processes them and sends results to .txt file

#include <iostream>
#include <fcntl.h>
#include <iomanip>
#include <stdio.h>
#include "mipsClass.hpp"
#include "CPU.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    CPU cpu;
    //Must make sure there is an element in the preIssue stack to be able to .top() it
    if (cpu.preIssueSize() > 1)
        cout << "cpu.preIssue.top() = " << cpu.preIssueTop() << endl;
    cpu.preIssuePush(423);
    cpu.preIssuePush(423);
    cpu.preIssuePush(423);
    //cpu.preIssuePush(4);
    cout << cpu.toString() << endl;
    
    //argv[0] = MIPSSimulator;
    //argv[1] = -i;
    //argv[2] = INPUTFILENNAME;
    //argv[3] = -o;
    //argv[4] = OUTPUFILENAME;
    //          ^-- will get appended with _pipeline.txt and _dis.txt
    
  //  if (argc != 5 || strcmp(argv[1], "-i") != 0 || strcmp(argv[3], "-o") != 0)
    //    fprintf(stderr, "Usage: MIPSSimulator -i INPUTFILENAME -o OUTPUTFILENAME\n");
    
    int j = 0;
    
    char buffer[4];
    int i;
    char * iPtr;
    iPtr = (char*)(void*)&i;
    
    FILE * FD;
    FD = fopen(argv[2], "rb+");
    
    if (FD == NULL)
    {
        fprintf(stderr, "\nNo such input file.  Name should be test1.bin, test2.bin, etc.\n\n");
        system("pause");
        exit(0);
    }
    
    Mips instruction;
    
    int amt = 4;
    while (amt != 0)
    {
        amt = fread(buffer, 1, 4, FD);
        if (amt == 4)
        {
            iPtr[0] = buffer[3];
            iPtr[1] = buffer[2];
            iPtr[2] = buffer[1];
            iPtr[3] = buffer[0];
            instruction.loadInstructions(j, i);
            j++;
        }
    }
    instruction.SetInstructionAmount(j);
    string outputFileName = string(argv[4]);
    instruction.OutputDis(outputFileName);
    instruction.findAfterBreak();
    
    
    
    //TODO:  Output for cycles
    
    system("pause");
}
