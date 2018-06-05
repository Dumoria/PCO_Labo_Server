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

/* Cette classe permet de modeliser les thread
 * devant traîter les requêtes
 */
class WorkerThread: public QThread
{
    Q_OBJECT

private:

   RunnableTask* task;
   QSemaphore* wait;

   std::list<WorkerThread*>* availableThreads;

   bool hasDebugLog;                        //Variable utilisée pour obtenir des logs pendant le debugging
   RequestHandler* requestHandler;          //Création d'un nouveau gestionnaire de requêtes

public:

    WorkerThread(bool hasDebugLog, RunnableTask* task, QSemaphore* wait,  std::list<WorkerThread*>* availableThreads): hasDebugLog(hasDebugLog), task(task), wait(wait), availableThreads(availableThreads) {
        requestHandler = new RequestHandler(*(task->getRequest()) ,hasDebugLog);     //Création d'un nouveau gestionnaire de requête
                                                                                     //Gérer request de requestHandler en ptr
    }

    ~WorkerThread(){
        delete requestHandler;
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
            task->setRequestHandlerFromCurrentThread(requestHandler);
            task->run();
            availableThreads->push_back(this);
            wait->acquire();
        }
    }

};

#endif // WORKERTHREAD_H


