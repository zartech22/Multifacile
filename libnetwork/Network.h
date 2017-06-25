/*Copyright (C) <2013> <Plestan> <Kévin>

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

#ifndef NETWORK_H
#define NETWORK_H

#include "network_global.h"

#include <QString>
#include <QTcpSocket>
#include <memory>

enum class QUIntSize
{
    QUInt16, QUInt32, QUInt64
};

class NETWORKSHARED_EXPORT Network : public QTcpSocket
{
    Q_OBJECT
    
public:
    Network();
    void sendMsg(const QString &msg, const QUIntSize answerMsgSize = QUIntSize::QUInt16) { _size = answerMsgSize; writePaquet<QString>(msg); }
    void sendVersion(const unsigned int version) {  _size = QUIntSize::QUInt16; writePaquet<unsigned int>(version); }
    void tryConnection(const QString &host, const unsigned int port) { connection(host, port); }

private:
    void connection(const QString &host, const unsigned int port) { abort(); connectToHost(host, port); }

    unsigned int _version;
    QString _msg;
    QUIntSize _size;

    template<typename T>
    void writePaquet(const T &var)
    {
        QByteArray paquet;
        QDataStream out(&paquet, QIODevice::WriteOnly);

        out << (quint16) 0;
        out << var;

        out.device()->seek(0);

        out << (quint16) (paquet.size() - sizeof(quint16));

        write(paquet);
    }

    template<typename T>
    void dataReceived()
    {
        static T msgSize = 0;

        QDataStream in(this);
        auto paquet = std::make_unique<QByteArray>();

        if(msgSize == 0)
        {
            if(bytesAvailable() < static_cast<qint64>(sizeof(msgSize)))
                return;
            in >> msgSize;
        }

        if(bytesAvailable() < static_cast<qint64>(msgSize))
            return;

        *paquet = read(msgSize);

        emit answer(paquet.release());

        msgSize = 0;
    }

public slots:
    void dataReceivedHandler();

signals:
    void answer(QByteArray*);
};

extern "C"  NETWORKSHARED_EXPORT Network* getNetwork();

#endif // NETWORK_H
