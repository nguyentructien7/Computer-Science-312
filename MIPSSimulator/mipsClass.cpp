// Names: Kelsey Nguyen & Maram Almutairi
// Project: Mips Simulator
// Date: 4-6-2017
// Class: CS312 - Prof. McKenney

//function def

#include "mipsClass.hpp"
#include <iostream>

using namespace std;
Mips::Mips()
{
    for (int i = 0; i <20; i++)
        data[i] = 0;
    instructionAmount = 0;
    for (int k = 0; k <32; k++)
    {
        registers[k] = 0;
    }
    PC = PCSTART;
    previousPC = PCSTART;
    afterBreak = 0;
}

bool Mips::ValadOp(int instruction)
{
    if (data[instruction] < 0)
        return true;
    else
        return false;
}

string Mips::DetermineOperation(int instruction)
{
    int opcode;
    opcode = (data[instruction] & DEMASKER);
    
    if (data[instruction] == NOOP)
    {
        return("NOP");
        //return noop instruction
    }
    
    opcode = opcode >> 24;
    
    if (ValadOp(instruction))
    {
        if (opcode == ADDIOP)
        {
            return("ADDI");
        }
        else if (opcode == JOP)
        {
            return("J");
        }
        else if (opcode == LWOP)
        {
            return("LW");
        }
        else if (opcode == SWOP)
        {
            return("SW");
        }
        else if (opcode == BEQOP)
        {
            return("BEQ");
        }
        else if (opcode == MULOP)
        {
            return("MUL");
        }
        else if (opcode == BLTZOP)
        {
            return("BLTZ");
        }
        else
        {
            opcode = (data[instruction] & DEMASKER2);
            if (opcode == ADDOP)
            {
                return("ADD");
            }
            else if (opcode == JROP)
            {
                return("JR");
            }
            else if (opcode == SUBOP)
            {
                return("SUB");
            }
            else if (opcode == SLLOP)
            {
                return("SLL");
            }
            else if (opcode == SLROP)
            {
                return("SRL");
            }
            else if (opcode == ANDOP)
            {
                return("AND");
            }
            else if (opcode == OROP)
            {
                return("OR");
            }
            else if (opcode == MOVZOP)
            {
                return("MOVZ");
            }
            else if (opcode == BREAKOP)
            {
                return("BREAK");
            }
        }
    }
    else
    {
        return("Invalid Instruction");
    }
    return (0);
}

void Mips::loadInstructions(int at, int instruction)
{
    data[at] = instruction;
}

void Mips::SetInstructionAmount(int value)
{
    instructionAmount = value;
}

void Mips::OutputDis(string outDisFile)
{
    outDisFile.append("_dis.txt");
    ofstream disfile;
    disfile.open(outDisFile);
    
    int currentPC = 96;
    int i = (currentPC - 96) / 4;
    do
    {
        int binary = (data[i]);
        for (int k = 0; k < 32; k++)
        {
            if (k == 0)
            {
                if (ValadOp(i))
                {
                    disfile << 1;
                    cout << 1;
                    binary = ((binary & DEMASKERPRO) << 1);
                }
                else
                {
                    disfile << 0;
                    cout << 0;
                    binary = ((binary & DEMASKERPRO) << 1);
                }
            }
            else
            {
                if ((binary >> 31) == 0xffffffff)
                {
                    disfile << 1;
                    cout << 1;
                }
                else
                {
                    disfile << (binary >> 31);
                    cout << (binary >> 31);
                }
                binary = (binary << 1);
            }
            if (k>29)
            {
            }
            else if (k % 5 == 0)
            {
                disfile << ' ';
                cout << ' ';
            }
        }
        disfile << "\t" << currentPC << "\t" << DetermineOperation(i);
        cout << "\t" << currentPC << "\t" << DetermineOperation(i);
        findDestinationLocation(i, disfile);
        disfile << endl;
        cout << endl;
        
        currentPC = currentPC + 4;
        i = (currentPC - 96) / 4;
    } while (DetermineOperation((currentPC - 96 - 4) / 4) != "BREAK");
    
    for (i; i < instructionAmount; i++)
    {
        int binary = (data[i]);
        for (int k = 0; k < 32; k++)
        {
            if ((binary >> 31) == 0xffffffff)
            {
                disfile << 1;
                cout << 1;
            }
            else
            {
                disfile << (binary >> 31);
                cout << (binary >> 31);
            }
            binary = (binary << 1);
        }
        disfile << "\t" << currentPC << "\t" << dec << (data[i]) << endl;
        cout << "\t" << currentPC << "\t" << dec << (data[i]) << endl;
        currentPC = currentPC + 4;
    }
    disfile.close();
}

