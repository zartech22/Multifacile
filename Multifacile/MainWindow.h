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

#include <QDebug>

#include "CheckUpdate.h"
#include "DataFileMgr.h"
#include "EasyModeWindow.h"
#include "MainWindowEnums.h"
#include "MediumModeWindow.h"
#include "MinCloseMenu.h"
#include "HardModeWindow.h"
#include "CustomMessageBox.h"
#include "Menu.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public :

    MainWindow();
    ~MainWindow();

private :
    bool _ClickOnWindow;
    bool _isProgressifMode;

    QMenu *_file;
    QMenu *_tools;

    QAction *_freeMode;
    QAction *_progressifMode;
    QAction *_quitAction;
    QAction *_updateAction;


    QWidgetAction *_easyMode;
    QWidgetAction *_mediumMode;
    QWidgetAction *_hardMode;

    QLabel *_point;
    QLabel *_texte;
    QLabel *_easyModeActionText;
    QLabel *_mediumModeActionText;
    QLabel *_hardModeActionText;

    QPushButton *_bouton[10];
    QPushButton *_quit;

    CheckUpdate *_check;

    MediumModeWindow *_fen;

    MinCloseMenu *_minCloseMenu;

    Mode _mode;

    Widget _actualWindow;

    QActionGroup *_actionGroup;
    QActionGroup *_progressifModeActionGroup;

    QPoint _Diff;

    QSignalMapper *_mapper;

    QWidget *_widget;

    Menu *_modes;

    DataFileMgr _mgr;

    void checkSucceedTables();
    void verifyModesPermissions(bool hasProgressifModeChanged = false);
    void createCentralWidget();
    void deleteAddIfExist();
    void doActions();
    void doActionGroup();
    void doMenuBar();
    void initStyle();

    void closeEvent(QCloseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *) { _ClickOnWindow = false; }
    void setNewSecondWindow() { open_window(_fen->getMultiple()); }
    void unavailableMode(Mode mode);
    void unavailableTable(const unsigned short int &table) { CustomMessageBox(CannotDoThisTable, this, table).exec(); }
    void updateButtonsLabels();

public slots :

    void changeProgressifMode(QAction*);
    void checkUpdateReceivedAnswer(UpdateType update);
    void socketError();
    void open_window(const int nbr);
    void resetCentralWidget();
    void setMode(QAction *action);
    void verification() { _check->tryConnection(true); }
};

#endif // FENETRE_PRINCIPALE_H
