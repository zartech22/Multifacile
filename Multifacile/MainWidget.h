#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QSignalMapper>
#include <QApplication>

#include "MainWindowEnums.h"
#include  "DataFileMgr.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(Mode mode);

    void updateButtonsLabels(Mode mode);
    void updateButtonsLabels(Mode mode, bool isProgressifMode);
    void checkSucceedTables(Mode mode);

private:
    QLabel *_point;
    QLabel *_texte;

    QPushButton *_bouton[10];
    QPushButton *_quit;

    QSignalMapper *_mapper;
    
signals:
    void clicked(int);
        
};

#endif // MAINWIDGET_H
