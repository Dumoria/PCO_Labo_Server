#include "workerthread.h"


WorkerThread::WorkerThread(Request* request,  AbstractBuffer<Response>* responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog) {
    requestHandler = new RequestHandler(*request, hasDebugLog);     //Création d'un nouveau gestionnaire de requête
}

void WorkerThread::run()
{
   Response response = requestHandler->handle();                    //Récupération de la réponse à la requête
   responses->put(response);                                        //Transmission de la réponse au buffer de réponse
}


WorkerThread::~WorkerThread() {

}
