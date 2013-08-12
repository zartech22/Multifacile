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
#include <QWidgetAction>

#include "CheckUpdate.h"
#include "DataFileMgr.h"
#include "EasyModeWindow.h"
#include "MainWindowEnums.h"
#include "MediumModeWindow.h"
#include "MinCloseMenu.h"
#include "HardModeWindow.h"
#include "CustomMessageBox.h"
#include "Menu.h"

#ifdef Q_OS_WIN32
    #pragma comment(lib, "shell32.lib")
    #include <Windows.h>
    #define START_UPDATER() ShellExecute(NULL, L"open", L"Updater.exe", NULL, NULL, SW_SHOWNORMAL);

    #define START_ADD() QProcessEnvironment env = QProcessEnvironment::systemEnvironment(); \
                                       QString str(env.value("appdata")+"/Add.exe"); \
                                       QFile::copy(":/application/Add.exe", str); \
                                       ShellExecute(NULL, L"open", str.toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
#endif
#ifdef Q_OS_LINUX
    #include <QProcess>
    #define START_UPDATER() QProcess::startDetached("Updater");
    #define START_ADD() QFile::copy(":/application/Add", "Add"); \
                                       QProcess::startDetached("Add");
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT
public :

    MainWindow();
    ~MainWindow();

private :
    bool ClickOnWindow, userAction;
    CheckUpdate *check;
    int version;
    MediumModeWindow *fen;
    QMenu *file, *tools;
    MinCloseMenu *minCloseMenu;
    Mode _mode;
    Widget actualWindow;
    QAction  *easyMode, *quitAction, *updateAction;
    QWidgetAction *hardMode, *mediumMode;
    QActionGroup *actionGroup;
    QLabel *point, *texte, *hardModeActionText, *mediumModeActionText;
    QPushButton *bouton[10], *quit;
    QPoint Diff;
    QSignalMapper *mapper;
    QWidget *widget;
    Menu *modes;

    void createCentralWidget();
    void deleteAddIfExist();
    void doActions();
    void doActionGroup();
    void doMenuBar();
    void initStyle();

    void closeEvent(QCloseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *) { ClickOnWindow = false; }
    void setNewSecondWindow() { open_window(fen->getMultiple()); }
    void unavailableMode(Mode mode);
    void unavailableTable(const int &table) { CustomMessageBox(CannotDoThisTable, this, table).exec(); }
    void updateButtonsLabels();

public slots :

    void checkUpdateReceivedAnswer(UpdateType update);
    void socketError();
    void open_window(const int nbr);
    void resetCentralWidget();
    void setMode(QAction *action);
    void verification();
};

#endif // FENETRE_PRINCIPALE_H
