#ifndef CHECKUPDATE_H
#define CHECKUPDATE_H

#include <QTcpSocket>

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
    void updateNeeded(bool);
};

#endif // CHECKUPDATE_H
