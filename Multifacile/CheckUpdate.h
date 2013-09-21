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


#include <QDataStream>
#include <QLibrary>
#include <QProcessEnvironment>
#include <QFile>

#include "../libnetwork/Network.h"

#ifdef Q_OS_WIN
    #pragma comment(lib, "shell32.lib")
    #include <Windows.h>
    #define START_UPDATER() ShellExecute(NULL, L"open", L"Updater.exe", NULL, NULL, SW_SHOWNORMAL);

    #define START_ADD() QProcessEnvironment env = QProcessEnvironment::systemEnvironment(); \
                                       QString str(env.value("appdata")+"/Add.exe"); \
                                       QFile::copy(":/application/Add.exe", str); \
                                       ShellExecute(NULL, L"open", str.toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
#elif defined(Q_OS_LINUX) || defined(Q_OS_MAC)
    #include <QProcess>
    #define START_UPDATER() QProcess::startDetached("Updater");
    #define START_ADD() QFile::copy(":/application/Add", "Add"); \
                                       QProcess::startDetached("Add");
#endif


enum UpdateType
{
    NoUpdate, NormalUpdate, UpdaterUpdate
};

typedef enum UpdateType UpdateType;

class CheckUpdate : public QObject
{
    Q_OBJECT
public:
    CheckUpdate(QObject *parent, const unsigned short int version, bool isUserAction = false);
    void tryConnection(bool isUserAction = false) { _isUserAction = isUserAction; net->tryConnection("multifacile.no-ip.org", 8087); }
    void disconnectFromHost() { net->disconnectFromHost(); }
    bool isUserAction() const { return _isUserAction; }
    void runMultifacileUpdate() { START_UPDATER(); }
    void runUpdaterUpdate() { START_ADD(); }
private:
    QLibrary lib;
    Network *net;
    quint16 messageSize;
    int actualVersion;
    bool _isUserAction;
public slots:
    void dataReceived(QByteArray*);
    void Connected() { net->sendVersion(actualVersion); }
signals:
    void checkUpdateAnswer(UpdateType);
    void error();
};

#endif // CHECKUPDATE_H
