#include "CheckUpdate.h"

CheckUpdate::CheckUpdate(QObject *parent, int version) : QTcpSocket(parent)
{
    actualVersion = version;
    messageSize = 0;

    tryConnection();

    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(this, SIGNAL(connected()), this , SLOT(sendRequest()));
}
void CheckUpdate::sendRequest()
{
        QByteArray paquet;
        QDataStream out(&paquet, QIODevice::WriteOnly);
        out << (quint16) 0;
        out << actualVersion;
        out.device()->seek(0);
        out << (quint16) (paquet.size() - sizeof(quint16));
        this->write(paquet);
}
void CheckUpdate::dataReceived()
{
    QDataStream in(this);
    if(messageSize == 0)
    {
        if(this->bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> messageSize;
    }
    if(this->bytesAvailable() < messageSize)
        return;
    QString answer;
    in >> answer;

    qDebug("ok");
    if(answer == "ok")
        emit updateNeeded(false);
    else if(answer == "update needed")
        emit updateNeeded(true);

    messageSize = 0;
}
void CheckUpdate::tryConnection()
{
    this->abort();
    this->connectToHost("multifacile.no-ip.org", 8087);
}
