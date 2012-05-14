#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#define VERSION 26

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenuBar>
#include <QAction>
#include <QCloseEvent>
#include "bouton.h"
#include "fen_secondaire.h"
#include "CheckUpdate.h"

#ifdef Q_OS_WIN32
    #pragma comment(lib, "shell32.lib")
    #include <Windows.h>
#endif
#ifdef Q_OS_LINUX
    #include <QProcess>
#endif


class Fenetre_principale : public QMainWindow
{
    Q_OBJECT
public :
    Fenetre_principale();
private :

    QMenu *file, *tools, *options;

    QAction *quitAction, *updateAction, *shuffleAction;

    Bouton *bouton1, *bouton2, *bouton3, *bouton4, *bouton5, *bouton6, *bouton7, *bouton8, *bouton9, *bouton10;

    QPushButton *quit, *custom;

    QLabel *texte, *espace;

    QGridLayout *layout, *glayout;

    QVBoxLayout *vlayout;

    Fen_secondaire *fen;

    CheckUpdate *check;

    QWidget *widget;

    int version;

    bool userAction;

    void closeEvent(QCloseEvent * event);

public slots :
    void open_window();
    void open_window(int nbr);
    void answer(bool update);
    void erreurSocket(QAbstractSocket::SocketError erreur);
    void verification();
};

#endif // FENETRE_PRINCIPALE_H
