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

#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#define VERSION 202

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
#include <QActionGroup>
#include <QList>
#include <QSignalMapper>

#include "EasyModeWindow.h"
#include "MediumModeWindow.h"
#include "HardModeWindow.h"
#include "CheckUpdate.h"
#include "modeEnum.h"

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
    ~Fenetre_principale();
private :

    Mode mode;

    QMenu *file, *tools, *modes;

    QAction *quitAction, *updateAction, *shuffleAction, *chrono, *easyMode, *mediumMode, *hardMode;
    QActionGroup *actionGroup;

    QPushButton *bouton[10];

    QSignalMapper *mapper;

    QPushButton *quit, *customTable;

    QLabel *texte, *espace;

    QGridLayout *layout, *glayout;

    QVBoxLayout *vlayout;

    CheckUpdate *check;

    QWidget *widget;

    QList<MediumModeWindow *> fenList;

    MediumModeWindow *fen;


    int version;

    bool userAction;

    void closeEvent(QCloseEvent * event);

public slots :
    void open_window();
    void open_window(const int nbr);
    void checkUpdateReceivedAnswer(UpdateType update);
    void erreurSocket();
    void verification();
    void setMode(QAction *action);
    void resetLabel(QAction *action);
};

#endif // FENETRE_PRINCIPALE_H
