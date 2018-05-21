#include "requestdispatcherthread.h"
#include "response.h"
#include <QDebug>

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for requests...";
        Request requ = requests->get();   // block until a request is available
        if (hasDebugLog)
            qDebug() << "Got a request '" << resp.getRequest().getFilePath() << "', signalling...";
        //responseReady(resp); // send signal
    }
}
