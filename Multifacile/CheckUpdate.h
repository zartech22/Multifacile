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

#define VERSION 340

#define CHECK_PORT 8087
#define SERVER_ADDR "127.0.0.1"

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

class CheckUpdate : public QObject  // Classe gérant la mise à jour de Multifacile
{
    Q_OBJECT

public:
    CheckUpdate(QObject *parent,  bool isUserAction = false);
    void tryConnection(bool isUserAction = false) { _isUserAction = isUserAction; _net->tryConnection(SERVER_ADDR, CHECK_PORT); }  //Lance une connection au serveur
    void disconnectFromHost() { _net->disconnectFromHost(); }  //deconecte du serveur
    bool isUserAction() const { return _isUserAction; }
    void runMultifacileUpdate() { START_UPDATER(); }
    void runUpdaterUpdate() { START_ADD(); }

private:
    Network *_net;
    int _actualVersion;
    bool _isUserAction;  // Vrai si c'est l'utilisateur qui a demande a verifier les mise a jours Faux sinon

public slots:
    void dataReceived(QByteArray*);
    void Connected() { _net->sendVersion(_actualVersion); }  //Lorsque connecte au serveur, envoyer la version actuel

signals:
    void checkUpdateAnswer(UpdateType);  //Envoie de la reponse : mise a jour disponoble pour multifacile ou pour l'updater, pas de mise à jour
    void error();
};

#endif // CHECKUPDATE_H
