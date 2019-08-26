// Names: Kelsey Nguyen & Maram Almutairi
// Project: Mips Simulator
// Date: 4-6-2017
// Class: CS312 - Prof. McKenney

//Class def for Mipsclass and all const ints required for class

#ifndef mipsClass_hpp
#define mipsClass_hpp
#endif
#include <fstream>
#include <string>
#include <stdio.h>
const int PCSTART = 96;
const int DEMASKER = 0x7C000000;
const int DEMASKER2 = 0x0000003F;
const int DEMASKERPRO = 0x7FFFFFFF;

//after demasker
const int ADDIOP = 0x00000020;
const int JOP = 0x00000008;
const int LWOP = 0x0000000C;
const int SWOP = 0x0000002C;
const int BEQOP = 0x00000010;
const int BLTZOP = 0x00000004;
const int NOOP = 0x80000000;

//after demasker2 for those that start 1 000 00
const int ADDOP = 0x00000020;
const int JROP = 0x00000008;
const int SUBOP = 0x00000022;
const int SLLOP = 0x00000000;
const int SLROP = 0x00000002;
const int MULOP = 0x00000070;
const int ANDOP = 0x00000024;
const int OROP = 0x00000025;
const int MOVZOP = 0x0000000A;
const int BREAKOP = 0x0000000D;

//for the computations themselves
const int DEMASKRS = 0x03E00000;
const int DEMASKRT = 0x001F0000;
const int DEMASKRD = 0x0000F800;
const int DEMASKSA = 0x000007C0;
const int DEMASKIM = 0x0000FFFF;
const int DEMASKJ = 0x03FFFFFF;

using namespace std;
class Mips
{
public:
    Mips();
    void loadInstructions(int at, int instruction);
    bool ValadOp(int instruction);
    string DetermineOperation(int instruction);
    void DetermineOperationCal(int instruction);
    void SetInstructionAmount(int value);
    void OutputDis(string outDisFile);
    void OutputSim(int instruction, int cycle, ofstream& simfile);
    void ComputeInstructions(string file);
    void findAfterBreak();
    void findDestinationLocation(int instruction, ofstream &outfile);
    
    
private:
    void ADD(int instruction);
    void ADDI(int instruction);
    void AND(int instruction);
    void BEQ(int instruction);
    void BLTZ(int instruction);
    void Jump(int instruction);
    void JR(int instruction);
    void LW(int instruction);
    void SW(int instruction);
    void SUB(int instruction);
    void MUL(int instruction);
    void MOVZ(int instruction);
    void OR(int instruction);
    void SLL(int instruction);
    void SLR(int instruction);
    void NOOPaction();
    
    void outputRdRSRT(int instruction, ofstream &outfile);
    void outputRdRtSa(int instruction, ofstream &outfile);
    void outputAddi(int instruction, ofstream &outfile);
    void outputJ(int instruction, ofstream &outfile);
    void outputJR(int instruction, ofstream &outfile);
    void outputBranch(int instruction, ofstream &outfile);
    void outputLoad(int instruction, ofstream &outfile);
    
    int data[50];
    int instructionAmount;
    int registers[32];
    int PC;
    int previousPC;
    int afterBreak;
    //int determ;
};

