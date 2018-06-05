#ifndef REQUESTDISPATCHERTHREAD_H
#define REQUESTDISPATCHERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "abstractbuffer.h"
#include "response.h"
#include "workerthread.h"
#include "threadpool.h"
#include <list>


/* Cette classe permet de dispatcher les requêtes
 * sur plusieurs threads afin de ne pas surcharger
 * un seul thread
 */
class RequestDispatcherThread: public QThread
{
    Q_OBJECT

private:
    AbstractBuffer<Request>* requests;          //Buffer de requêtes en attente
    AbstractBuffer<Response>* responses;        //Buffer de réponses en attente (pour transmettre au workers)
    ThreadPool* threadPool;
    bool hasDebugLog;                           //Variable utilisée pour obtenir des logs pendant le debugging


public:
    RequestDispatcherThread(AbstractBuffer<Request>* requests, AbstractBuffer<Response>* responses, bool hasDebugLog);

    virtual ~RequestDispatcherThread();

protected:
    void run();

};


#endif // REQUESTDISPATCHERTHREAD_H
