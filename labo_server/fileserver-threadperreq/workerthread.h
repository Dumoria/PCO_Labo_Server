#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Request.h"
#include "response.h"
#include "abstractbuffer.h"


class WorkerThread: public QThread
{
    Q_OBJECT

public:
    WorkerThread(Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog) {

        //qRegisterMetaType<request>("request");
    }

protected:
    void run();

private:
   AbstractBuffer<Response>* responses;
   Request* request;
   bool hasDebugLog;

};

#endif // WORKERTHREAD_H
