#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "response.h"

class RequestDispatcherThread: public QThread
{
    Q_OBJECT


private:
    AbstractBuffer<Request>* requests;
    AbstractBuffer<Response>* responses;
    List<WorkerThread*> wokersStarted;

    bool hasDebugLog;


public:
    RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog): requests(requests), responses(responses), hasDebugLog(hasDebugLog) {
        if (hasDebugLog)
            qDebug() << "Created request dispatcher thread";
        qRegisterMetaType<Request>("Request");
    }

protected:
    void run();

};


#endif // REQUESTDISPATCHERTHREAD_H
