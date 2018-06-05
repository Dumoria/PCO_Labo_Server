#ifndef RUNNABLETASK_H
#define RUNNABLETASK_H

#include "request.h"
#include "abstractbuffer.h"
#include "requesthandler.h"

class RunnableTask : public Runnable{

private:

    QString idTask;                          //Task id
    //static int nextId;                     //Next id to attribute


    Request* request;                        //Requête assignée au threadWorker
    AbstractBuffer<Response>* responses;     //Buffer de réponse pour savoir où déposer la réponse une fois la requête traitée
    bool hasDebugLog;                        //Variable utilisée pour obtenir des logs pendant le debugging
    RequestHandler* requestHandler;          //Création d'un nouveau gestionnaire de requêtes



public:

    RunnableTask(Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog){
        idTask = ("Task n°");// + nextId++);

    }

    Request* getRequest(){
        return request;
    }


    void setRequestHandlerFromCurrentThread(RequestHandler* requestHandler){
        this->requestHandler = requestHandler;
    }

    virtual ~RunnableTask() {

    }

    void run(){
        Response response = requestHandler->handle();                    //Récupération de la réponse à la requête
        responses->put(response);                                        //Transmission de la réponse au buffer de réponse
    }

    virtual QString id(){
        return idTask;
    }

};

#endif // RUNNABLETASK_H
