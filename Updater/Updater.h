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


#include <QLibrary>
#include "../libnetwork/Network.h"

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
    QLibrary lib;

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
