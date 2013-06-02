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

#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#include <QAbstractSocket>
#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QCloseEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QMenuBar>
#include <QPoint>
#include <QProcessEnvironment>
#include <QPushButton>
#include <QSignalMapper>
#include <QVBoxLayout>
#include <QWidget>

#include "CheckUpdate.h"
#include "EasyModeWindow.h"
#include "FenetrePrincipaleEnums.h"
#include "MediumModeWindow.h"
#include "MinCloseMenu.h"
#include "HardModeWindow.h"

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

    bool ClickOnWindow, userAction;
    CheckUpdate *check;
    int version;
    MediumModeWindow *fen;
    QMenu *file, *tools, *modes;
    MinCloseMenu *minCloseMenu;
    Mode mode;
    Window actualWindow;
    QAction *easyMode, *hardMode, *mediumMode, *quitAction, *updateAction;
    QActionGroup *actionGroup;
    QLabel *point, *texte;
    QPushButton *bouton[10], *quit;
    QPoint Diff;
    QSignalMapper *mapper;
    QWidget *widget;

    void createCentralWidget();

    inline void closeEvent(QCloseEvent * event);
    inline void mouseMoveEvent(QMouseEvent *event);
    inline void mousePressEvent(QMouseEvent *event);
    inline void mouseReleaseEvent(QMouseEvent *);
    inline void setNewSecondWindow();

public slots :

    void checkUpdateReceivedAnswer(UpdateType update);
    void erreurSocket();
    void open_window(const int nbr);
    void resetCentralWidget();
    void resetLabel(QAction *action);
    void setMode(QAction *action);
    void verification();
};

#endif // FENETRE_PRINCIPALE_H
