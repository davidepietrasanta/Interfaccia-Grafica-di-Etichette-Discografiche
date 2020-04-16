#include "downloader.h"
#include <QCoreApplication>


Downloader::Downloader(QObject *parent) :
    QObject(parent), NDownload(0) {}

void Downloader::doDownload(QString strUrl)
{
    manager = new QNetworkAccessManager(this);

    connect(manager, SIGNAL(finished(QNetworkReply*) ),
            this, SLOT(replyFinished(QNetworkReply*) ) );

    manager->get(QNetworkRequest(QUrl( strUrl )));

}

void Downloader::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        //CONFIG   += console
        qDebug() << reply->header(QNetworkRequest::ContentTypeHeader).toString();
        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();



        QFile *file = new QFile(QCoreApplication::applicationDirPath() + "/tempFile.txt");
        if(file->open(QFile::Append))
        {
            file->write(reply->readAll());
            file->write("\n&&&&&\n");
            file->flush();
            file->close();
        }
        delete file;
        NDownload++;
    }

    reply->deleteLater();
    if( NDownload == 2 ){
        //qDebug() << "finish signal";
        emit finish();
    }
    if( NDownload == 1 ){
        //qDebug() << "First File signal";
        emit finishFirstFile();
    }

}

void Downloader::doDownloadAll(){
    const QString URLEMI = "http://www.ivl.disco.unimib.it/minisites/cpp/List_of_EMI_artists.txt";
    connect(this, SIGNAL(finishFirstFile()), this, SLOT(doDownloadSlot()) ); //Serve per sincronizzare il download
    doDownload(URLEMI);
}

void Downloader::doDownloadSlot(){
    //qDebug() << "Start doDownloadSlot";
    const QString URLUniversal = "http://www.ivl.disco.unimib.it/minisites/cpp/List_of_Universal_artists.txt";
    Downloader::doDownload(URLUniversal);
}
