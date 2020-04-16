#ifndef COREOBJECT_H
#define COREOBJECT_H
#include "downloader.h"
#include "MainWindow.h"

class CoreObject: public QMainWindow{

    Q_OBJECT

public:
      CoreObject() {}
      ~CoreObject() {}

      void ExecuteCore(){

          Downloader *dFile = new Downloader;
          dFile->doDownloadAll(); //Scarichiamo e salviamo i file in un file locale
          MainWindow *myWindowCore = new MainWindow;
          connect(dFile, SIGNAL(finish()),myWindowCore, SLOT(ExecutSlot() ) );
          //Finito il download del secondo file si inizia ad elaborare i dati
      }

};


#endif // COREOBJECT_H
