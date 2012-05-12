#ifndef FEN_SECONDAIRE_H
#define FEN_SECONDAIRE_H

#include <QApplication>
#include <QWidget>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include "fen_correction.h"
#include "Shuffle.h"


class Fen_secondaire : public QWidget
{
    Q_OBJECT
public :
    Fen_secondaire(const int multiplicateur, bool shuffle);
    ~Fen_secondaire();
private :
    int m_multiplicateur;

    int array[10];

    QLabel *label[10];

    QVBoxLayout *vlayout;

    QHBoxLayout *hlayout;

    QFormLayout *layout;

    QPushButton *corriger, *melanger;

    QSpinBox *reponses[10];

    Fen_correction *fen;


public slots:
    void open();
    void Melange();

};

#endif // FEN_SECONDAIRE_H
