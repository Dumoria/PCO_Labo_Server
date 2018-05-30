#include "requestdispatcherthread.h"
#include "response.h"
#include "workerthread.h"
#include <QDebug>

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(requests), responses(responses), hasDebugLog(hasDebugLog) {
    if (hasDebugLog)
        qDebug() << "Created request dispatcher thread";
}

void RequestDispatcherThread::run()
{
    std::list<WorkerThread*> workersToRemove;

    while(true) {

        //Check for finished workers
        for(WorkerThread* worker : workersStarted){
            if(worker->isFinished()){
                worker->terminate();
                workersToRemove.push_back(worker);
            }
        }

        //Remove workers frome the workersStarted and delete them
        for(WorkerThread* worker : workersToRemove){
            workersStarted.remove(worker);
            delete worker;
        }

        //Clear workers to remove
        workersToRemove.clear();

        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request requ = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request '" << requ.getFilePath() << "', starting new WorkerThread...";

        WorkerThread* worker = new WorkerThread(&requ, responses, hasDebugLog);         //Création d'un nouveau thread pour gérer la requête
        workersStarted.push_back(worker);                                               //Ajout du thread en question à la liste des workers encore actifs
        worker->start();                                                                //Faire travailler le worker
    }
}

RequestDispatcherThread::~RequestDispatcherThread(){

}
