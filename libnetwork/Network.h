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

enum QUIntSize
{
    QUInt16, QUInt32, QUInt64
};

typedef enum QUIntSize QUIntSize;

class NETWORKSHARED_EXPORT Network : public QTcpSocket
{
    Q_OBJECT
    
public:
    Network();
    void sendMsg(const QString &msg, QUIntSize answerMsgSize = QUInt16) { _size = answerMsgSize; writePaquet<QString>(msg); }
    void sendVersion(const unsigned int version) {  _size = QUInt16; writePaquet<unsigned int>(version); }
    void tryConnection(const QString &host, const unsigned int port) { connection(host, port); }

private:
    void connection(const QString &host, const unsigned int port) { abort(); connectToHost(host, port); }

    unsigned int _version;
    quint16 _msgSize;
    quint64 _msg64Size;
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

public slots:
    void dataReceived() { (_size == QUInt16) ? quint16DataReceived() : quint64DataReceived(); }
    void quint16DataReceived();
    void quint64DataReceived();
signals:
    void answer(QByteArray*);
};

#endif // NETWORK_H
