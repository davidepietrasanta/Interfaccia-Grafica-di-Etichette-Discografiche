#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QString>

class Downloader : public QObject
{   unsigned int NDownload;
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    void doDownload(QString strUrl);
    void doDownloadAll();

signals:
    void finish();
    void finishFirstFile();

public slots:
    void replyFinished (QNetworkReply *reply);
    void doDownloadSlot();

private:
   QNetworkAccessManager *manager;

};

#endif // DOWNLOADER_H
