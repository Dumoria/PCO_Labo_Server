#include "requestdispatcherthread.h"
#include "response.h"
#include "workerthread.h"
#include "runnabletask.h"
#include <QDebug>
#include "threadpool.h"

RequestDispatcherThread::RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(requests), responses(responses), hasDebugLog(hasDebugLog) {
    threadPool = new ThreadPool(5, hasDebugLog);
    if (hasDebugLog)
        qDebug() << "Created request dispatcher thread";
}

void RequestDispatcherThread::run()
{
    unsigned int nbRequetes;
    QString idTask;

    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request requ = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request '" << requ.getFilePath() << "', starting new WorkerThread...";

        //idTask = std::itoa(nbRequetes++);
        RunnableTask* task = new RunnableTask(idTask, &requ, responses, hasDebugLog);
        threadPool->start(task);

    }
}

RequestDispatcherThread::~RequestDispatcherThread(){
    delete threadPool;
}
