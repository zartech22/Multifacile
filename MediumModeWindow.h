#ifndef FEN_SECONDAIRE_H
#define FEN_SECONDAIRE_H

#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QTimer>
#include <QtDebug>
#include <QLCDNumber>

#include "fen_correction.h"
#include "spinBox.h"
#include "Shuffle.h"


class MediumModeWindow : public QWidget
{
    Q_OBJECT
public :
    MediumModeWindow();
    MediumModeWindow(const int multiplicateur, bool chrono);
    virtual ~MediumModeWindow();
protected :
    int m_multiple;

    int array[10], secondes;

    QLabel *label[10], *text, *minute, *seconde, *deuxPoint;

    QVBoxLayout *vlayout;

    QHBoxLayout *hlayoutBottom, *hlayoutTop;

    QFormLayout *layout;

    QPushButton *corriger;

    SpinBox *reponses[10];

    Fen_correction *fen;

    QTimer *chronometre;

    void startTime();
    void closeEvent(QCloseEvent *event);

    bool time;

signals:
    void addSeconde(int);
public slots:
    virtual void open();
    void newSetFocus(int number);
    void newSecond();
    void updateLabel(int temps);

};

#endif // FEN_SECONDAIRE_H