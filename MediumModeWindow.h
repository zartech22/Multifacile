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
#include "fen_correction.h"
#include "spinBox.h"
#include "Shuffle.h"


class MediumModeWindow : public QWidget
{
    Q_OBJECT
public :
    MediumModeWindow();
    MediumModeWindow(const int multiplicateur);
    virtual ~MediumModeWindow();
protected :
    int m_multiple;

    int array[10];

    QLabel *label[10];

    QVBoxLayout *vlayout;

    QHBoxLayout *hlayout;

    QFormLayout *layout;

    QPushButton *corriger;

    SpinBox *reponses[10];

    Fen_correction *fen;


public slots:
    virtual void open();
    void newSetFocus(int number);

};

#endif // FEN_SECONDAIRE_H
