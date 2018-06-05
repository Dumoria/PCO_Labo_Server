#ifndef TASK_H
#define TASK_H


#include "request.h"
#include "abstractbuffer.h"
#include "requesthandler.h"
#include "runnable.h"
#include "requesthandler.h"
#include <QDebug>
#include <iostream>

class RunnableTask : public Runnable {

    friend class WorkerThread;
    friend class ThreadPool;

private:

    QString idTask;                          //Task id
    Request* request;                        //Requête assignée au threadWorker
    AbstractBuffer<Response>* responses;     //Buffer de réponse pour savoir où déposer la réponse une fois la requête traitée
    bool hasDebugLog;                        //Variable utilisée pour obtenir des logs pendant le debugging
    RequestHandler* requestHandler;          //Création d'un nouveau gestionnaire de requêtes



public:

    RunnableTask(Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog){
        requestHandler = new RequestHandler(*request ,hasDebugLog);     //Création d'un nouveau gestionnaire de requête
                                                                        //Gérer request de requestHandler en ptr
        idTask = ("Task n°");// + nextId++);

    }

    Request* getRequest(){
        return request;
    }

    virtual ~RunnableTask() {
        delete requestHandler;
    }

protected:
    void run(){
        Response response = requestHandler->handle();                    //Récupération de la réponse à la requête
        std::cout << response.getResponse().toStdString() << std::endl;
        responses->put(response);                                        //Transmission de la réponse au buffer de réponse
    }

     QString id(){
        return idTask;
    }

};


#endif // TASK_H
