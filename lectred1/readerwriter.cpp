/** @file readerwriter.cpp
 *  @brief Test of reader-writer protocols
 *
 *  This code instantiates a reader-writer protocol and starts
 *  a certain number of readers and writers threads.
 *  A checker performs a light check in order to ensure
 *  mutual exclusion between readers and writers.
 *  You just need to change the resource creation to create
 *  various protocols.
 *
 *  @author Yann Thoma
 *  @date 08.05.2017
 *  @bug No known bug
 */

// General includes
#include <iostream>


// Qt related includes
#include <QCoreApplication>
#include <QThread>


// Application related includes
#include "abstractreaderwriter.h"
#include "readerwriterprioreaders.h"
#include "readerwriterprioreading.h"
#include "readerwriterprioreadergeneral.h"
#include "readerwriterequal.h"
#include "readerwriterpriowriter.h"



// Number of writer threads
#define NB_THREADS_WRITER     2

// Number of reader threads
#define NB_THREADS_READER     3



// The resource access protocole
AbstractReaderWriter *resource;




typedef struct {
    int nbRead;
    int nbWrite;
} ReaderWriterChecker;

ReaderWriterChecker checker;




class Writer : public QThread
{
public:
    Writer(int tid) : tid(tid) {}

    int tid;

    void run() Q_DECL_OVERRIDE {
        while(1) {
            resource->lockWriting();
            checker.nbWrite++;
            if (checker.nbRead!=0) {
                std::cout << "Task writer " << tid << ": There is a reading. That's bad" << std::endl;
            }
            if (checker.nbWrite!=1) {
                std::cout << "Task writer " << tid << ": There is a writing. That's bad" << std::endl;
            }
            std::cout << "Task " << tid << ": writing" << std::endl;
            //	usleep(1000000);
            usleep((int)((float)600000*rand()/(RAND_MAX+1.0)));
            if (checker.nbRead!=0) {
                std::cout << "Task writer " << tid << ": There is a reading. That's bad" << std::endl;
            }
            if (checker.nbWrite!=1) {
                std::cout << "Task writer " << tid << ": There is a writing. That's bad" << std::endl;
            }
            checker.nbWrite--;
            resource->unlockWriting();
            //	usleep(1000000);
            usleep((int)((float)600000*rand()/(RAND_MAX+1.0)));
        }
    }
};


class Reader : public QThread
{
public:
    Reader(int tid) : tid(tid) {}

    int tid;

    void run() Q_DECL_OVERRIDE {
        while(1) {
            resource->lockReading();

            checker.nbRead++;
            if (checker.nbWrite!=0) {
                std::cout << "Task reader " << tid << ": There is a writing. That's bad" << std::endl;
            }
            std::cout << "Task " << tid << ": reading" << std::endl;
            usleep((int)((float)60000*rand()/(RAND_MAX+1.0)));
            //usleep(100000);
            if (checker.nbWrite!=0) {
                std::cout << "Task reader " << tid << ": There is a writing. That's bad" << std::endl;
            }
            checker.nbRead--;

            resource->unlockReading();
            //	usleep(2000000);
            usleep((int)((float)600000*rand()/(RAND_MAX+1.0)));

        }
    }
};

int main (int /*argc*/, char *[]/*argv[]*/)
{
    Writer* threadsRed[NB_THREADS_WRITER];
    Reader* threadsLec[NB_THREADS_READER];

    checker.nbWrite=0;
    checker.nbRead=0;

    /**************************************************************************
     * Change the instantiation in order to create other protocols.
     *************************************************************************/
    resource = new ReaderWriterPrioWriter();

    for(int t=0; t<NB_THREADS_READER; t++){
        std::cout << "In main: creating thread reader " << t << std::endl;
        threadsLec[t] = new Reader(t);
        threadsLec[t]->start();
    }
    for(int t=0; t<NB_THREADS_WRITER; t++){
        std::cout << "In main: creating thread writer " << t << std::endl;
        threadsRed[t] = new Writer(t);
        threadsRed[t]->start();
    }

    for(int t=0; t<NB_THREADS_READER; t++){
        threadsLec[t]->wait();
    }
    for(int t=0; t<NB_THREADS_WRITER; t++){
        threadsRed[t]->wait();
    }

    return 0;
}