void Mips::DetermineOperationCal(int instruction)
{
    int opcode;
    opcode = (data[instruction] & DEMASKER);
    
    if ((data[instruction] == NOOP) || !ValadOp(instruction))
    {
        NOOPaction();
        return;
        //return noop instruction
    }
    
    opcode = opcode >> 24;
    
    if (ValadOp(instruction))
    {
        if (opcode == ADDIOP)
        {
            ADDI(instruction);
        }
        else if (opcode == JOP)
        {
            Jump(instruction);
        }
        else if (opcode == LWOP)
        {
            LW(instruction);
        }
        else if (opcode == SWOP)
        {
            SW(instruction);
        }
        else if (opcode == BEQOP)
        {
            BEQ(instruction);
        }
        else if (opcode == MULOP)
        {
            MUL(instruction);
        }
        else if (opcode == BLTZOP)
        {
            BLTZ(instruction);
        }
        else
        {
            opcode = (data[instruction] & DEMASKER2);
            if (opcode == ADDOP)
            {
                ADD(instruction);
            }
            else if (opcode == JROP)
            {
                JR(instruction);
            }
            else if (opcode == SUBOP)
            {
                SUB(instruction);
            }
            else if (opcode == SLLOP)
            {
                SLL(instruction);
            }
            else if (opcode == SLROP)
            {
                SLR(instruction);
            }
            else if (opcode == ANDOP)
            {
                AND(instruction);
            }
            else if (opcode == OROP)
            {
                OR(instruction);
            }
            else if (opcode == MOVZOP)
            {
                MOVZ(instruction);
            }
            else if (opcode == BREAKOP)
            {
                NOOPaction();
            }
        }
    }
}

void Mips::ComputeInstructions(string file)
{
    file.append("_sim.txt");
    ofstream simfile;
    simfile.open(file);
    int i = (PC - 96) / 4;
    int cycleNumber = 1;
    do
    {
        if (ValadOp(i))
        {
            DetermineOperationCal(i);
            OutputSim(i, cycleNumber, simfile);
            cycleNumber++;
        }
        else
        {
            PC = PC + 4;
        }
        i = (PC - 96) / 4;
    } while (DetermineOperation((PC - 96 - 4) / 4) != "BREAK");
    simfile.close();
}

void Mips::OutputSim(int instruction, int cycle, ofstream& simfile)
{
    
    int value = afterBreak;
    int valueOfdataPC;
    simfile << "====================" << endl;
    simfile << "cycle:" << cycle << "\t" << previousPC << "\t" << DetermineOperation(instruction);
    cout << "====================" << endl;
    cout << "cycle:" << cycle << "\t" << previousPC << "\t" << DetermineOperation(instruction);
    findDestinationLocation(instruction, simfile);
    
    simfile << endl << endl << "registers:" << endl << "r00:";
    cout << endl << endl << "registers:" << endl << "r00:";
    for (int k = 0; k <8; k++)
    {
        simfile << "\t" << registers[k];
        cout << "\t" << registers[k];
    }
    simfile << endl << "r08:";
    cout << endl << "r08:";
    for (int k = 8; k<16; k++)
    {
        simfile << "\t" << registers[k];
        cout << "\t" << registers[k];
    }
    simfile << endl << "r16:";
    cout << endl << "r16:";
    for (int k = 16; k<24; k++)
    {
        simfile << "\t" << registers[k];
        cout << "\t" << registers[k];
    }
    simfile << endl << "r24:";
    cout << endl << "r24:";
    for (int k = 24; k<32; k++)
    {
        simfile << "\t" << registers[k];
        cout << "\t" << registers[k];
    }
    simfile << endl << endl << "data:" << endl;
    cout << endl << endl << "data:" << endl;
    
    for (value; value < instructionAmount; (value++))
    {
        valueOfdataPC = value * 4 + 96;
        simfile << valueOfdataPC << ':';
        cout << valueOfdataPC << ':';
        
        int q = 0;
        int temp = value;
        
        while ((q < 8) && ((q + value) < instructionAmount))
        {
            simfile << "\t" << data[value + q];
            cout << "\t" << data[value + q];
            q++;
        }
        simfile << endl;
        cout << endl;
        value = value + 7;
    }
    simfile << endl;
    cout << endl;
}

//finds where the break point will occur in the instruction set
//this aids in outputing items to the screen that are in "memory"
void Mips::findAfterBreak()
{
    int fakePc = 96;
    while (DetermineOperation((fakePc - 96) / 4) != "BREAK")
    {
        fakePc = fakePc + 4;
    }
    afterBreak = (fakePc - 96 + 4) / 4;
}

void Mips::findDestinationLocation(int instruction, ofstream& outfile)
{
    string word = DetermineOperation(instruction);
    if ((word == "LW") || (word == "SW"))
        outputLoad(instruction, outfile);
    else if ((word == "SLL") || (word == "SRL"))
        outputRdRtSa(instruction, outfile);
    else if ((word == "BEQ") || (word == "BLTZ"))
        outputBranch(instruction, outfile);
    else if (word == "ADDI")
        outputAddi(instruction, outfile);
    else if (word == "J")
        outputJ(instruction, outfile);
    else if (word == "JR")
        outputJR(instruction, outfile);
    else if ((word == "MOVZ") || (word == "ADD") || (word == "MUL") || (word == "SUB") || (word == "AND") || (word == "OR"))
        outputRdRSRT(instruction, outfile);
}

