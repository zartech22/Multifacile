#ifndef CHECKUPDATE_H
#define CHECKUPDATE_H

#include <QTcpSocket>

class CheckUpdate : public QTcpSocket
{
    Q_OBJECT
public:
    CheckUpdate(QObject *parent, int version);
    void sendRequest();
    void updateRequire();
private:
    quint16 messageSize;
    int actualVersion;
public slots:
    void dataReceived();
signals:
    void updateNeeded(bool);
};

#endif // CHECKUPDATE_H
