#ifndef CHECKUPDATE_H
#define CHECKUPDATE_H

#include <QTcpSocket>

typedef enum UpdateType UpdateType;

enum UpdateType
{
    NoUpdate, NormalUpdate, UpdaterUpdate
};

class CheckUpdate : public QTcpSocket
{
    Q_OBJECT
public:
    CheckUpdate(QObject *parent, const int version);
    void tryConnection();
private:
    quint16 messageSize;
    int actualVersion;
public slots:
    void dataReceived();
    void sendRequest();
signals:
    void checkUpdateAnswer(UpdateType);
};

#endif // CHECKUPDATE_H
