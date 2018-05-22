
#include "workerthread.h"
#include "response.h"
#include <QDebug>

void WorkerThread::run()
{
    QString a = "la ou il y aura la reponse";
   Response response(*request, a);
   responses->put(response);
}
