#include <QApplication>
#include <QMainWindow>
#include "CoreObject.h"
#include <QCloseEvent>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CoreObject window;
    window.setWindowTitle(QString::fromUtf8("MainWindow"));
    window.ExecuteCore();

    int ret = app.exec();
    //In questo modo prima della chiusura completa elimina il file creato
    QFile::remove(QCoreApplication::applicationDirPath() + "/tempFile.txt");
    return ret;
}
