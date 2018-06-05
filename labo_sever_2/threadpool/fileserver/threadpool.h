#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "workerthread.h"
#include "QSemaphore"
#include "QMutex"
#include "QWaitCondition"

//C:\Users\benja\OneDrive\Documents\HEIG\Git\PCO\PCO_Labo_Server\labo_sever_2\threadpool\fileserver\shakespeare.txt
class ThreadPool
{


private :

    unsigned int maxThreadCount;                 //Nombre maximum de thread dans la threadPool
    bool hasDebugLog;

    std::list<WorkerThread*> threadPool;         //Liste des threads présents dans la threadPool
    std::list<WorkerThread*> availableThreads;   //Liste des threads disponibles dans la threadPool

    QSemaphore wait;                             //Permet aux threads de la thread pool de faire une attente passive
    QMutex mutex;                                //Sécurisation des variables locales
    QWaitCondition condAvailbleThreads;          //Attendre la disponibilité d'un thread


public:

    ThreadPool(int maxThreadCount) : maxThreadCount(maxThreadCount){

    }

    ThreadPool(int maxThreadCount, bool hasDebugLog) : maxThreadCount(maxThreadCount), hasDebugLog(hasDebugLog), wait(0), mutex(), condAvailbleThreads(){

    }

    ~ThreadPool(){

        const int size = threadPool.size();
        WorkerThread* tmp;

        for(int i = 0; i < size; ++i){
            tmp = threadPool.front();
            tmp->terminate();
            threadPool.pop_front();
            delete tmp;
        }

    }

    /* Start a runnable. If a thread in the pool is avaible, assign the
    runnable to it. If no thread is available but the pool can grow,
    create a new pool thread and assign the runnable to it. If no
    thread is available and the pool is at max capacity, block the
    caller until a thread becomes available again.*/
    void start(Runnable* runnable) {

        mutex.lock();

        if(threadPool.size() < maxThreadCount){
            WorkerThread* worker = new WorkerThread(hasDebugLog, (RunnableTask*) runnable, &wait, &mutex, &availableThreads, &condAvailbleThreads);
            threadPool.push_back(worker);
            worker->start();
        }else{

            while(!availableThreads.size()){
                condAvailbleThreads.wait(&mutex);
            }

            availableThreads.front()->assignRunnable((RunnableTask*) runnable);
            wait.release();
            availableThreads.pop_front();
        }
        mutex.unlock();
    }
};


#endif // THREADPOOL_H
