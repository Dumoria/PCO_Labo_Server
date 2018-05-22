#include "requestdispatcherthread.h"
#include "response.h"
#include "workerthread.h"
#include <QDebug>

void RequestDispatcherThread::run()
{
    while(true) {

        for(WorkerThread* worker : workersStarted){
            if(worker->isFinished()){
                worker->terminate();
                workersStarted.remove(worker);
            }
        }

        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request requ = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request '" << requ.getFilePath() << "', starting new WorkerThread...";

        workersStarted.push_back(new WorkerThread(&requ, responses, hasDebugLog));
    }
}
