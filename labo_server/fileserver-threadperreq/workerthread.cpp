
#include "workerthread.h"
#include "response.h"
#include "requesthandler.h"
#include <QDebug>

void WorkerThread::run()
{
   RequestHandler requestHandler(*request, hasDebugLog);
   Response response = requestHandler.handle();
   responses->put(response);
}
