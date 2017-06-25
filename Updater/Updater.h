#ifndef UPDATER_H
#define UPDATER_H

#ifdef RELEASE
    #define NETWORK "network"
#elif defined(DEBUG)
    #define NETWORK "networkd"
#endif

#include <QProgressDialog>
#include <QMessageBox>
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include <QProcess>
#include <QTextCodec>
#include <QDir>

#include "../libnetwork/Network.h"

static const uint16_t updatePort = 8090;
static const char* serverName = "multifacile.no-ip.org";

typedef enum QueryState QueryState;

enum QueryState
{
    FileQuery, NameQuery, ToDoQuery
};

class Updater : public QProgressDialog
{
    Q_OBJECT
public:
    Updater();
    ~Updater() {}
public slots:
    void ReceiveFilesData(QByteArray*);
    void ReceiveNamesData(QByteArray*);
    void ReceiveToDoData(QByteArray *);
    void setConnection() { sendRequest(FileQuery); }
    void stop() { qApp->quit(); }
private:

    Network *net;

    quint64 FilesMessageSize;

    quint16 NamesMessageSize;

    quint16 ToDoMessageSize;

    quint16 FilesNumber;

    quint16 downloadedFiles;

    quint32 fileSize;

    QString request, name, ToDo;
    QList<QFile *> files;
    bool downloaded;

    void remplacement();
    void sendRequest(QueryState state);
    void ToDoProcess();
    void finish();
};

#endif // UPDATER_H
