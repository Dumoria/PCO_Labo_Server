
#include "workerthread.h"
#include "response.h"
#include <QDebug>

void WorkerThread::run()
{

   Response response(*request, "la ou il y aura la reponse");
   responses.put(response);
}
