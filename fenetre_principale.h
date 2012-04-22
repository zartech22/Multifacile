#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#define VERSION 22
#define WIN32
//#define LINUX

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include "bouton.h"
#include "fen_secondaire.h"
#include "CheckUpdate.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QtNetwork>
#include <Windows.h>
#include <QMessageBox>
#include <QProcess>

#pragma comment(lib, "shell32.lib")


class Fenetre_principale : public QWidget
{
    Q_OBJECT
public :
    Fenetre_principale();
private :
    Bouton *bouton1, *bouton2, *bouton3, *bouton4, *bouton5, *bouton6, *bouton7, *bouton8, *bouton9, *bouton10;

    QPushButton *quit, *custom;

    QLabel *texte, *espace;

    QGridLayout *layout, *glayout;

    QVBoxLayout *vlayout;

    Fen_secondaire *fen;

    CheckUpdate *check;

    int version;

public slots :
    void open_window();
    void open_window(int nbr);
    void answer(bool update);
    void erreurSocket(QAbstractSocket::SocketError erreur);
};

#endif // FENETRE_PRINCIPALE_H
