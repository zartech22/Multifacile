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

#include "CheckUpdate.h"

CheckUpdate::CheckUpdate(QObject *parent, bool isUserAction) : QObject(parent), _actualVersion(VERSION), _lib(NETWORKLIB), _isUserAction(isUserAction)
{
    typedef Network* (*NetworkConstructor) ();

    NetworkConstructor constructor = (NetworkConstructor) _lib.resolve("getNetwork");

    if(constructor)
        _net = constructor();

    connect(_net, SIGNAL(connected()), this, SLOT(Connected()));
    connect(_net, SIGNAL(answer(QByteArray*)), this, SLOT(dataReceived(QByteArray*)));
    connect(_net, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(error()));
    _net->tryConnection("multifacile.no-ip.org", 8087);
}

void CheckUpdate::dataReceived(QByteArray*array)
{
    QDataStream in(array, QIODevice::ReadOnly);

    QString answer;
    in >> answer;

    if(answer == "ok")
        emit checkUpdateAnswer(NoUpdate);
    else if(answer == "update needed")
        emit checkUpdateAnswer(NormalUpdate);
    else if(answer == "updaterUpdate")
        emit checkUpdateAnswer(UpdaterUpdate);
}
