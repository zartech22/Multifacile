#ifndef PROBLEMWIDGET_H
#define PROBLEMWIDGET_H

#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QSignalMapper>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QRegExpValidator>

#include <QDebug>

#include "Shuffle.h"

class ProblemWidget : public QWidget
{

    Q_OBJECT

public:
    ProblemWidget();
private:
    QPushButton *_tables;
    QPushButton *_problems;

    QPushButton *_chooseATable;
    QPushButton *_correction;
    QPushButton *_quit;

    QLineEdit *_answer;

    QLabel *_text;

    QSqlDatabase bdd;

    static bool bddIsCreated;

public slots:
    void showProblem(int table);

signals :
    void goToTables();
};

#endif // PROBLEMWIDGET_H
