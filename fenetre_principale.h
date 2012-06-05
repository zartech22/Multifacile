#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#define VERSION 28

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
#include "bouton.h"
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

    Bouton *bouton[10];

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
    void open_window(int nbr);
    void answer(bool update);
    void erreurSocket();
    void verification();
    void setMode(QAction *action);
    void resetLabel(QAction *action);
};

#endif // FENETRE_PRINCIPALE_H
