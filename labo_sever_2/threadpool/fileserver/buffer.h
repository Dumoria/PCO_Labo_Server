#ifndef BUFFER_H
#define BUFFER_H

#include "abstractbuffer.h"
#include <QSemaphore>

const int NoInitTamponN = 10;

/* Cette classe représente le buffer de requêtes/réponses
 * (voir support de cours pour de plus amples informations)
 */
template<typename T> class Buffer : public AbstractBuffer<T> {

protected:
    T *elements;
    int writePointer;
    int readPointer;
    int bufferSize;
    QSemaphore mutex, waitNotFull, waitNotEmpty;

public:
    Buffer(unsigned int size) : mutex(1), waitNotFull(size) {
        if ((elements = new T[size]) != 0) {
            writePointer = readPointer = 0;
            bufferSize = size;
            return;
        }
        throw NoInitTamponN;
    }

    virtual ~Buffer() {
        delete[] elements;
    }

    virtual void put(T item) {
        waitNotFull.acquire();
        mutex.acquire();
        elements[writePointer] = item;
        writePointer = (writePointer + 1) % bufferSize;
        waitNotEmpty.release();
        mutex.release();
    }

    virtual T get(void) {
        T item;
        waitNotEmpty.acquire();
        mutex.acquire();
        item = elements[readPointer];
        readPointer = (readPointer + 1) % bufferSize;
        waitNotFull.release();
        mutex.release();
        return item;
    }
};


#endif // BUFFER_H
