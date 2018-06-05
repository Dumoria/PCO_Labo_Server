#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "workerthread.h"
#include "QSemaphore"
#include "QMutex"

class ThreadPool
{


private :

    unsigned int maxThreadCount;                //Nombre maximum de thread dans la threadPool
    bool hasDebugLog;

    std::list<WorkerThread*> threadPool;         //Liste des threads présents dans la threadPool
    std::list<WorkerThread*> availableThreads;   //Liste des threads disponibles dans la threadPool
    AbstractBuffer<Response>* responses;        //Buffer de réponse pour savoir où déposer la réponse une fois la requête traitée

    QSemaphore wait;                            //Permet aux threads de la thread pool de faire une attente passive
    QMutex mutex;
    

public:

    ThreadPool(int maxThreadCount) : maxThreadCount(maxThreadCount), threadPool(), availableThreads(){

    }

    ThreadPool(int maxThreadCount, bool hasDebugLog,  AbstractBuffer<Response>* responses) : maxThreadCount(maxThreadCount), hasDebugLog(hasDebugLog), threadPool(), availableThreads(), responses(responses), wait(0){
    }
    
    ~ThreadPool(){
       //delete all ptr
    }

    /* Start a runnable. If a thread in the pool is avaible, assign the
    runnable to it. If no thread is available but the pool can grow,
    create a new pool thread and assign the runnable to it. If no
    thread is available and the pool is at max capacity, block the
    caller until a thread becomes available again.*/
    void start(Runnable* runnable) {
        mutex.lock();
        if(threadPool.size() < maxThreadCount){
           WorkerThread* worker = new WorkerThread(hasDebugLog, (RunnableTask*) runnable, &wait, &availableThreads);
            threadPool.push_back(worker);
            worker->start();
        }else if(availableThreads.size()){
            availableThreads.front()->assignRunnable((RunnableTask*) runnable);
            availableThreads.pop_front();
        }
        mutex.unlock();
    }
};


#endif // THREADPOOL_H
