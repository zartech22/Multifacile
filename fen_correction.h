#ifndef FEN_CORRECTION_H
#define FEN_CORRECTION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "spinBox.h"


class Fen_correction : public QWidget
{
public :
    Fen_correction(const int multiple, SpinBox *reponses[], int *order);
    ~Fen_correction();
private :

    void notation();

    int m_multiple;
    int reponse[10], resultat[10];
    int *tab;
    int note;
    QLabel *multiplication[10];
    QLabel *correction[10];
    QLabel *texte;
    QLabel *total;

    QPushButton *quit;

    QVBoxLayout *vlayout;

    QGridLayout *layout;

    QHBoxLayout *hlayout[3];

};

#endif // FEN_CORRECTION_H
