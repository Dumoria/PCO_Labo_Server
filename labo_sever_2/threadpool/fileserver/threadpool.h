#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "workerthread.h"

class ThreadPool
{


private :

    unsigned int maxThreadCount;

    std::list<WorkerThread> threadPool;
    std::list<WorkerThread> availableThreads;

public:

    ThreadPool(int maxThreadCount) : maxThreadCount(maxThreadCount), threadPool(){

    }

    /* Start a runnable. If a thread in the pool is avaible, assign the &
    !runnable to it. If no thread is available but the pool can grow, &
    !create a new pool thread and assign the runnable to it. If no &
    !thread is available and the pool is at max capacity, block the &
    !caller until a thread becomes available again.

    Créer des threads et assigner au runnable

    Modificer requestDispatcher pour utilisation de la threadPool et non création indefiniment
    Modifer buffer prob pour assurer un non bloquage des requête mais ignore après un certain nb de bloqu (ou pres dans buffer, sais pas trop encore)

*/

    //Prob quelque chose du genre waitForAvailable

    /* Passer list aux worker pour qu'ils s'ajoutent eux-même en fin si possible
     * Eventuellement semaphore bloquant puis appelé depuis thread dispo
     */

    void start(Runnable* runnable) {
        if(threadPool.size() < maxThreadCount){
            threadPool.push_back(new WorkerThread(runnable)); //Check pour construction
        }else if(availableThreads.size()){
            availableThreads.pop_front().assign(runnable);    //Check assign
        }else{

        }
    }
}


#endif // THREADPOOL_H
