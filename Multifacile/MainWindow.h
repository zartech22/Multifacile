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
#include "Include.h"
#include "MediumModeWindow.h"
#include "MinCloseMenu.h"
#include "HardModeWindow.h"
#include "CustomMessageBox.h"
#include "Menu.h"
#include "MainWidget.h"
//#include "ProblemWidget.h"


class MainWindow : public QMainWindow  // Classe representant la fenetre. Contient d'autres "fenetres" de type MediumModeWindow (et enfant) ou MainWidget
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


    QLabel *_easyModeActionText;
    QLabel *_mediumModeActionText;
    QLabel *_hardModeActionText;

    CheckUpdate *_check;

    AbstractModeWindow *_fen;

    MinCloseMenu *_minCloseMenu;

    Mode _mode;

    Widget _actualWindow;

    QActionGroup *_actionGroup;
    QActionGroup *_progressifModeActionGroup;

    QPoint _Diff;

    MainWidget *_widget;
    //ProblemWidget *_probWidget;

    Menu *_modes;

    DataFileMgr _mgr;

    void checkSucceedTables();  //lance la verification de la reussite des tables
    void verifyModesPermissions(bool hasProgressifModeChanged = false);  //modife le style des modes en fonction du mode de progression
    void createCentralWidget();  //creer la fenetre de presentation de table
    void deleteAddIfExist();  //supprime le fichier add (ou add.exe) s'il existe
    void doActions();  //creer les items des menus
    void doActionGroup();  //creer les groupes d'items des menus
    void doMenuBar();  //creer la barre de menus
    void initStyle();  //initialise le style

    void closeEvent(QCloseEvent * event);  //reimplementation
    void mouseMoveEvent(QMouseEvent *event) { if(_ClickOnWindow) window()->move(event->globalPos() - _Diff); }  // (les trois prochaine fonctions)  Gestion du deplacement de la fenetre
    void mousePressEvent(QMouseEvent *event) {  _ClickOnWindow = true; _Diff = event->pos(); }
    void mouseReleaseEvent(QMouseEvent *) { _ClickOnWindow = false; }
    void setNewSecondWindow() { openWindow(_fen->getMultiple()); }  //remplace la fentre de table actuellle par celle d'un autre mode
    void unavailableMode(Mode mode);  //Indique un mode inacessible
    void unavailableTable(const operande &table) { CustomMessageBox(CannotDoThisTable, this, table).exec(); }  //indique une table inacessible
    void updateButtonsLabels();  //Lance la mise a jour des boutons de choix de table

public slots :

    void changeProgressifMode(QAction*);  //traitement du changement de mode progressif
    void checkUpdateReceivedAnswer(UpdateType update);  //reception de la reponse du serveur de mise à jour et traitement
    void socketError();  //indique une erreur de connection
    void openWindow(const int nbr);  //ouvre une fenetre de table dans le mode adequat
    void resetCentralWidget() { createCentralWidget(); this->setCentralWidget(_widget); }  //recreer et reeafiche la fenetre de presentationd de table
    void setMode(QAction *action);  //traite le changement de mode
    //void switchToTables();
    //void switchToProblems();
    void verification() { _check->tryConnection(true); }  //lance une verification de mise a jour
};

#endif // FENETRE_PRINCIPALE_H
