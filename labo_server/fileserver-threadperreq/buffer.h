#ifndef BUFFER_H
#define BUFFER_H



class Buffer : public AbstractBuffer {
private:
    List<T> buffer;

protected:
  QSemaphore mutex;
  QSemaphore fifo;
  QSemaphore writer;
  int nbReaders;

public:
  ReaderWriterEqual() :
    mutex(1),
    fifo(1),
    writer(1),
    nbReaders(0) {}

  void lockReading() {
    fifo.acquire();
    mutex.acquire();
    nbReaders++;
    if (nbReaders==1) {
      writer.acquire();
    }
    mutex.release();
    fifo.release();
  }

  void unlockReading() {
    mutex.acquire();
    nbReaders--;
    if (nbReaders==0) {
      writer.release();
    }
    mutex.release();
  }

  void lockWriting() {
    fifo.acquire();
    writer.acquire();
  }

  void unlockWriting() {
    writer.release();
    fifo.release();
  }

  void put(T item){
      lockWriting();
      buffer.push_back(item);
      unlockWriting();

  }

  T get(){
      lockReading();
      T tmp = buffer.pop_back();
      unlockReading();
      return tmp;
  }

};

#endif // BUFFER_H
