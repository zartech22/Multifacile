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

#ifndef CHECKUPDATE_H
#define CHECKUPDATE_H

#define VERSION 330

#ifdef DEBUG
    #define NETWORKLIB "networkd"
#elif defined(RELEASE)
    #define NETWORKLIB "network"
#endif

#include <QTcpSocket>
#include <QDataStream>
#include <QLibrary>

#include "../libnetwork/Network.h"

enum UpdateType
{
    NoUpdate, NormalUpdate, UpdaterUpdate
};

typedef enum UpdateType UpdateType;

class CheckUpdate : public QObject
{
    Q_OBJECT
public:
    CheckUpdate(QObject *parent, const int version);
    void tryConnection() { net->tryConnection("multifacile.no-ip.org", 8087); }
    void disconnectFromHost() { net->disconnectFromHost(); }
private:
    QLibrary lib;
    Network *net;
    quint16 messageSize;
    int actualVersion;
public slots:
    void dataReceived(QByteArray*);
    void Connected() { net->sendVersion(actualVersion); }
signals:
    void checkUpdateAnswer(UpdateType);
    void error();
};

#endif // CHECKUPDATE_H
