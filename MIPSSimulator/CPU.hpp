#ifndef __CPU_HPP__
#define __CPU_HPP__

#include <queue>
#include <stack>
#include <array>
#include <vector>
//=================================

using namespace std;

class CPU
{
private:
    stack<int> preIssue;         //STL stack is a LIFO structure; this has four elements.
    queue<int> preALU, preMem;   //STL queue is a FIFO structure; these have two elements.
    queue<int> postALU, postMem; //only one element allowed
public:
    array<int, 32> registers = { 0 };
    array<int, 16> cache = { 0 };
    array<bool, 8> cacheLRUbit = { 0 };
    array<bool, 8> cacheValidBit = { 0 };
    array<bool, 8> cacheDirtyBit = { 0 };
    array<bool, 8> cacheTagBit = { 0 };
    //vector<int> data = { 7, 5, 16, 8 };  //test data
    vector<int> data;
    
    string toString() const;
    
    bool preIssuePush(int n);
    int preIssueTop();
    void preIssuePop();
    int preIssueSize();
    bool preIssueEmpty();
    
    bool preALUPush(int n);
    int preALUFront();
    void preALUPop();
    int preALUSize();
    bool preALUEmpty();
    
    bool preMemPush(int n);
    int preMemFront();
    void preMemPop();
    int preMemSize();
    bool preMemEmpty();
    
    bool postALUPush(int n);
    int postALUFront();
    void postALUPop();
    int postALUSize();
    bool postALUEmpty();
    
    bool postMemPush(int n);
    int postMemFront();
    void postMemPop();
    int postMemSize();
    bool postMemEmpty();
    
};

#endif // __CPU_HPP__
