#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "requesthandler.h"
#include "QSemaphore"
#include "runnabletask.h"
#include "QMutex"
#include "QWaitCondition"

/* Cette classe permet de modeliser les thread
 * devant traîter les requêtes
 */
class WorkerThread: public QThread
{
   Q_OBJECT

private:

   RunnableTask* task;
   QSemaphore* wait;
   QMutex* mutex;
   QWaitCondition* condAvailbleThreads;

   std::list<WorkerThread*>* availableThreads;

   bool hasDebugLog;                        //Variable utilisée pour obtenir des logs pendant le debugging


public:

    WorkerThread(bool hasDebugLog, RunnableTask* task, QSemaphore* wait, QMutex* mutex, std::list<WorkerThread*>* availableThreads,  QWaitCondition* condAvailbleThreads): hasDebugLog(hasDebugLog), task(task), wait(wait), mutex(mutex), availableThreads(availableThreads), condAvailbleThreads(condAvailbleThreads){
    }

    ~WorkerThread(){
    }

    void assignRunnable(RunnableTask* task){
        this->task = task;
    }

    /* Le worker thread va executer les tâches qu'on
     * lui donne puis attend qu'on lui signale l'arrivée
     * d'une nouvelle tâche
     */
    void run(){
        while(true){
            task->run();

            mutex->lock();
            availableThreads->push_back(this);
            mutex->unlock();

            condAvailbleThreads->wakeOne();
            wait->acquire();
        }
    }

};

#endif // WORKERTHREAD_H