//to show values in the instructions
void Mips::outputRdRSRT(int instruction, ofstream& outfile)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    cout << "\tR" << rd << ", R" << rs << ", R" << rt;
    outfile << "\tR" << rd << ", R" << rs << ", R" << rt;
}

void Mips::outputRdRtSa(int instruction, ofstream &outfile)
{
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    int sa = (data[instruction] & DEMASKSA) >> 6;
    cout << "\tR" << rd << ", R" << rt << ", #" << sa;
    outfile << "\tR" << rd << ", R" << rt << ", #" << sa;
}

void Mips::outputAddi(int instruction, ofstream &outfile)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int neg = (data[instruction] & 0x00008000);
    int Im = (data[instruction] & DEMASKIM);
    if (neg == 0x00008000)
        Im = Im | 0xFFFF0000;
    cout << "\tR" << rt << ", R" << rs << ", #" << Im;
    outfile << "\tR" << rt << ", R" << rs << ", #" << Im;
}

void Mips::outputJ(int instruction, ofstream &outfile)
{
    int value = (data[instruction] & DEMASKJ) << 2;
    cout << "\t#" << value;
    outfile << "\t#" << value;
}

void Mips::outputJR(int instruction, ofstream &outfile)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    cout << "\tR" << rs;
    outfile << "\tR" << rs;
}

void Mips::outputBranch(int instruction, ofstream &outfile)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int ofset = (data[instruction] & DEMASKIM) << 2;
    if (DetermineOperation(instruction) == "BEQ")
    {
        cout << "\tR" << rs << ", R" << rt << ", #" << ofset;
        outfile << "\tR" << rs << ", R" << rt << ", #" << ofset;
    }
    else
    {
        cout << "\tR" << rs << ", #" << ofset;
        outfile << "\tR" << rs << ", #" << ofset;
    }
}

void Mips::outputLoad(int instruction, ofstream &outfile)
{
    int base = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int ofset = (data[instruction] & DEMASKIM);
    cout << "\tR" << rt << ", " << ofset << "(R" << base << ')';
    outfile << "\tR" << rt << ", " << ofset << "(R" << base << ')';
}



//start of calulatory stuff
void Mips::ADD(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    registers[rd] = registers[rs] + registers[rt];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::ADDI(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int neg = (data[instruction] & 0x00008000);
    int Im = (data[instruction] & DEMASKIM);
    if (neg == 0x00008000)
        Im = Im | 0xFFFF0000;
    registers[rt] = registers[rs] + Im;
    previousPC = PC;
    PC = PC + 4;
}

void Mips::AND(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    registers[rd] = registers[rs] & registers[rt];
    previousPC = PC;
    PC = PC + 4;
}

//had an issue here but after looking up code saw you didn't do delay continued
//after see that made it much easier for BEQ/BLTZ
void Mips::BEQ(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int ofset = (data[instruction] & DEMASKIM) << 2;
    previousPC = PC;
    if (registers[rs] == registers[rt])
        PC = PC + ofset;
    PC = PC + 4;
}

void Mips::BLTZ(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int ofset = (data[instruction] & DEMASKIM) << 2;
    previousPC = PC;
    if (registers[rs] < 0)
        PC = PC + ofset;
    PC = PC + 4;
}

void Mips::Jump(int instruction)
{
    int value = (data[instruction] & DEMASKJ) << 2;
    previousPC = PC;
    PC = value;
}

void Mips::JR(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    previousPC = PC;
    PC = registers[rs];
}

void Mips::LW(int instruction)
{
    int base = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int ofset = (data[instruction] & DEMASKIM);
    registers[rt] = data[(((ofset + registers[base]) - 96) / 4)];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::SW(int instruction)
{
    int base = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int ofset = (data[instruction] & DEMASKIM);
    data[(((ofset + registers[base]) - 96) / 4)] = registers[rt];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::SUB(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    registers[rd] = registers[rs] - registers[rt];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::MUL(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    registers[rd] = registers[rs] * registers[rt];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::MOVZ(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    if (registers[rt] == 0)
        registers[rd] = registers[rs];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::OR(int instruction)
{
    int rs = (data[instruction] & DEMASKRS) >> 21;
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    registers[rd] = registers[rs] | registers[rt];
    previousPC = PC;
    PC = PC + 4;
}

void Mips::SLL(int instruction)
{
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    int sa = (data[instruction] & DEMASKSA) >> 6;
    registers[rd] = registers[rt] << sa;
    previousPC = PC;
    PC = PC + 4;
}

void Mips::SLR(int instruction)
{
    int rt = (data[instruction] & DEMASKRT) >> 16;
    int rd = (data[instruction] & DEMASKRD) >> 11;
    int sa = (data[instruction] & DEMASKSA) >> 6;
    registers[rd] = registers[rt] >> sa;
    previousPC = PC;
    PC = PC + 4;
}

void Mips::NOOPaction()
{
    previousPC = PC;
    PC = PC + 4;
}
