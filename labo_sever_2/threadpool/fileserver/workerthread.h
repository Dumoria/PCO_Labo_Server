#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "Request.h"
#include "response.h"
#include "abstractbuffer.h"
#include "requesthandler.h"

/* Cette classe permet de modeliser les thread
 * devant traîter les requêtes
 */
class WorkerThread: public QThread
{
    Q_OBJECT

private:
   Request* request;                        //Requête assignée au threadWorker
   AbstractBuffer<Response>* responses;     //Buffer de réponse pour savoir où déposer la réponse une fois la requête traitée
   bool hasDebugLog;                        //Variable utilisée pour obtenir des logs pendant le debugging
   RequestHandler* requestHandler;          //Création d'un nouveau gestionnaire de requêtes

public:

    WorkerThread(Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog);


    virtual ~WorkerThread();

protected:
    void run();

};

#endif // WORKERTHREAD_H
