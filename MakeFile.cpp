/*
 Name: Kelsey (Tien) Nguyen & Maram Almutairi
 Project 1
 CS312 - Mckenney
 2-17-2017
 Description: find max average of a neighborhood of cells and report it.
 Try to minimize time spent by multithreading.
 */


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <sstream>
#include <list>
#include <string>
#include <thread>
#include <mutex>
#include <pthread.h>


using namespace std;

//variables
int bestRow(0);
int bestColumn(0);
float bestAvg(0);
std::mutex myMutex;


void computeAvg(unsigned int **arr, int row, int col);


// a class to get more accurate time

class stopwatch{
    
    private:
    double elapsedTime;
    double startedTime;
    bool timing;
    //returns current time in seconds
    double current_time( )
    {
        timeval tv;
        gettimeofday(&tv, NULL);
        double rtn_value = (double) tv.tv_usec;
        rtn_value /= 1e6;
        rtn_value += (double) tv.tv_sec;
        return rtn_value;
    }
    
    public:
    stopwatch( ): elapsedTime( 0 ), startedTime( 0 ), timing( false )
    {
    }
    
    void start( )
    {
        if( !timing )
        {
            timing = true;
            startedTime = current_time( );
        }
    }
    
    void stop( )
    {
        if( timing )
        {
            elapsedTime +=  current_time( )-startedTime;
            timing = false;
        }
    }
    
    void resume( )
    {
        start( );
    }
    
    void reset( )
    {
        elapsedTime = 0;
        startedTime = 0;
        timing = false;
    }
    
    double getTime( )
    {
        return elapsedTime;
    }
};



// function takes an array pointer, and the number of rows and cols in the array, and
// allocates and intializes the two dimensional array to a bunch of random numbers

void makeRandArray( unsigned int **& data, unsigned int rows, unsigned int cols, unsigned int seed )
{
    // allocate the array
    data = new unsigned int*[ rows ];
    for( unsigned int i = 0; i < rows; i++ )
    {
        data[i] = new unsigned int[ cols ];
    }
    
    // seed the number generator
    // you should change the seed to get different values
    srand( seed );
    
    // populate the array
    
    for( unsigned int i = 0; i < rows; i++ )
    for( unsigned int j = 0; j < cols; j++ )
    {
        data[i][j] = rand() % 10000 + 1; // number between 1 and 10000
    }
}

void getDataFromFile( unsigned int **& data, char fileName[], unsigned int &rows, unsigned int &cols )
{
    ifstream in;
    in.open( fileName );
    if( !in )
    {
        cerr << "error opening file: " << fileName << endl;
        exit( -1 );
    }
    
    in >> rows >> cols;
    data = new unsigned int*[ rows ];
    for( unsigned int i = 0; i < rows; i++ )
    {
        data[i] = new unsigned int[ cols ];
    }
    
    // now read in the data
    
    for( unsigned int i = 0; i < rows; i++ )
    for( unsigned int j = 0; j < cols; j++ )
    {
        in >> data[i][j];
    }
    
}




int main( int argc, char* argv[] )
{
    if( argc < 3 )
    {
        cerr<<"Usage: " << argv[0] << " [input data file] [num of threads to use] " << endl;
        
        cerr<<"or" << endl << "Usage: "<< argv[0] << " rand [num of threads to use] [num rows] [num cols] [seed value]" << endl;
        exit( 0 );
    }
    
    // read in the file
    unsigned int rows, cols, seed;
    unsigned int numThreads;
    unsigned int ** data;
    // convert numThreads to int
    {
        stringstream ss1;
        ss1 << argv[2];
        ss1 >> numThreads;
    }
    
    string fName( argv[1] );
    if( fName == "rand" )
    {
        {
            stringstream ss1;
            ss1 << argv[3];
            ss1 >> rows;
        }
        {
            stringstream ss1;
            ss1 << argv[4];
            ss1 >> cols;
        }
        {
            stringstream ss1;
            ss1 << argv[5];
            ss1 >> seed;
        }
        makeRandArray( data, rows, cols, seed );
    }
    else
    {
        getDataFromFile( data,  argv[1], rows, cols );
    }
    
    cerr << "data: " << endl;
    for( unsigned int i = 0; i < rows; i++ )
    {
        for( unsigned int j = 0; j < cols; j++ )
        {
            cerr << "i,j,data " << i << ", " << j << ", ";
            cerr << data[i][j] << " ";
        }
        cerr << endl;
    }
    cerr<< endl;
    
    // tell omp how many threads to use
    omp_set_num_threads( numThreads );
    
#pragma omp parallel
    {
    }
    
    stopwatch S1;
    S1.start();
    
    /////////////////////////////////////////////////////////////////////
    ///////////////////////  YOUR CODE HERE       ///////////////////////
    /////////////////////////////////////////////////////////////////////
    // TODO code application logic here
    
    pthread_create(&inputTimer, NULL, stopwatch, NULL);
    
    
    std::thread **threads = new std::thread*[numThreads];
    
    int rowsPerThread = rows/numThreads + 1;
    
    
    for(int i=0;i<numThreads;i++)
    {
        int rowStart = i*rowsPerThread;
        threads[i] = new std::thread(computeAvg, &data, rowStart, rowsPerThread, cols);
        
    }
    
    //end main
    for(int i=0;i<numThreads;i++)
    {
        threads[i]->join();
    }
    
    S1.stop();
    
    // print out the max value here
    cout << "largest average: " << bestAvg << endl;
    cout << "found at cells: (" << bestRow << "," << bestColumn << ")" << endl;
    cerr << "elapsed time: " << S1.getTime( ) << endl;
    
}



//computes avg and prints highest avg with cell #
void computeAvg(unsigned int **arr, int rows, int rowPerThread, int cols ){
    float newAvg=0;
    float sum=0;
    for (int i=1;i<rows-1;i++){
        for (int j=1; j<cols-1;j++){
            sum = (arr[i-1][j-1]+
                   arr[i-1][j]+
                   arr[i-1][j+1]+
                   arr[i][j-1]+
                   arr[i][j]+
                   arr[i][j+1]+
                   arr[i+1][j-1]+
                   arr[i+1][j]+
                   arr[i+1][j+1]);
            newAvg=sum/9;
            
            if (newAvg>=bestAvg){
                bool failed = true;
                while(failed)
                {
                    if(myMutex.try_lock())
                    {
                        bestAvg=newAvg;
                        bestRow=i;
                        bestColumn=j;
                        myMutex.unlock();
                        failed = false;
                    }
                }
                
            }
        }
    }
    
    
}


//end file


