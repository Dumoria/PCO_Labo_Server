/** @file readerwriteprioreadergeneral.h
 *  @brief Reader-writer with priority for readers
 *
 *  Implementation of a reader-writer resource manager with priority
 *  for readers. This class follows the "general" way of solving
 *  concurrent problems: internal variables, one mutex, and semaphores
 *  as synchronization primitives.
 *
 *
 *  @author Yann Thoma
 *  @date 08.05.2017
 *  @bug No known bug
 */

#ifndef READERWRITERPRIOREADERGENERAL_H
#define READERWRITERPRIOREADERGENERAL_H

#include <QSemaphore>

#include "abstractreaderwriter.h"


class ReaderWriterPrioReader2 :
      public AbstractReaderWriter {
protected:
  QSemaphore mutex;
  QSemaphore readerBlocker;
  QSemaphore writerBlocker;
  int nbReaders;
  int nbReadersWaiting;
  int nbWritersWaiting;
  bool oneWriter;

public:
  ReaderWriterPrioReader2() :
    mutex(1),
    nbReaders(0),
    nbReadersWaiting(0),
    nbWritersWaiting(0),
    oneWriter(false) {}

  void lockReading() {
    mutex.acquire();
    if (oneWriter) {
      nbReadersWaiting++;
      mutex.release();     // ouverture
      readerBlocker.acquire();
    }
    else {
      nbReaders++;
      mutex.release();
    }
  }

  void unlockReading() {
    mutex.acquire();
    nbReaders--;
    if (nbReaders==0) {
      if (nbWritersWaiting>0) {
        oneWriter=true;
        nbWritersWaiting--;
        writerBlocker.release();
      }
    }
    mutex.release();
  }

  void lockWriting() {
    mutex.acquire();
    if (oneWriter || (nbReaders>0)
        || (nbReadersWaiting>0)) {
      nbWritersWaiting++;
      mutex.release();       // ouverture
      writerBlocker.acquire();
    }
    else {
      oneWriter=true;
      mutex.release();}}

  void unlockWriting() {
    mutex.acquire();
    oneWriter=false;
    if (nbReadersWaiting>0) {
      for(int i=0;i<nbReadersWaiting;i++)
        readerBlocker.release();
      nbReaders=nbReadersWaiting;
      nbReadersWaiting=0;
    }
    else {
      if (nbWritersWaiting>0) {
        oneWriter=true;
        nbWritersWaiting--;
        writerBlocker.release();
      }
    }
    mutex.release();
  }
};
#endif // READERWRITERPRIOREADERGENERAL_H
