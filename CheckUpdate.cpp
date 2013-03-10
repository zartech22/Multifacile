/*Copyright (C) <2012> <Plestan> <Kévin>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

#include "CheckUpdate.h"

CheckUpdate::CheckUpdate(QObject *parent, const int version) : QTcpSocket(parent), actualVersion(version), messageSize(0)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
    connect(this, SIGNAL(connected()), this , SLOT(sendRequest()));
    Connection();
}
void CheckUpdate::sendRequest()
{
        QByteArray paquet;
        QDataStream out(&paquet, QIODevice::WriteOnly);
        out << (quint16) 0;
        out << actualVersion;
        out.device()->seek(0);
        out << (quint16) (paquet.size() - sizeof(quint16));
        write(paquet);
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

    if(answer == "ok")
        emit checkUpdateAnswer(NoUpdate);
    else if(answer == "update needed")
        emit checkUpdateAnswer(NormalUpdate);
    else if(answer == "updaterUpdate")
        emit checkUpdateAnswer(UpdaterUpdate);

    messageSize = 0;
}
void CheckUpdate::tryConnection()
{
    Connection();
}

inline void CheckUpdate::Connection()
{
    this->abort();
    this->connectToHost("multifacile.no-ip.org", 8087);
}
