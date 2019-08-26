#include <stack>
#include <queue>
#include <array>
#include <vector>
#include <iostream>
#include <sstream>
#include <bitset>

#include "CPU.hpp"
#include "mipsClass.hpp"

//STL stack operations:
//  s.push(100);
//  Get the value of the top of the stack before popping it:
//  (the stack must not be empty or there will be a runtime exception)
//  int n = s.top();
//  s.pop();
//  int size = s.size();
//  bool empty = s.empty();
//STL queue operations:
//  q.push(100);
//  Get the value of the front of the queue before popping it:
//  (the queue must not be empty or there will be a runtime exception)
//  int n = q.front();
//  q.pop();
//  bool empty = q.empty();

string CPU::toString() const {
    Mips instruction;
    stringstream ss;
    
    //Pre-Issue Buffer
    stack<int> preIssueCopy = preIssue;
    ss << "Pre-Issue Buffer:" << endl;
    int instructions[4];
    int size = preIssue.size();
    int i = 0;
    for (int i = 0; i < size; i++) {
        instructions[size - 1 - i] = preIssueCopy.top();
        preIssueCopy.pop();
    }
    for (i = 0; i < size; i++)
        ss << "\tEntry " << i << ":\t" << "[" << instruction.DetermineOperation(instructions[i]) <<
        "]" << endl;
    for (; i < 4; i++)
        ss << "\tEntry " << i << ":" << endl;
    
    //Pre-ALU Queue:
    queue<int> preALUCopy = preALU;
    ss << "Pre-ALU Queue:" << endl;
    for (i = 0; i < 2; i++)
        if (!preALUCopy.empty()) {
            int instr = preALUCopy.front();
            ss << "\tEntry " << i << ":\t" << "[" << instruction.DetermineOperation(instr) << "]" <<
            endl;
        }
        else
            ss << "\tEntry " << i << ":" << endl;
    
    //Post_ALU Queue:
    ss << "Post_ALU Queue:" << endl;
    if (!postALU.empty()) {
        int instr = postALU.front();
        ss << "\tEntry 0:\t" << "[" << instruction.DetermineOperation(instr) << "]" << endl;
    }
    else
        ss << "\tEntry 0:" << endl;
    
    //Pre_MEM Queue:
    queue<int> preMemCopy = preMem;
    ss << "Pre-MEM Queue:" << endl;
    for (i = 0; i < 2; i++)
        if (!preMemCopy.empty()) {
            int instr = preMemCopy.front();
            ss << "\tEntry " << i << ":\t" << "[" << instruction.DetermineOperation(instr) << "]" << endl;
        }
        else
            ss << "\tEntry " << i << ":" << endl;
    
    //Post_MEM Queue:
    ss << "Post_MEM Queue:" << endl;
    if (!postMem.empty()) {
        int instr = postMem.front();
        ss << "\tEntry 0:\t" << "[" << instruction.DetermineOperation(instr) << "]" << endl;
    }
    else
        ss << "\tEntry 0:" << endl << endl;
    
    //Registers
    ss << "Registers" << endl << "R00:\t";
    for (i = 0; i < 8; i++)
        ss << registers[i] << "\t";
    ss << endl << "R08:\t";
    for (i = 8; i < 16; i++)
        ss << registers[i] << "\t";
    ss << endl << "R16:\t";
    for (i = 16; i < 24; i++)
        ss << registers[i] << "\t";
    ss << endl << "R24:\t";
    for (i = 24; i < 32; i++)
        ss << registers[i] << "\t";
    ss << endl << endl;
    
    //Cache
    ss << "Cache" << endl;
    i = 0;
    for (int set = 0; set < 4; set++) {
        ss << "Set " << set << ": LRU=" << cacheLRUbit[i] << endl;
        for (int line = 0; line < 2; line++) {
            bitset<32> word0(cache[i * 2]);
            bitset<32> word1(cache[i * 2 + 1]);
            ss << "\tEntry " << line << ":[(" << cacheValidBit[i] << "," << cacheDirtyBit[i] <<
            "," << cacheTagBit[i] << ")<" << word0 << "," << word1 << ">]" << endl;
            i++;
        }
    }
    ss << endl;
    
    //Data
    ss << "Data" << endl;
    ss << "XXX:\t";
    i = 0;
    for (int n : data) {
        ss << n << "\t";
        i++;
        if (i != 0 && i % 8 == 0)
            ss << endl << "XXX:\t";
    }
    ss << endl;
    
    string s = ss.str();
    return s;
}

// Must check the bool return value: if true, push() operation was success, false otherwise
bool CPU::preIssuePush(int n) {
    if (preIssue.size() <= 3) {
        preIssue.push(n);
        return true;
    }
    else
        return false;
}
int CPU::preIssueTop() {
    return preIssue.top();
}
void CPU::preIssuePop() {
    preIssue.pop();
}
int CPU::preIssueSize() {
    return preIssue.size();
}
bool CPU::preIssueEmpty() {
    return preIssue.empty();
}

// Must check the bool return value: if true, push() operation was success, false otherwise
bool CPU::preALUPush(int n) {
    if (preALU.size() <= 1) {
        preALU.push(n);
        return true;
    }
    else
        return false;
}
int CPU::preALUFront() {
    return preALU.front();
}
void CPU::preALUPop() {
    preALU.pop();
}
int CPU::preALUSize() {
    return preALU.size();
}
bool CPU::preALUEmpty() {
    return preALU.empty();
}

// Must check the bool return value: if true, push() operation was success, false otherwise
bool CPU::preMemPush(int n) {
    if (preMem.size() <= 1) {
        preMem.push(n);
        return true;
    }
    else
        return false;
}
int CPU::preMemFront() {
    return preMem.front();
}
void CPU::preMemPop() {
    preMem.pop();
}
int CPU::preMemSize() {
    return preMem.size();
}
bool CPU::preMemEmpty() {
    return preMem.empty();
}

// Must check the bool return value: if true, push() operation was success, false otherwise
bool CPU::postALUPush(int n) {
    if (postALU.size() <= 0) {
        postALU.push(n);
        return true;
    }
    else
        return false;
}
int CPU::postALUFront() {
    return postALU.front();
}
void CPU::postALUPop() {
    postALU.pop();
}
int CPU::postALUSize() {
    return postALU.size();
}
bool CPU::postALUEmpty() {
    return postALU.empty();
}

// Must check the bool return value: if true, push() operation was success, false otherwise
bool CPU::postMemPush(int n) {
    if (postMem.size() <= 0) {
        postMem.push(n);
        return true;
    }
    else
        return false;
}
int CPU::postMemFront() {
    return postMem.front();
}
void CPU::postMemPop() {
    postMem.pop();
}
int CPU::postMemSize() {
    return postMem.size();
}
bool CPU::postMemEmpty() {
    return postMem.empty();
}
