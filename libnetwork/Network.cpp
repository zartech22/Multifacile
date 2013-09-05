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

#include "Network.h"

extern "C"  NETWORKSHARED_EXPORT Network* getNetwork();

Network* getNetwork() { return new Network(); }

Network::Network() : QTcpSocket(),  _msgSize(0), _msg64Size(0) { connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived())); }

void Network::quint16DataReceived()
{
    QDataStream in(this);
    QByteArray *paquet = new QByteArray;

    if(_msgSize == 0)
    {
        if(bytesAvailable() < (int)sizeof(quint16))
            return;
        in >> _msgSize;
    }

    if(bytesAvailable() < _msgSize)
        return;
    *paquet = read(_msgSize);

    emit answer(paquet);

    _msgSize = 0;
}

void Network::quint64DataReceived()
{
    QDataStream in(this);
    QByteArray *paquet = new QByteArray;

    if(_msg64Size == 0)
    {
        if(bytesAvailable() < (int) sizeof(quint64))
            return;
        in >> _msg64Size;
    }
    if(bytesAvailable() <  (qint64)_msg64Size)
        return;

    *paquet = read(_msg64Size);

    emit answer(paquet);

    _msg64Size = 0;
}
